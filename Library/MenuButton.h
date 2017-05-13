#pragma once

#include "DefaultObservableId.h"
#include "I_LocatedInteractiveBitmap.h"

namespace it
{
  class MenuButton : public I_LocatedInteractiveBitmap
  {
    ALLEGRO_BITMAP *    bitmap_;
    PlanarPosition      position_;
    DefaultObservableId observableId_;

  public:
    MenuButton (PlanarPosition const &);
    ~MenuButton();

    virtual bool const & isLastFetchedBitmapUpToDate() const override;
    virtual PlanarPosition const & getPosition() const override;
    virtual ALLEGRO_BITMAP * fetchBitmap() override;
    virtual void processEvent (I_AllegroEventAdapter const &) override;
    virtual void reset() override;

    // Inherited via I_LocatedInteractiveBitmap
    virtual I_ObservableId const & getObservableId() const override;
  };
}