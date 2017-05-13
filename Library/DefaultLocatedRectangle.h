#pragma once

#include "I_LocatedRectangle.h"

namespace it
{
  class DefaultLocatedRectangle : public I_LocatedRectangle
  {
    PlanarPosition   position_;
    PlanarDimensions dimensions_;
  public:
    DefaultLocatedRectangle (const PlanarPosition&, const PlanarDimensions&);
    virtual const unsigned int& getWidth() const override;
    virtual const unsigned int& getHeight() const override;
    virtual bool contains (const PlanarPosition&) const override;
    virtual const int& getX() const override;
    virtual const int& getY() const override;
  };
}