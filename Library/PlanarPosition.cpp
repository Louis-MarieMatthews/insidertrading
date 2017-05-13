#include "PlanarPosition.h"

namespace it
{
  PlanarPosition::PlanarPosition(const int& x, const int& y) :
    x_ (x),
    y_ (y)
  {
  }



  const int& PlanarPosition::getX() const
  {
    return x_;
  }



  const int& PlanarPosition::getY() const
  {
    return y_;
  }



  bool PlanarPosition::operator== (const PlanarPosition& position) const
  {
    return x_ == position.getX() && y_ == position.getY();
  }



  bool PlanarPosition::operator!= (const PlanarPosition& position) const
  {
    return !(*this == position);
  }
}