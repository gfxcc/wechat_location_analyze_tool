#ifndef _WECHAT_ANALYZE_UTIL_H_
#define _WECHAT_ANALYZE_UTIL_H_

#include <string>
#include <utility>
#include <codecvt>
#include <vector>
#include <locale>
#include <memory>
#include <unordered_set>

class WechatAccount;


//
void Usage();

//
void PrintDateTime();

// convert wchar_t to string
std::string wc2s(const wchar_t& wc);

// convert string to wstring ; used for handle chinese character
std::wstring s2ws(const std::string& str);

// conver wstring to string
std::string ws2s(const std::wstring& wstr);

//
int ReadRegionJsonFile(const std::string& path,
                       std::vector<std::pair<std::string, std::wstring>>& locations);
int ReadNormalWechatFile(const std::string& path,
                         std::vector<WechatAccount>& wechat_accounts,
                         std::unordered_set<std::string>& st_wechat_uuid,
                         int row);

// build path for file under parent path
std::string GetPath(const std::string& parent, const std::string& dir);

#endif
