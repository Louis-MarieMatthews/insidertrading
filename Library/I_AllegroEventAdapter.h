#pragma once

#include "../packages/Allegro.5.2.2.1/build/native/include/allegro5/allegro.h"
#include "I_LocatedRectangle.h"

namespace it
{
  class I_AllegroEventAdapter
  {
  public:
    virtual ~I_AllegroEventAdapter() {};
    virtual void update (ALLEGRO_EVENT const &) = 0;
    virtual bool isCausedByAMouseMove() const = 0;
    virtual bool didTheMouseEnter (I_LocatedRectangle const &) const = 0;
    virtual bool didTheMouseLeave (I_LocatedRectangle const &) const = 0;
    virtual bool wasTheMouseLeftClicked() const = 0;
    virtual bool wasTheMouseLeftClickReleased() const = 0;
    virtual bool isMouseWithin (I_LocatedRectangle const &) const = 0;
    virtual PlanarPosition const & getMousePosition() const = 0;
    virtual bool wasEscapeKeyPressed() const = 0;
    virtual bool const & isFpsFrame() const = 0;
    virtual bool const & isNewSecond() const = 0;
    virtual bool const & isNewCentisecond() const = 0;
  };
}