#pragma once

#include "I_ContextualMenu.h"
#include "I_Rectangle.h"
#include "PlanarDimensions.h"
#include "PlanarPosition.h"

namespace it
{
  class I_LocatedRectangle : public I_Rectangle
  {
  public:
    virtual ~I_LocatedRectangle() {};
    virtual bool contains (PlanarPosition const &) const = 0;
    virtual int const & getX() const = 0;
    virtual int const & getY() const = 0;
  };
}