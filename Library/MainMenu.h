#pragma once

#include "DefaultObservableId.h"
#include "I_BitmapView.h"
#include "I_ConstantObserver.h"
#include "MenuButton.h"
#include "ViewData.h"
#include "GameMenuBar.h"

namespace it
{
  class MainMenu : public I_BitmapView, public I_ConstantObserver
  {
    ALLEGRO_BITMAP *    mapBitmap_;
    MenuButton          buttonQuit_;
    MenuButton          buttonPlay_;
    PlanarDimensions    dimensions_;
    bool                isLastFetchedBitmapUpToDate_;
    I_BitmapView *      next_;
    DefaultObservableId observableId_;

    static const unsigned BUTTON_WIDTH_ {500};
    static const unsigned TOP_MARGIN_ {200};
    static const unsigned BUTTON_BOTTOM_MARGIN_ {100};

    static PlanarPosition getButtonPosition (PlanarDimensions const &, unsigned short const &);

  public:
    MainMenu (ViewData &, PlanarDimensions const &);
    ~MainMenu();

    // Inherited via I_BitmapView
    virtual I_BitmapView * getNext() override;
    virtual void reset() override;
    virtual void processEvent (I_AllegroEventAdapter const &) override;
    virtual bool const & isLastFetchedBitmapUpToDate() const override;
    virtual ALLEGRO_BITMAP * fetchBitmap() override;

    // Inherited via I_BitmapView
    virtual I_ObservableId const & getObservableId() const override;

    // Inherited via I_ConstantObserver
    virtual void notifyObserver(I_ObservableId const &) override;
  };
}