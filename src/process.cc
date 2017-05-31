#include "process.h"

#include <dirent.h>
#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <stdio.h>

#include "util.h"
#include "trie.h"
#include "wechat.h"

using namespace std;

void Process(Trie& trie, std::vector<WechatAccount>& wechat_accounts) {

  int accounts_size = wechat_accounts.size();
  for (int i = 0; i < accounts_size; i++) {
    auto& account = wechat_accounts[i];
    unordered_map<string, string> locations;
    // process name
    string name = account.GetInfo(WechatAccount::Field::name);
    for (int i = 0; i < name.size(); i += 3) {
      int len = min(10, static_cast<int>(name.size()) - i);
      string keyword = name.substr(i, len);
      auto ret = trie.find(s2ws(keyword));
      for (auto& ele : ret) {
        locations[ele.first] = ele.second;
      }
    }

    // process intro
    string intro = account.GetInfo(WechatAccount::Field::intro);
    for (int i = 0; i < intro.size(); i += 3) {
      int len = min(10, static_cast<int>(intro.size()) - i);
      string keyword = intro.substr(i, len);
      auto ret = trie.find(s2ws(keyword));
      for (auto& ele : ret) {
        locations[ele.first] = ele.second;
      }
    }

    // insert locations into acount
    for (auto& location : locations) {
      account.Insert(location);
    }

    printf("\rInfo: parsing wechat... %i ( %i %% )", i, i * 100 / accounts_size);
    fflush(stdout);

/*
    // print match result
    cout << "---------------------------------------------------" << endl;
    cout << "name:" << account.GetInfo(WechatAccount::Field::name) << endl;
    cout << "intro:" << account.GetInfo(WechatAccount::Field::intro) << endl;
    cout << locations.size() << " regions matched successed" << endl;
    for (auto& location : locations) {
      cout << location.first << ":" << location.second << endl;
    }
    cout << "---------------------------------------------------" << endl;
*/
  }
  cout << endl;
}



int LoadRegionDataFromPath(const std::string& path,
    std::vector<std::pair<std::string, std::wstring>>& regions) {
  int ret = 0;
  DIR *dp;
  struct dirent *dirp;
  if((dp  = opendir(path.c_str())) == NULL) {
    cout << "Error(" << errno << ") opening " << path << endl;
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
    cout << "Error(" << errno << ") opening " << path << endl;
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

int OutputToFile(const string& path, vector<WechatAccount>& wechat_accounts) {

  ofstream output;
  output.open (path);

  int accounts_size = wechat_accounts.size();
  for (int i = 0; i < accounts_size; i++) {
    auto& account = wechat_accounts[i];
    if (account.GetSizeOfLocation()) {
      output << "-----------------------------------------" << endl
             << account.GetInfo(WechatAccount::Field::name) << endl
             << account.GetInfo(WechatAccount::Field::intro) << endl;
      for (auto& ele : account.locations_) {
        output << ele.first << ":" << ele.second << endl;
      }
    }
  }

  output.close();
  return 0;
}


