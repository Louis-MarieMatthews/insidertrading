#pragma once

#include "I_BitmapView.h"
#include "DefaultObservableId.h"
#include "ViewData.h"
#include "GameMenuBar.h"
#include "I_ConstantObserver.h"

namespace it
{
  class GameMenu : public I_BitmapView, public I_ConstantObserver
  {
    ALLEGRO_BITMAP *    bitmap_;
    PlanarDimensions    dimensions_;
    bool                isLastFetchedBitmapUpToDate_;
    DefaultObservableId observableId_;
    GameMenuBar         menuBar_;
    I_BitmapView *      next_; // TODO: needs to be const!!
    ViewData &          viewData_;

  public:
    GameMenu (ViewData &, PlanarDimensions const &);
    ~GameMenu();

    // Inherited via I_BitmapView
    virtual I_ObservableId const & getObservableId() const override;
    virtual void reset() override;
    virtual void processEvent (I_AllegroEventAdapter const &) override;
    virtual bool const & isLastFetchedBitmapUpToDate() const override;
    virtual ALLEGRO_BITMAP * fetchBitmap() override;
    virtual I_BitmapView * getNext() override;

    // Inherited via I_ConstantObserver
    virtual void notifyObserver (I_ObservableId const &) override;
  };


}