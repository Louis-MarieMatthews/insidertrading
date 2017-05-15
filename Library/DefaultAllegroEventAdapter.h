#pragma once

#include "allegro5\allegro.h"

#include "I_AllegroEventAdapter.h"

namespace it
{
  class DefaultAllegroEventAdapter : public I_AllegroEventAdapter
  {
    bool                  currentEscapeKeyPressed_;
    ALLEGRO_EVENT*        currentEvent_;
    bool                  currentLeftClickReleased_;
    PlanarPosition*       currentPosition_;
    bool                  isFpsFrame_;
    bool                  isNewCentisecond_;
    bool                  isMouseButtonPressed_;
    bool                  isUpKeyPressed_;
    bool                  isDownKeyPressed_;
    bool                  isLeftKeyPressed_;
    bool                  isRightKeyPressed_;
    ALLEGRO_EVENT_TYPE    lastType_;
    bool                  previousLeftClickReleased_;
    bool                  previousEscapeKeyPressed_;
    PlanarPosition*       previousPosition_;
    ALLEGRO_TIMER const * timerFps_;
    ALLEGRO_TIMER const * timerCentiseconds_;
    bool                  wasUpKeyReleased_;
    bool                  wasDownKeyReleased_;
    bool                  wasLeftKeyReleased_;
    bool                  wasRightKeyReleased_;

    void updateCurrentEvent (ALLEGRO_EVENT const &);

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
    virtual bool const & isNewCentisecond() const override;
    virtual bool const & isMouseButtonPressed() const override;

    // Inherited via I_AllegroEventAdapter
    virtual bool const & isDownKeyPressed() const override;
    virtual bool const & isLeftKeyPressed() const override;
    virtual bool const & isRightKeyPressed() const override;
    virtual bool const & isUpKeyPressed() const override;

    // Inherited via I_AllegroEventAdapter
    virtual bool const & wasUpKeyReleased() const override;
    virtual bool const & wasDownKeyReleased() const override;
    virtual bool const & wasLeftKeyReleased() const override;
    virtual bool const & wasRightKeyReleased() const override;
  };
}