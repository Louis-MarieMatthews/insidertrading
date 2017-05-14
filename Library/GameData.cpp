#include "GameData.h"

namespace it
{
  GameData::GameData() :
    companyBeingCleaned_ (nullptr),
    sec_ (PlanarPosition (500, 50), companies_, time_)
  {
    companies_.insert (new Company ("Lockheed Martin", playersMoney_, PlanarPosition (100, 100)));
    companies_.insert (new Company ("Sarif Industries", playersMoney_, PlanarPosition (300, 500)));
    companies_.insert (new Company ("Versalife", playersMoney_, PlanarPosition (600, 500)));
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



  ObservablePointer<Company> & GameData::getCompanyBeingCleaned()
  {
    return companyBeingCleaned_;
  }



  Sec & GameData::getSec()
  {
    return sec_;
  }



  void GameData::setCompanyBeingCleaned (Company * company)
  {
    companyBeingCleaned_.setPointer (company);
  }
}