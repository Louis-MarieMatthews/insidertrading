#pragma once

#include "DefaultObservableId.h"
#include "I_LocatedInteractiveBitmap.h"
#include "I_ConstantObserver.h"
#include "DefaultLocatedRectangle.h"
#include "Sec.h"

namespace it
{
  class SecIcon : public I_LocatedInteractiveBitmap, public I_ConstantObserver
  {
    ALLEGRO_BITMAP *        bitmap_;
    DefaultObservableId     observableId_;
    bool                    isLastFetchedBitmapUpToDate_;
    PlanarPosition          position_;
    DefaultLocatedRectangle rectangle_;
    Sec &                   sec_;

  public:
    SecIcon (Sec &);
    ~SecIcon();

    // Inherited via I_LocatedInteractiveBitmap
    virtual I_ObservableId const & getObservableId() const override;
    virtual void reset() override;
    virtual void processEvent (I_AllegroEventAdapter const &) override;
    virtual bool const & isLastFetchedBitmapUpToDate() const override;
    virtual ALLEGRO_BITMAP * fetchBitmap() override;
    virtual unsigned int const & getWidth() const override;
    virtual unsigned int const & getHeight() const override;
    virtual bool contains (PlanarPosition const &) const override;
    virtual int const & getX() const override;
    virtual int const & getY() const override;
    virtual PlanarPosition const & getPosition() const override;

    // Inherited via I_ConstantObserver
    virtual void notifyObserver(I_ObservableId const &) override;
  };
}