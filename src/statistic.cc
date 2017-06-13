#include "statistic.h"

#include "wechat.h"

#include <iostream>

void Statistic::Process() {
  for (auto& account : data_) {
    cnt_++;
    if (account.GetSizeOfRegion() >= 3) {
      match_++; multi_match_++;
    } else if (account.GetSizeOfRegion() == 2) {
      match_++; double_match_++;
    } else if (account.GetSizeOfRegion() == 1) {
      match_++; single_match_++;
    }
  }
}

void Statistic::Print() {
  std::cout << "-------------------------Statistic Result---------------------------" << std::endl;
  std::cout << cnt_ << " wechat account exist" << std::endl;
  std::cout << "Matched:" << match_ << " ( " << int(match_ * 100 / cnt_) << "% )" << std::endl;
  std::cout << "Single:" << single_match_ << " ( " << int(single_match_ * 100 / cnt_) << "% )" << std::endl;
  std::cout << "Double:" << double_match_ << " ( " << int(double_match_ * 100 / cnt_) << "% )" << std::endl;
  std::cout << "Multi:" << multi_match_ << " ( " << int(multi_match_ * 100 / cnt_) << "% )" << std::endl;
}

