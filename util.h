#ifndef _WECHAT_ANALYZE_UTIL_H_
#define _WECHAT_ANALYZE_UTIL_H_

#include <string>
#include <utility>
#include <codecvt>
#include <vector>
#include <locale>
#include <memory>

#include "wechat.h"

std::string wc2s(const wchar_t& wc);

std::wstring s2ws(const std::string& str);

std::string ws2s(const std::wstring& wstr);
// recursively visit every files under specific path
int OperateEveryFileUnderPath(std::string dir,
    std::vector<std::pair<std::string, std::wstring>>& locations);

// row indicated how many rows should be read
int ReadWechatAccountFromFile(std::string file_path,
    std::vector<WechatAccount>& wechat_accounts, int row);


#endif
