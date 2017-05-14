#include "Company.h"

#include "ObserverListSingleton.h"
#include "InsufficientPlayerBalanceException.h"

namespace it
{
  Company::Company (std::string const & name, PlayerBalance & playerBalance, PlanarPosition const & position) :
    hasInsiders_ (false),
    name_ (name),
    playerBalance_ (playerBalance),
    position_ (position)
  {
  }



  Company::~Company()
  {
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



  bool const & Company::hasInsiders() const
  {
    return hasInsiders_;
  }



  void Company::addInsiders()
  {
    if (playerBalance_ >= insiderCost_) {
      playerBalance_ -= insiderCost_;
      hasInsiders_ = true;
      ObserverListSingleton::getInstance().notifyObservers (observableId_);
    }
    else {
      throw InsufficientPlayerBalanceException();
    }
  }



  void Company::removeInsiders()
  {
    hasInsiders_ = false;
    ObserverListSingleton::getInstance().notifyObservers (observableId_);
  }



  I_ObservableId const & Company::getObservableId() const
  {
    return observableId_;
  }



  bool operator< (Company const & c1, Company const & c2)
  {
    return c1.getName() < c2.getName();
  }
}