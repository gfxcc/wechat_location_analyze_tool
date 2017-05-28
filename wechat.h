#ifndef WECHAT_ANALYZE_WECHAT_H_
#define WECHAT_ANALYZE_WECHAT_H_

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <boost/algorithm/string.hpp>

class WechatAccount{
public:
  enum Field {info_0 = 0, info_1, name, info_2, intro, info_4, info_5, date};
  WechatAccount(const std::string& str) {
    boost::split(infos_, str, boost::is_any_of("\t"));
  }

  std::string GetInfo(Field f) {
    return infos_[f];
  }

  void Insert(const std::pair<std::string, std::string>& location) {
    locations_.emplace_back(location);
  }

  void Print() {
    std::cout << "--WechatAccount--" << std::endl;
    std::cout << "name:" << infos_[Field::name] << std::endl;
    std::cout << "intro:" << infos_[Field::intro] << std::endl;
    std::cout << "locations:" << locations_.size() << std::endl;
    for (auto& location : locations_) {
      std::cout << "        " << location.first << ":" << location.second << std::endl;
    }
    std::cout << std::endl;
  }

  bool IsValid() {
    return infos_.size() == 8;
  }

  int GetInfoSize() {
    return infos_.size();
  }

  int GetSizeOfLocation() {
    return locations_.size();
  }

  void Debug() {
    for (auto& info : infos_)
      std::cout << info << std::endl;
    std::cout << std::endl;
  }
private:
  std::vector<std::string> infos_;
  std::vector<std::pair<std::string, std::string>> locations_;
};



#endif // WECHAT_ANALYZE_WECHAT_H_
