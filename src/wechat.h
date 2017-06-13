#ifndef WECHAT_ANALYZE_WECHAT_H_
#define WECHAT_ANALYZE_WECHAT_H_

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <algorithm>

class WechatAccount{
public:

  static int size_intro_;
  static int size_name_;
  static std::string max_intro_;
  static std::string max_name_;

  enum Field {field_0 = 0, uuid, name, field_3, intro, field_5, field_6, date};
  WechatAccount(const std::string& str);

  std::string GetInfo(Field f) const;

  void Insert(const std::pair<std::string, std::string>& location);

  void Print() const;
  bool IsValid() const;
  int GetInfoSize() const;
  int GetSizeOfRegion() const;
  std::string GetJsonString() const;
  void Debug() const;
  std::vector<std::pair<std::string, std::string>> regions_;
private:
  std::vector<std::string> infos_;
};


#endif // WECHAT_ANALYZE_WECHAT_H_
