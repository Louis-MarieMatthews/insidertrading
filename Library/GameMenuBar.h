#pragma once

#include "I_LocatedInteractiveBitmap.h"
#include "DefaultObservableId.h"
#include "DefaultLocatedRectangle.h"
#include "I_GameData.h"
#include "I_ConstantObserver.h"
#include "FontFormat.h"

// TODO: make it inherit an abstract that implement getX(), getY() , getWidth(), getHeight() and getPosition()
namespace it
{
  class GameMenuBar : public I_LocatedInteractiveBitmap, public I_ConstantObserver
  {
    ALLEGRO_BITMAP *        mapBitmap_;
    FontFormat              fontFormat_;
    I_GameData &              gameData_;
    bool                    isLastFetchedBitmapUpToDate_;
    DefaultObservableId     observableId_;
    PlanarPosition          position_;
    DefaultLocatedRectangle rectangle_;

  public:
    GameMenuBar (I_GameData &, PlanarDimensions const & dimensions, PlanarPosition const & position);
    ~GameMenuBar();

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
    virtual PlanarPosition const & getCenter() const override;
    virtual PlanarPosition const & getPosition() const override;

    // Inherited via I_ConstantObserver
    virtual void notifyObserver (I_ObservableId const &) override;
  };
}