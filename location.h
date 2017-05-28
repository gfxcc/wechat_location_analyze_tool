#ifndef WECHAT_ANALYZE_LOCATION_H_
#define WECHAT_ANALYZE_LOCATION_H_

#include <string>
#include <memory>
#include <vector>
/*
class Location {
public:

  enum class Level {country, province, city, county};

  static std::unique_ptr<Location> BuildTree(std::string path);

  Location(std::string name, std::string region_code, Level level, std::weak_ptr<Location> parent):
    name_(name), region_code_(region_code), level_(level), parent_(parent) {}
  void AddOffspring(std::string name, std::string region_code, Level level) {
    offspring_.emplace_back(new Location(name, region_code, level, this));
  }

private:
  std::string name_, region_code_;
  Level level_;
  std::weak_ptr<Location> parent_;
  std::vector<std::shared_ptr<Location>> offspring_;
};
*/
#endif // WECHAT_ANALYZE_LOCATION_H_
