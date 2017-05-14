#include "GameData.h"

namespace it
{
  GameData::GameData() :
    sec_ (PlanarPosition (500, 50), companies_, time_)
  {
    companies_.insert (new Company ("Lockheed Martin", PlanarPosition (100, 100)));
    companies_.insert (new Company ("Sarif Industries", PlanarPosition (300, 500)));
    companies_.insert (new Company ("Versalife", PlanarPosition (600, 500)));
  }



  GameData::~GameData()
  {
    for (auto c : companies_) {
      delete c;
    }
  }



  Duration & GameData::getTime()
  {
    return time_;
  }



  PlayerBalance & GameData::getPlayersMoney()
  {
    return playersMoney_;
  }



  std::set<Company *> const & GameData::getCompanies()
  {
    return companies_;
  }



  Sec & GameData::getSec()
  {
    return sec_;
  }
}