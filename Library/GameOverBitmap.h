#pragma once

#include "I_LocatedInteractiveBitmap.h"
#include "DefaultObservableId.h"
#include "DefaultLocatedRectangle.h"
#include "FontFormat.h"

namespace it
{
  class GameOverBitmap : public I_LocatedInteractiveBitmap
  {
    ALLEGRO_BITMAP *        bitmap_;
    FontFormat              fontFormat_; // TODO: maybe move this in ViewData?
    bool                    isLastFetchedBitmapUpToDate_;
    DefaultObservableId     observableId_;
    PlanarPosition          position_;
    DefaultLocatedRectangle rectangle_;
    std::string             text_;

    static PlanarDimensions calculateDimensions (PlanarDimensions const &);
    static PlanarPosition calculatePosition (PlanarDimensions const &);

  public:
    GameOverBitmap (PlanarDimensions const &);
    ~GameOverBitmap();

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
  };
}