#pragma once
#include "PlanarPosition.h"

namespace it
{
  class Company;

  class PlayerPosition : public PlanarPosition
  {
    Company & company_;

  public:
    PlayerPosition (PlayerPosition const &);
    PlayerPosition (Company &, int x, int y);
    Company & getCompany() const;
  };
}