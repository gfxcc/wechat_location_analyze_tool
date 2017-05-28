#include <unordered_map>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdlib>
#include <ctime>

#include "wechat.h"
#include "location.h"
#include "trie.h"
#include "util.h"
#include "statistic.h"
#include "review.h"

using namespace std;

// main process func
void Process(Trie& trie, std::vector<WechatAccount>& wechat_accounts);

void PrintTime() {
  time_t now = time(0);

  // convert now to string form
  char* dt = ctime(&now);

  cout << "The local date and time is: " << dt << endl;
}

int main(int argc, char const * argv[]) {
  PrintTime();

  string dir_path = "./data";

  // load location from dirctory
  vector<pair<string, wstring>> locations;
  if (OperateEveryFileUnderPath(dir_path, locations) != 0) {
    cout << "EXIT: read location file failed" << endl;
    exit (EXIT_FAILURE);
  }
  cout << "read " << locations.size() << " locations from file" << endl;

  // build Trie
  Trie trie(locations);

  // load wechat accounts from file
  vector<WechatAccount> wechat_accounts;
  string file_path;
  if (argc == 2)
    file_path = string(argv[1]);
  else
    file_path = "/home/yong/Documents/connectplus/biz_all_2017-05-23";

  if (ReadWechatAccountFromFile(file_path, wechat_accounts, 10000) != 0) {
    cout << "EXIT: read wechat file failed" << endl;
    exit (EXIT_FAILURE);
  }

  cout << "read " << wechat_accounts.size() << " wechat accounts from file" << endl;

  // start to match wechat account with location
  cout << "start to process..." << endl;
  Process(trie, wechat_accounts);

  // static
  Statistic statis(wechat_accounts);
  statis.Process();
  statis.Print();

  PrintTime();

  // waiting for review
  cout << "Processing Finished; Please enter review command" << endl;
  cout << "q         exit" << endl;
  cout << "i         print statistic information" << endl;
  cout << "n num     print num empty match" << endl;
  cout << "m num     print num match" << endl;
  cout << "s num     print num single match" << endl;
  cout << "d num     print num double match" << endl;
  cout << "u num     print num multi match" << endl;

  Review review(wechat_accounts);

  while (true) {
    cout << "> ";
    string cmd;
    cin >> cmd;
    if (cmd == "q")
      break;
    switch(cmd[0]) {
      case 'i':
        statis.Print();
        break;
      case 'n':
        cin >> cmd;
        review.PrintMatch(Review::Type::NoMatch, stoi(cmd));
        break;
      case 'm':
        cin >> cmd;
        review.PrintMatch(Review::Type::Match, stoi(cmd));
        break;
      case 's':
        cin >> cmd;
        review.PrintMatch(Review::Type::SingleMatch, stoi(cmd));
        break;
      case 'd':
        cin >> cmd;
        review.PrintMatch(Review::Type::DoubleMatch, stoi(cmd));
        break;
      case 'u':
        cin >> cmd;
        review.PrintMatch(Review::Type::MultiMatch,stoi(cmd));
        break;
      default:
        cout << "wrong cmd" << endl;
        break;
    }

  }
  return 0;
}

void Process(Trie& trie, std::vector<WechatAccount>& wechat_accounts) {
  for (auto& account : wechat_accounts) {
    cout << "name:" << account.GetInfo(WechatAccount::Field::name) << endl;
    cout << "intro:" << account.GetInfo(WechatAccount::Field::intro) << endl;

    unordered_map<string, string> locations;
    // process name
    string name = account.GetInfo(WechatAccount::Field::name);
    for (int i = 0; i < name.size(); i += 3) {
      int len = min(10, static_cast<int>(name.size()) - i);
      string keyword = name.substr(i, len);
      cout << keyword << endl;
      auto ret = trie.find(s2ws(keyword));
      for (auto& ele : ret) {
        locations[ele.first] = ele.second;
      }
    }

    // process intro
    string intro = account.GetInfo(WechatAccount::Field::intro);
    for (int i = 0; i < intro.size(); i += 3) {
      int len = min(10, static_cast<int>(intro.size()) - i);
      string keyword = intro.substr(i, len);
      auto ret = trie.find(s2ws(keyword));
      for (auto& ele : ret) {
        locations[ele.first] = ele.second;
      }
    }

    // insert locations into acount
    for (auto& location : locations) {
      account.Insert(location);
    }


    cout << locations.size() << " regions matched successed" << endl;
    for (auto& location : locations) {
      cout << location.first << ":" << location.second << endl;
    }

    cout << "---------------------------------------------------" << endl;
    //auto ret = trie.find(account.GetInfo(WechatAccount::Field::name));
    //wechat_accounts.locations_.push_back(ret.begin(), ret.end());
  }
}

