#pragma once

#include "DefaultObservableId.h"
#include "I_BitmapView.h"
#include "ViewData.h"

namespace it
{
  class CompanyView : public I_BitmapView
  {
    ALLEGRO_BITMAP *         bitmap_;
    PlanarDimensions const & dimensions_;
    bool                     isLastFetchedBitmapUpToDate_;
    I_BitmapView *           next_;
    DefaultObservableId      observableId_;
    ViewData &         viewData_;

  public:
    CompanyView (ViewData &, PlanarDimensions const &);
    ~CompanyView();

    // Inherited via I_BitmapView
    virtual I_ObservableId const & getObservableId() const override;
    virtual void reset() override;
    virtual void processEvent (I_AllegroEventAdapter const &) override;
    virtual bool const & isLastFetchedBitmapUpToDate() const override;
    virtual ALLEGRO_BITMAP * fetchBitmap() override;
    virtual I_BitmapView * getNext() override;
  };
}