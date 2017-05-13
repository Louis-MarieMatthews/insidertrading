#include "GameData.h"

namespace it
{
  GameData::GameData()
  {
    companies_.insert (Company ("Lockheed Martin", PlanarPosition (100, 100)));
    companies_.insert (Company ("Sarif Industries", PlanarPosition (300, 500)));
    companies_.insert (Company ("Versalife", PlanarPosition (600, 500)));
  }



  Time & GameData::getTime()
  {
    return time_;
  }



  PlayersMoney & GameData::getPlayersMoney()
  {
    return playersMoney_;
  }



  std::set<Company> const & GameData::getCompanies()
  {
    return companies_;
  }
}