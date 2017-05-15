#include "DefaultGameData.h"

namespace it
{
  DefaultGameData::DefaultGameData() :
    companyBeingCleaned_ (nullptr),
    isPlayerInTheGame_ (true),
    playerPosition_ (0, 0),
    sec_ (*this, PlanarPosition (500, 50), companies_, time_)
  {
    companies_.insert (new Company (*this, "Lockheed Martin", playersMoney_, PlanarPosition (100, 100)));
    companies_.insert (new Company (*this, "Sarif Industries", playersMoney_, PlanarPosition (300, 500)));
    companies_.insert (new Company (*this, "Versalife", playersMoney_, PlanarPosition (600, 500)));
  }



  DefaultGameData::~DefaultGameData()
  {
    for (auto c : companies_) {
      delete c;
    }
  }



  Duration & DefaultGameData::getTime()
  {
    return time_;
  }



  PlayerBalance & DefaultGameData::getPlayersMoney()
  {
    return playersMoney_;
  }



  std::set<Company *> const & DefaultGameData::getCompanies()
  {
    return companies_;
  }



  ObservablePointer<Company> & DefaultGameData::getCompanyBeingCleaned()
  {
    return companyBeingCleaned_;
  }



  Sec & DefaultGameData::getSec()
  {
    return sec_;
  }



  PlanarPosition & DefaultGameData::getPlayerPosition()
  {
    return playerPosition_;
  }



  void DefaultGameData::setCompanyBeingCleaned (Company * company)
  {
    companyBeingCleaned_.setPointer (company);
  }



  Boolean & DefaultGameData::isPlayerInTheGame()
  {
    return isPlayerInTheGame_;
  }
}