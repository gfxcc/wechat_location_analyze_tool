#ifndef _WECHAT_ANALYZE_REVIEW_H_
#define _WECHAT_ANALYZE_REVIEW_H_

#include <iostream>
#include <string>
#include <vector>


class WechatAccount;

class Review {
public:

  enum Type {NoMatch = 0, Match, SingleMatch, DoubleMatch, MultiMatch};

  Review(std::vector<WechatAccount>& data) : data_size_(data.size()), data_(data) {}

  void PrintMatch(Type type, int row) {
    int index = index_[type];
    for (int cnt = 0; cnt < row && index < data_size_; index++) {
      WechatAccount& account = data_[index];
      if (FitType(type, account.GetSizeOfLocation())) {
        account.Print();
        cnt++;
      }
    }
    index_[type] = index;
  }

private:

  bool FitType(Type type, int size) {
    switch (type) {
      case Type::NoMatch:
        return size == 0;
        break;
      case Type::Match:
        return size;
        break;
      case Type::SingleMatch:
        return size == 1;
        break;
      case Type::DoubleMatch:
        return size == 2;
        break;
      case Type::MultiMatch:
        return size >= 3;
        break;
      default:
        return false;
    }
    return false;
  }

  int index_[5] = {0}, data_size_;
  std::vector<WechatAccount>& data_;
};

#endif
