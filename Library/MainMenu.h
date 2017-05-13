#pragma once

#include "I_BitmapView.h"
#include "MenuButton.h"
#include "DefaultObservableId.h"

namespace it
{
  class MainMenu : public I_BitmapView
  {
    ALLEGRO_BITMAP *    bitmap_;
    PlanarDimensions    dimensions_;
    bool                isLastFetchedBitmapUpToDate_;
    MenuButton          menuButton_;
    DefaultObservableId observableId_;


  public:
    MainMenu (PlanarDimensions const &);
    ~MainMenu();

    // Inherited via I_BitmapView
    virtual I_BitmapView * getNext() override;
    virtual void reset() override;
    virtual void processEvent (I_AllegroEventAdapter const &) override;
    virtual bool const & isLastFetchedBitmapUpToDate() const override;
    virtual ALLEGRO_BITMAP * fetchBitmap() override;

    // Inherited via I_BitmapView
    virtual I_ObservableId const & getObservableId() const override;
  };
}