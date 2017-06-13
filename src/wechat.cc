#include "wechat.h"

#include <json.hpp>

using namespace std;
using json = nlohmann::json;

int WechatAccount::size_intro_ = 0;
int WechatAccount::size_name_ = 0;

string WechatAccount::max_name_ = "";
string WechatAccount::max_intro_ = "";

WechatAccount::WechatAccount(const std::string& str) {
  boost::split(infos_, str, boost::is_any_of("\t"));
  if (IsValid()) {
    int size_name = static_cast<int>(infos_[Field::name].size()),
        size_intro = static_cast<int>(infos_[Field::intro].size());
    if (size_name > size_name_) {
      size_name_ = size_name;
      max_name_ = infos_[Field::name];
    }
    if (size_intro > size_intro_) {
      size_intro_ = size_intro;
      max_intro_ = infos_[Field::intro];
    }
  }
}

std::string WechatAccount::GetInfo(Field f) const {
  return infos_[f];
}

void WechatAccount::Insert(const std::pair<std::string, std::string>& location) {
  regions_.emplace_back(location);
}

void WechatAccount::Print() const {
  std::cout << "--WechatAccount--" << std::endl;
  std::cout << "name:" << infos_[Field::name] << std::endl;
  std::cout << "intro:" << infos_[Field::intro] << std::endl;
  cout << infos_[uuid].size() << endl << infos_[name].size() << endl << infos_[intro].size() << endl;

  std::cout << "locations:" << regions_.size() << std::endl;
  for (auto& location : regions_) {
    std::cout << "        " << location.first << ":" << location.second << std::endl;
  }
  std::cout << std::endl;
}

bool WechatAccount::IsValid() const {
  return infos_.size() == 8 &&
    infos_[Field::uuid].size() <= 20 &&
    infos_[Field::name].size() <= 200 &&
    infos_[Field::intro].size() <= 500;
}

int WechatAccount::GetInfoSize() const {
  return infos_.size();
}

int WechatAccount::GetSizeOfRegion() const {
  return regions_.size();
}

void WechatAccount::Debug() const {
  for (auto& info : infos_)
    std::cout << info << std::endl;
  std::cout << std::endl;
}

string WechatAccount::GetJsonString() const {

  json regions;
  for (auto& region : regions_) {
    regions[region.first] = region.second;
  }

  json j;
  j["filed_0"] = infos_[field_0];
  j["uuid"] = infos_[uuid];
  j["name"] = infos_[name];
  j["filed_3"] = infos_[field_3];
  j["intro"] = infos_[intro];
  j["field_5"] = infos_[field_5];
  j["filed_6"] = infos_[field_6];
  j["date"] = infos_[date];
  j["regions"] = regions;
  return j.dump(2);
}
