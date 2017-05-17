#include "Company.h"

#include "ObserverListSingleton.h"
#include "InsufficientPlayerBalanceException.h"

namespace it
{
  Company::Company (I_GameData & gameData, unsigned long long const & dividend, std::string const & mapFilename, std::string const & name, PlanarPosition const & position) :
    dividend_ (dividend),
    hasInsiders_ (false),
    insiderCost_ (dividend * 10),
    lastSecond_ (-1),
    map_ (gameData, *this, mapFilename),
    name_ (name),
    playerBalance_ (gameData.getPlayersMoney()),
    position_ (position),
    time_ (gameData.getTime())
  {
    ObserverListSingleton::getInstance().addObserver (map_.getDocuments().getObservableId(), *this);
  }



  Company::~Company()
  {
    ObserverListSingleton::getInstance().removeObserver (time_.getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (map_.getDocuments().getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObservable (observableId_);
  }



  CompanyMap & Company::getMap()
  {
    return map_;
  }



  std::string const & Company::getName() const
  {
    return name_;
  }



  PlanarPosition const & Company::getPosition() const
  {
    return position_;
  }



  unsigned long long const & Company::getInsiderCost() const
  {
    return insiderCost_;
  }



  std::string Company::getDividendString() const
  {
    return std::string ("$" + std::to_string (dividend_));
  }



  Boolean const & Company::hasInsiders() const
  {
    return hasInsiders_;
  }



  void Company::addInsiders()
  {
    if (playerBalance_ >= insiderCost_) {
      playerBalance_ -= insiderCost_;
      hasInsiders_ = true;
      ObserverListSingleton::getInstance().addObserver (time_.getObservableId(), *this);
      ObserverListSingleton::getInstance().notifyObservers (observableId_);
    }
    else {
      throw InsufficientPlayerBalanceException();
    }
  }



  void Company::removeInsiders()
  {
    hasInsiders_ = false;
    ObserverListSingleton::getInstance().removeObserver (time_.getObservableId(), *this);
    ObserverListSingleton::getInstance().notifyObservers (observableId_);
  }



  I_ObservableId const & Company::getObservableId() const
  {
    return observableId_;
  }



  void Company::notifyObserver (I_ObservableId const & observableId)
  {
    if (&time_.getObservableId() == &observableId && hasInsiders_) {
      if (lastSecond_ != time_.getSecond()) {
        lastSecond_ = time_.getSecond();
        playerBalance_+= (dividend_);
      }
    }
    else if (&map_.getDocuments().getObservableId() == &observableId) {
      if (map_.getDocuments().getSize() == 0) {
        removeInsiders();
      }
    }
  }
}