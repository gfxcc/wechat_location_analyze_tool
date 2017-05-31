#ifndef _WECHAT_ANALYZE_REVIEW_H_
#define _WECHAT_ANALYZE_REVIEW_H_

#include <iostream>
#include <string>
#include <vector>


class WechatAccount;
class Statistic;

class Review {
public:

  enum Type {NoMatch = 0, Match, SingleMatch, DoubleMatch, MultiMatch};

  Review(std::vector<WechatAccount>& data, Statistic& statis) : data_size_(data.size()), data_(data),
                                             statis_(statis){}

  void Start();

  void PrintMatch(Type type, int row);
private:

  bool FitType(Type type, int size);

  int index_[5] = {0}, data_size_;
  std::vector<WechatAccount>& data_;
  Statistic& statis_;
};

#endif
