#ifndef _WECHAT_ANALYZE_STATISTIC_H_
#define _WECHAT_ANALYZE_STATISTIC_H_

#include <vector>
#include <string>
#include <iostream>


class WechatAccount;

class Statistic {
public:
  Statistic(std::vector<WechatAccount>& data) : cnt_(0), match_(0), single_match_(0),
                                    double_match_(0), multi_match_(0), data_(data) {}

  void Process() {
    for (auto& account : data_) {
      cnt_++;
      if (account.GetSizeOfLocation() >= 3) {
        match_++; multi_match_++;
      } else if (account.GetSizeOfLocation() == 2) {
        match_++; double_match_++;
      } else if (account.GetSizeOfLocation() == 1) {
        match_++; single_match_++;
      }
    }
  }

  void Print() {
    std::cout << "-------------------------Statistic Result---------------------------" << std::endl;
    std::cout << cnt_ << " wechat account exist" << std::endl;
    std::cout << "Matched:" << match_ << " ( " << int(match_ * 100 / cnt_) << "% )" << std::endl;
    std::cout << "Single:" << single_match_ << " ( " << int(single_match_ * 100 / cnt_) << "% )" << std::endl;
    std::cout << "Double:" << double_match_ << " ( " << int(double_match_ * 100 / cnt_) << "% )" << std::endl;
    std::cout << "Multi:" << multi_match_ << " ( " << int(multi_match_ * 100 / cnt_) << "% )" << std::endl;
  }

private:
  std::vector<WechatAccount>& data_;
  int cnt_, match_, single_match_, double_match_, multi_match_;
};

#endif
