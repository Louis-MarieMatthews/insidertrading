#include "Company.h"

namespace it
{
  Company::Company (std::string const & name, PlanarPosition const & position) :
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



  bool operator< (Company const & c1, Company const & c2)
  {
    return c1.getName() < c2.getName();
  }
}