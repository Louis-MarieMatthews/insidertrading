#pragma once

#include <string>

#include "PlanarPosition.h"

namespace it
{
  class Company
  {
    std::string    name_;
    PlanarPosition position_;

  public:
    Company (std::string const &, PlanarPosition const &);
    std::string const & getName() const;
    PlanarPosition const & getPosition() const;
  };

  bool operator< (Company const &, Company const &);
}