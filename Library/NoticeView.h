#pragma once

#include "I_BitmapView.h"

#include "DefaultObservableId.h"
#include "Duration.h"
#include "FontFormat.h"
#include "I_ConstantObserver.h"
#include "ViewData.h"

namespace it
{
  class NoticeView : public I_BitmapView
  {
    ALLEGRO_BITMAP *         bitmap_;
    PlanarDimensions         dimensions_;
    float                    displayTime_;
    ALLEGRO_COLOR            fontColor_;
    FontFormat               fontFormat_;
    bool                     isLastFetchedBitmapUpToDate_;
    I_BitmapView *           next_;
    DefaultObservableId      observableId_;
    std::vector<std::string> lines_;
    ViewData &               viewData_;
    float                    timeItsBeenOn_;
    I_BitmapView *           after_;

    void updateColor();

  public:
    NoticeView (I_BitmapView *, PlanarDimensions const &, std::vector<std::string> const &, ViewData &);
    ~NoticeView();

    // Inherited via I_BitmapView
    virtual I_ObservableId const & getObservableId() const override;
    virtual void reset() override;
    virtual void processEvent(I_AllegroEventAdapter const &) override;
    virtual bool const & isLastFetchedBitmapUpToDate() const override;
    virtual ALLEGRO_BITMAP * fetchBitmap() override;
    virtual I_BitmapView * getNext() override;
  };
}