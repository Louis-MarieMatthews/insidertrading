#include "GameData.h"

namespace it
{
  GameData::GameData() :
    sec_ (PlanarPosition (500, 50), companies_, time_)
  {
    companies_.insert (Company ("Lockheed Martin", PlanarPosition (100, 100)));
    companies_.insert (Company ("Sarif Industries", PlanarPosition (300, 500)));
    companies_.insert (Company ("Versalife", PlanarPosition (600, 500)));
  }



  Duration & GameData::getTime()
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



  Sec & GameData::getSec()
  {
    return sec_;
  }
}