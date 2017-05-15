#pragma once

#include "DefaultObservableId.h"
#include "I_BitmapView.h"
#include "ViewData.h"
#include "Company.h"

namespace it
{
  class CompanyView : public I_BitmapView
  {
    ALLEGRO_BITMAP *         bitmap_;
    ALLEGRO_BITMAP *         bitmapMap_;
    bool                     bitmapMapUpToDate_;
    Company &                company_;
    CompanyMap &             companyMap_;
    PlanarDimensions const & dimensions_;
    bool                     isLastFetchedBitmapUpToDate_;
    unsigned short const     itemHeight_;
    unsigned short const     itemWidth_;
    bool                     justOpened_;
    I_BitmapView *           next_;
    DefaultObservableId      observableId_;
    PlanarPosition &         playerPosition_;
    ViewData &               viewData_;
    void generateMapBitmap();

  public:
    CompanyView (Company & company, ViewData &, PlanarDimensions const &);
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