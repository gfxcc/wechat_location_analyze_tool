#ifndef _WECHAT_ANALYZE_STATISTIC_H_
#define _WECHAT_ANALYZE_STATISTIC_H_

#include <vector>
#include <string>


class WechatAccount;

class Statistic {
public:
  Statistic(std::vector<WechatAccount>& data) : cnt_(0), match_(0), single_match_(0),
  double_match_(0), multi_match_(0), data_(data) {}

  void Process();
  void Print();
private:
  int cnt_, match_, single_match_, double_match_, multi_match_;
  std::vector<WechatAccount>& data_;

};

#endif
