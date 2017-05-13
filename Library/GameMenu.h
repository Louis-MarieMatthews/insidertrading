#pragma once

#include "I_BitmapView.h"
#include "DefaultObservableId.h"
#include "ViewData.h"

namespace it
{
  class GameMenu : public I_BitmapView
  {
    ALLEGRO_BITMAP *    bitmap_;
    PlanarDimensions    dimensions_;
    bool                isLastFetchedBitmapUpToDate_;
    DefaultObservableId observableId_;
    I_BitmapView *      next_; // TODO: needs to be const!!
    ViewData &          viewData_;

  public:
    GameMenu (ViewData &, PlanarDimensions const &);

    // Inherited via I_BitmapView
    virtual I_ObservableId const & getObservableId() const override;
    virtual void reset() override;
    virtual void processEvent (I_AllegroEventAdapter const &) override;
    virtual bool const & isLastFetchedBitmapUpToDate() const override;
    virtual ALLEGRO_BITMAP * fetchBitmap() override;
    virtual I_BitmapView * getNext() override;
  };


}