#include "review.h"

#include <iostream>
#include <string>

#include "statistic.h"
#include "wechat.h"

using namespace std;

void Review::Start() {
  while (true) {
    // waiting for review
    cout << "Processing Finished; Please enter review command" << endl;
    cout << "q         exit" << endl;
    cout << "i         print statistic information" << endl;
    cout << "n num     print num empty match" << endl;
    cout << "m num     print num match" << endl;
    cout << "s num     print num single match" << endl;
    cout << "d num     print num double match" << endl;
    cout << "u num     print num multi match" << endl;

    cout << "> ";
    string cmd;
    cin >> cmd;
    if (cmd == "q")
      break;
    switch(cmd[0]) {
      case 'i':
        statis_.Print();
        break;
      case 'n':
        cin >> cmd;
        PrintMatch(Review::Type::NoMatch, stoi(cmd));
        break;
      case 'm':
        cin >> cmd;
        PrintMatch(Review::Type::Match, stoi(cmd));
        break;
      case 's':
        cin >> cmd;
        PrintMatch(Review::Type::SingleMatch, stoi(cmd));
        break;
      case 'd':
        cin >> cmd;
        PrintMatch(Review::Type::DoubleMatch, stoi(cmd));
        break;
      case 'u':
        cin >> cmd;
        PrintMatch(Review::Type::MultiMatch,stoi(cmd));
        break;
      default:
        cout << "wrong cmd" << endl;
        break;
    }

  }


}

void Review::PrintMatch(Type type, int row) {
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


bool Review::FitType(Type type, int size) {
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

