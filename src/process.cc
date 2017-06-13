#include "process.h"

#include <dirent.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <stdio.h>
#include <json.hpp>

#include "util.h"
#include "wechat.h"
#include "sql.h"

// add ltp library
#include "crk/crk.h"

using namespace std;
using namespace crk;

int Process(std::vector<WechatAccount>& wechat_accounts) {

  // create crk engine
  Engine* engine_raw;
  Options options;
  options.model_segmentor = "/home/yong/Program/project/wechat_location_analyze_tool/thirdparty/crk/thirdparty/ltp/models/cws.model";
  options.model_postagger = "/home/yong/Program/project/wechat_location_analyze_tool//thirdparty/crk/thirdparty/ltp/models/pos.model";
  options.region_data = "/home/yong/Program/project/wechat_location_analyze_tool/thirdparty/crk/region_data/";
  Status s = Engine::CreateEngine(options, &engine_raw);

  if (s.ok() == false) {
    cout << "Error: failed to create crk engine" << endl;
    cout << "Error: crk: " << s.msg << endl;
    return -1;
  }
  // wrap engine_raw into unique_ptr
  unique_ptr<Engine> engine(engine_raw);

  int accounts_size = wechat_accounts.size();
  for (int i = 0; i < accounts_size; i++) {
    auto& account = wechat_accounts[i];
    string input = account.GetInfo(WechatAccount::Field::name) + " " +
                   account.GetInfo(WechatAccount::Field::intro);
    vector<vector<pair<string, string>>> regions;

    engine->MatchRegion(input, regions);

    for (auto& ele : regions) {
      for (auto& region : ele) {
        account.Insert(move(region));
      }
    }

    printf("\rInfo: parsing wechat... %i ( %i %% )", i, i * 100 / accounts_size);
    fflush(stdout);
  }
  cout << endl;

  return 0;
}



int LoadRegionDataFromPath(const std::string& path,
    std::vector<std::pair<std::string, std::wstring>>& regions) {
  int ret = 0;
  DIR *dp;
  struct dirent *dirp;
  if((dp  = opendir(path.c_str())) == NULL) {
    cout << "Error(" << strerror(errno) << ") opening " << path << endl;
    return errno;
  }

  while ((dirp = readdir(dp)) != NULL) {
    string filename(dirp->d_name);
    switch (dirp->d_type) {
      case DT_REG:
        // load file
        // find detail in util.h
        ret = ReadRegionJsonFile(GetPath(path, filename), regions);
        if (ret != 0) {
          return -1;
        }
        break;
      case DT_DIR:
        if (filename != "." && filename != "..") {
          // recursivly load folder
          ret = LoadRegionDataFromPath(path + "/" + filename, regions);
          if (ret != 0) {
            return -1;
          }
        }
        break;
      default:
        break;
    }
  }
  closedir(dp);
  return 0;
}

int LoadWechatDataFromPath(const std::string& path, std::vector<WechatAccount>& wechat_accounts,
    std::unordered_set<std::string>& st_wechat_uuid, int row) {
  int ret = 0;
  DIR *dp;
  struct dirent *dirp;
  if((dp  = opendir(path.c_str())) == NULL) {
    cout << "Error(" << strerror(errno) << ") opening " << path << endl;
    return errno;
  }

  while ((dirp = readdir(dp)) != NULL) {
    string filename(dirp->d_name);
    switch (dirp->d_type) {
      case DT_REG:
        // load file
        // find detail in util.h
        ret = ReadNormalWechatFile(GetPath(path, filename), wechat_accounts, st_wechat_uuid, row);
        if (ret != 0) {
          return -1;
        }
        break;
      case DT_DIR:
        if (filename != "." && filename != "..") {
          // recursivly load folder
          ret = LoadWechatDataFromPath(path + "/" + filename, wechat_accounts, st_wechat_uuid, row);
          if (ret != 0) {
            return -1;
          }
        }
        break;
      default:
        break;
    }
  }
  closedir(dp);
  return 0;

}


int DumpIntoFile(const vector<WechatAccount>& wechat_accounts) {

  ofstream output;
  output.open("./output/wechat_account_matched.json");

  // json head
  output << "{" << endl;
  output << "  \"WechatAccount\": [" << endl;
  int cnt = 0;
  int accounts_size = wechat_accounts.size();
  for (int i = 0; i < accounts_size; i++) {
    auto& account = wechat_accounts[i];
    if (account.GetSizeOfRegion() == 0) {
      continue;
    }
    if (cnt) {
      output << "," << endl;
    }
    string s = account.GetJsonString();
    output << s;
    cnt++;
    printf("\rInfo: dump into file... %i (%i %%)", i,
        i * 100 / accounts_size);
    fflush(stdout);
  }
  output << "  ]" << endl;
  output << "}" << endl;
  cout << endl;

  output.close();
  return 0;
}


// abandoned functioni
//
//
//
//

int OutputToFile(const string& path,const vector<WechatAccount>& wechat_accounts) {

  ofstream output;
  output.open (path);

  int accounts_size = wechat_accounts.size();
  for (int i = 0; i < accounts_size; i++) {
    const auto& account = wechat_accounts[i];
    if (account.GetSizeOfRegion()) {
      output << "-----------------------------------------" << endl
        << account.GetInfo(WechatAccount::Field::name) << endl
        << account.GetInfo(WechatAccount::Field::intro) << endl;
      for (auto& ele : account.regions_) {
        output << ele.first << ":" << ele.second << endl;
      }
    }
  }

  output.close();
  return 0;
}

void InsertToDatabase(const std::vector<WechatAccount>& wechat_accounts) {

  int wechat_accounts_size = wechat_accounts.size();
  for (int i = 0; i < wechat_accounts_size; i++) {
    const WechatAccount& account = wechat_accounts[i];
    for (auto& location : account.regions_) {
      auto& sql_helper = Sql::GetInstance();
      sql_helper.InsertRegionToWechat(account.GetInfo(WechatAccount::Field::uuid),
          location.first);
    }
    printf("\rInfo: database insertion... %i (%i %%)", i,
        i * 100 / wechat_accounts_size);
    fflush(stdout);
  }
  cout << endl;
}


void DumpWechatAccount(const std::vector<WechatAccount>& wechat_accounts) {

  ofstream output("./output/wechat.sql");
  /*
     int wechat_accounts_size = wechat_accounts.size();
     for (int i = 0; i < wechat_accounts_size; i++) {
     WechatAccount& account = wechat_accounts[i];
     string sql_command = "INSERT INTO wechat_account (uuid, name, intro) VALUES ('" +
     account.GetInfo(WechatAccount::Field::uuid) + "', '" +
     account.GetInfo(WechatAccount::Field::name) + "', '" +
     account.GetInfo(WechatAccount::Field::intro) + "')";
     output << sql_command << ";" << endl;

     printf("\rInfo: dump wechat... %i ( %i %% )", i, i * 100 / wechat_accounts_size);
     fflush(stdout);
     }
     */


  output.close();
}

