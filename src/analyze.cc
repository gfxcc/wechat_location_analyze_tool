//
// created by Yong Cao on May/28/2017
//


#include <iostream>
#include <vector>
#include <unistd.h>
#include <unordered_set>

#include "wechat.h"
#include "util.h"
#include "statistic.h"
#include "review.h"
#include "process.h"

using namespace std;

int main(int argc, char * const argv[]) {

  int row = INT_MAX;
  bool verbose = false;
  string path_region = "./data/",
         path_wechat = "/home/yong/Documents/connectplus/wechat/",
         path_output = "./output";

  // load argv
  char c;
  while ((c = getopt (argc, argv, "hr:w:l:v")) != -1) {
    switch (c)
    {
      case 'r':
        path_region = optarg;
        break;
      case 'w':
        path_wechat = optarg;
        break;
      case 'l':
        row = stoi(string(optarg));
        break;
      case 'v':
        verbose = true;
        break;
      case 'h':
        Usage();
        exit (EXIT_SUCCESS);
      default:
        cout << "Error: illgal argument" << endl;
        Usage();
        exit (EXIT_FAILURE);
    }
  }

  PrintDateTime();
  // load data from path
  vector<pair<string, wstring>> regions;
  vector<WechatAccount> wechat_accounts;
  unordered_set<string> st_wechat_uuid;

  if (LoadRegionDataFromPath(path_region, regions) != 0) {
    cout << "Error: " << path_region << " read region files failed, please check" << endl;
    exit (EXIT_FAILURE);
  }
  cout << "Info: " << regions.size() << " regions have been loaded" << endl;


  if (LoadWechatDataFromPath(path_wechat, wechat_accounts, st_wechat_uuid, row) != 0) {
    cout << "Error: " << path_wechat << " read wechat files failed, please check" << endl;
    exit (EXIT_FAILURE);
  }
  cout << "Info: " << wechat_accounts.size() << " wechat accounts have been loaded" << endl;

  // start to match wechat account with region
  cout << "Info: processing..." << endl;
  if (Process(wechat_accounts) != 0) {
    exit (EXIT_FAILURE);
  }

  DumpIntoFile(wechat_accounts);

  Statistic statis(wechat_accounts);
    statis.Process();
    statis.Print();

  if (verbose) {
    // review
    Review review(wechat_accounts, statis);
    review.Start();
  }
  PrintDateTime();
  return 0;
}


