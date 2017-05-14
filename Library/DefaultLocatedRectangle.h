#pragma once

#include "I_LocatedRectangle.h"

namespace it
{
  class DefaultLocatedRectangle : public I_LocatedRectangle
  {
    PlanarPosition   const center_;
    PlanarPosition   const position_;
    PlanarDimensions const dimensions_;

    static PlanarPosition calculateCenter (PlanarDimensions const &, PlanarPosition const &);

  public:
    DefaultLocatedRectangle (const PlanarPosition&, const PlanarDimensions&);
    virtual const unsigned int& getWidth() const override;
    virtual const unsigned int& getHeight() const override;
    virtual bool contains (const PlanarPosition&) const override;
    virtual int const & getX() const override;
    virtual int const & getY() const override;
    virtual PlanarPosition const & getCenter() const override;
  };
}