#include "DefaultGameData.h"

#include "json.hpp"

#include <fstream>

using json = nlohmann::json;

namespace it
{
  DefaultGameData::DefaultGameData (Duration const & time, std::string const & gameFilename) :
    companyBeingCleaned_ (nullptr),
    isPlayerInTheGame_ (true),
    playerPosition_ (0, 0),
    sec_ (*this, PlanarPosition (500, 50), companies_, time),
    time_ (time)
  {
    std::ifstream f (std::string ("../gamefiles/games/" + gameFilename).c_str());
    json j;
    f >> j;
    std::set<std::string> const companyList = j.at ("companyList");
    for (auto e : companyList) {
      unsigned long long dividend = j.at ("companies").at (e).at ("dividend");
      std::string map = j.at ("companies").at (e).at ("map");
      std::string name = j.at ("companies").at (e).at ("name");
      int x = j.at ("companies").at (e).at ("position").at (0);
      int y = j.at ("companies").at (e).at ("position").at (1);
      companies_.insert (new Company (*this, dividend, map, name, PlanarPosition (x, y)));
    }
  }



  DefaultGameData::~DefaultGameData()
  {
    for (auto c : companies_) {
      delete c;
    }
  }



  Duration const & DefaultGameData::getTime()
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