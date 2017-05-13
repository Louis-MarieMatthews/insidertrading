#pragma once

#include "allegro5\allegro.h"

#include "I_AllegroEventAdapter.h"

namespace it
{
  class DefaultAllegroEventAdapter : public I_AllegroEventAdapter
  {
    ALLEGRO_EVENT*  currentEvent_;
    bool currentLeftClickReleased_;
    bool previousLeftClickReleased_;
    bool currentEscapeKeyPressed_;
    bool previousEscapeKeyPressed_;
    ALLEGRO_EVENT_TYPE lastType_;
    PlanarPosition* currentPosition_;
    PlanarPosition* previousPosition_;
    bool isFpsFrame_;
    bool isNewSecond_;
    ALLEGRO_TIMER const * fpsTimer_;
    ALLEGRO_TIMER const * secondsTimer_;

  public:
    DefaultAllegroEventAdapter (ALLEGRO_TIMER const *, ALLEGRO_TIMER const *);
    virtual void update (ALLEGRO_EVENT const & event) override;
    virtual bool isCausedByAMouseMove() const override;
    virtual bool didTheMouseEnter (I_LocatedRectangle const &) const override;
    virtual bool didTheMouseLeave (I_LocatedRectangle const &) const override;
    virtual bool wasTheMouseLeftClicked() const override;
    virtual bool wasTheMouseLeftClickReleased() const override;
    virtual bool isMouseWithin (I_LocatedRectangle const &) const override;
    virtual PlanarPosition const & getMousePosition() const override;
    virtual bool wasEscapeKeyPressed() const override;
    virtual bool const & isFpsFrame() const override;

    // Inherited via I_AllegroEventAdapter
    virtual bool const & isNewSecond() const override;
  };
}