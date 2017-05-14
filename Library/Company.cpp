#include "Company.h"

#include "ObserverListSingleton.h"

namespace it
{
  Company::Company (std::string const & name, PlanarPosition const & position) :
    hasInsiders_ (false),
    name_ (name),
    position_ (position)
  {
  }



  std::string const & Company::getName() const
  {
    return name_;
  }



  PlanarPosition const & Company::getPosition() const
  {
    return position_;
  }



  bool const & Company::hasInsiders() const
  {
    return hasInsiders_;
  }



  void Company::addInsiders()
  {

    hasInsiders_ = true;
    ObserverListSingleton::getInstance().notifyObservers (observableId_);
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