#pragma once

#include "DefaultObservableId.h"
#include "FontFormat.h"
#include "I_LocatedInteractiveBitmap.h"

namespace it
{
  class MenuButton : public I_LocatedInteractiveBitmap
  {
    ALLEGRO_BITMAP *    bitmap_;
    FontFormat          fontFormat_;
    DefaultObservableId observableId_;
    PlanarPosition      position_;
    std::string         text_;

  public:
    MenuButton (PlanarPosition const &, std::string const &);
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