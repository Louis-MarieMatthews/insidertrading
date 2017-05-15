#pragma once
#include "PlanarPosition.h"

namespace it
{
  class I_CompanyMapItem
  {
  public:
    virtual ~I_CompanyMapItem() {};
    virtual bool const & isTraversable() const = 0;
    virtual bool const & isDocument() const = 0;
    virtual PlanarPosition const & getPosition() const = 0;
  };
}