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
    sec_ (*this, PlanarPosition (500, 50), companies_, gameTime_),
    programTime_ (time)
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
    ObserverListSingleton::getInstance().addObserver (isPlayerInTheGame_.getObservableId(), *this);
    if (isPlayerInTheGame_) {
      ObserverListSingleton::getInstance().addObserver (programTime_.getObservableId(), *this);
    }
    sec_.startInspecting();
  }



  DefaultGameData::~DefaultGameData()
  {
    ObserverListSingleton::getInstance().removeObserver (isPlayerInTheGame_.getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (programTime_.getObservableId(), *this);
    for (auto c : companies_) {
      delete c;
    }
    sec_.stopInspecting();
  }



  Duration const & DefaultGameData::getTime()
  {
    return gameTime_;
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



  void DefaultGameData::notifyObserver (I_ObservableId const & observableId)
  {
    if (&programTime_.getObservableId() == &observableId) {
      gameTime_.tick();
    }
    else if (&isPlayerInTheGame_.getObservableId() == &observableId) {
      if (isPlayerInTheGame_) {
        ObserverListSingleton::getInstance().addObserver (programTime_.getObservableId(), *this);
      }
      else {
        ObserverListSingleton::getInstance().removeObserver (programTime_.getObservableId(), *this);
      }
    }
  }
}