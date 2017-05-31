#include "util.h"

#include <errno.h>
#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <fstream>
#include <stdio.h>
#include <json.hpp>
#include <ctime>

#include "wechat.h"

using namespace std;
using nlohmann::json;

void Usage() {
  cout << "Usage: analyze [OPTION] pattern" << endl;
  cout << "       -r arg: set path_region" << endl;
  cout << "       -w arg: set path_wechat" << endl;
  cout << "       -o arg: enable output to file and set path_output" << endl;
  cout << "       -l arg: row_need_read_from_wechat" << endl;
  cout << "       -d    : enable debug mode" << endl;
  cout << "       -h    : help" << endl;
}

void PrintDateTime() {
  time_t now = time(0);
  // convert now to string form
  char* dt = ctime(&now);
  cout << "The local date and time is: " << dt << endl;
}

int ReadRegionJsonFile(string path, vector<pair<string, wstring>>& locations) {
  ifstream input(path);
  if (input.is_open() == false) {
    return -1;
  }
  json j;
  input >> j;

  for (auto it = j.begin(); it != j.end(); it++) {
    if (it.value().get<string>() == "城区")
      continue;
    locations.emplace_back(it.key(), s2ws(it.value().get<string>()));
  }
  return 0;
}

int ReadNormalWechatFile(string path, vector<WechatAccount>& wechat_accounts,
                         unordered_set<string>& st_wechat_uuid, int row) {
  ifstream input(path);
  if (input.is_open() == false) {
    return -1;
  }
  string line;
  int cnt = wechat_accounts.size();
  while (getline(input, line)) {
    if (cnt++ >= row) {
      cout << endl;
      return 0;
    }
    WechatAccount account(line);
    string uuid = account.GetInfo(WechatAccount::Field::uuid);
    if (account.IsValid() && st_wechat_uuid.count(uuid) == 0) {
      wechat_accounts.emplace_back(line);
      st_wechat_uuid.insert(uuid);
    }
    else
      cout << "drop:" << line << endl;

    // print \r info
    printf("\rInfo: loading wechat... %i ( %i %% )", cnt, cnt * 100 / row);
    fflush(stdout);
  }
  cout << endl;
  return 0;

}

string GetPath(string parent, string dir) {
  return parent + "/" + dir;
}

std::string wc2s(const wchar_t& wc) {
  wstring ws(1, wc);
  using convert_typeX = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_typeX, wchar_t> converterX;

  return converterX.to_bytes(ws);

}

// implements
std::wstring s2ws(const std::string& str)
{

  using convert_typeX = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_typeX, wchar_t> converterX;

  wstring ret;
  try {
    ret = converterX.from_bytes(str);
  } catch (...) {
    return wstring();
  }
  return ret;
}

std::string ws2s(const std::wstring& wstr)
{
  using convert_typeX = std::codecvt_utf8<wchar_t>;
  std::wstring_convert<convert_typeX, wchar_t> converterX;

  string ret;
  try {
    ret = converterX.to_bytes(wstr);
  } catch (...) {
    return string();
  }
  return ret;
}


