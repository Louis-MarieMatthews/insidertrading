#include "PlayerPosition.h"

namespace it
{
  PlayerPosition::PlayerPosition (PlayerPosition const & position) :
    company_ (position.getCompany()),
    PlanarPosition (position.getX(), position.getY())
  {
  }



  PlayerPosition::PlayerPosition (Company & company, int x, int y) :
    company_ (company),
    PlanarPosition (x, y)
  {
  }



  Company & PlayerPosition::getCompany() const
  {
    return company_;
  }
}