#include "util.h"

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <fstream>
#include <stdio.h>
#include <json.hpp>

using namespace std;
using nlohmann::json;

// local help func
void ReadJsonFile(string path, vector<pair<string, wstring>>& locations) {
  ifstream input(path);
  json j;
  input >> j;

  for (auto it = j.begin(); it != j.end(); it++) {
    if (it.value().get<string>() == "城区")
      continue;
    locations.emplace_back(it.key(), s2ws(it.value().get<string>()));
  }
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

int OperateEveryFileUnderPath(string dir, vector<pair<string, wstring>>& locations) {
  DIR *dp;
  struct dirent *dirp;
  if((dp  = opendir(dir.c_str())) == NULL) {
    cout << "Error(" << errno << ") opening " << dir << endl;
    return errno;
  }

  while ((dirp = readdir(dp)) != NULL) {
    string filename(dirp->d_name);
    switch (dirp->d_type) {
      case DT_REG:
        // operation
        ReadJsonFile(GetPath(dir, filename), locations);
        break;
      case DT_DIR:
        if (filename != "." && filename != "..")
          OperateEveryFileUnderPath(dir + "/" + filename, locations);
        break;
      default:
        break;
    }
  }
  closedir(dp);
  return 0;
}

int ReadWechatAccountFromFile(std::string file_path,
    std::vector<WechatAccount>& wechat_accounts, int row) {
  ifstream input(file_path);
  if (input.is_open() ==  false) {
    cout << "ERROR: open wechat account file failed" << endl;
    return -1;
  }
  string line;
  int cnt = 0;
  while (getline(input, line)) {
    if (cnt++ > row)
      return 0;
    WechatAccount account(line);
    if (account.IsValid())
      wechat_accounts.emplace_back(line);
    else
      cout << "drop:" << line << endl;

    // print \r info
    printf("\r processing... %i ( %i %% )", cnt, cnt * 100 / 10000000);
    fflush(stdout);
  }
  return 0;
}


