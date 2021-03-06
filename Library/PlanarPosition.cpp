#include "PlanarPosition.h"

#include "ObserverListSingleton.h"
#include <cmath>

namespace it
{
  PlanarPosition::PlanarPosition(const int& x, const int& y) :
    x_ (x),
    y_ (y)
  {
  }



  PlanarPosition::~PlanarPosition()
  {
    ObserverListSingleton::getInstance().removeObservable (observableId_);
  }



  const int& PlanarPosition::getX() const
  {
    return x_;
  }



  const int& PlanarPosition::getY() const
  {
    return y_;
  }



  void PlanarPosition::setX (int const & x)
  {
    x_ = x;
    ObserverListSingleton::getInstance().notifyObservers (observableId_);
  }



  void PlanarPosition::setY (int const & y)
  {
    y_ = y;
    ObserverListSingleton::getInstance().notifyObservers (observableId_);
  }



  void PlanarPosition::update (PlanarPosition const & position)
  {
    x_ = position.getX();
    y_ = position.getY();
    ObserverListSingleton::getInstance().notifyObservers (observableId_);
  }



  bool PlanarPosition::isNearby (PlanarPosition const & position, int const & distance) const
  {
    bool nearbyX (std::abs (x_ - position.getX()) <= distance);
    bool nearbyY (std::abs (y_ - position.getY()) <= distance);
    return nearbyX && nearbyY;
  }



  bool PlanarPosition::operator== (const PlanarPosition& position) const
  {
    return x_ == position.getX() && y_ == position.getY();
  }



  bool PlanarPosition::operator!= (const PlanarPosition& position) const
  {
    return !(*this == position);
  }



  I_ObservableId const & PlanarPosition::getObservableId() const
  {
    return observableId_;
  }
}