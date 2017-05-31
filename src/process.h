#ifndef _WECHAT_ANALYZE_PROCESS_H_
#define _WECHAT_ANALYZE_PROCESS_H_

#include <string>
#include <vector>
#include <utility>
#include <unordered_set>

class WechatAccount;
class Trie;

// main process func
void Process(Trie& trie, std::vector<WechatAccount>& wechat_accounts);

// recursively read file under path
int LoadRegionDataFromPath(const std::string& path,
    std::vector<std::pair<std::string, std::wstring>>& regions);

//
int LoadWechatDataFromPath(const std::string& path, std::vector<WechatAccount>& wechat_accounts,
                           std::unordered_set<std::string>& st_wechat_uuid, int row);

//
int OutputToFile(const std::string& path, std::vector<WechatAccount>& wechat_accounts);

#endif
