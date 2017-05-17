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
    static const unsigned           BUTTON_WIDTH_ {500};
    static const unsigned           TOP_MARGIN_ {200};
    static const unsigned           BUTTON_BOTTOM_MARGIN_ {100};

    ALLEGRO_BITMAP *                bitmap_;
    ALLEGRO_BITMAP *                bitmapBackground_;
    MenuButton                      buttonQuit_;
    MenuButton                      buttonNewGame1_;
    MenuButton                      buttonNewGame2_;
    MenuButton                      buttonNewGame3_;
    MenuButton                      buttonResumeGame_;
    PlanarDimensions                dimensions_;
    bool                            isLastFetchedBitmapUpToDate_;
    I_BitmapView *                  next_;
    DefaultObservableId             observableId_;
    ObservablePointer<I_GameData> & gameData_;
    ViewData &                      viewData_;


    void stopObserving();
    static PlanarPosition getButtonPosition (PlanarDimensions const &, unsigned short const &);

  public:
    MainMenu (ObservablePointer<I_GameData> &, ViewData &, PlanarDimensions const &);
    ~MainMenu();

    // Inherited via I_BitmapView
    virtual I_BitmapView * getNext() override;
    virtual void open() override;
    virtual void close() override;
    virtual void reset() override;
    virtual void processEvent (I_AllegroEventAdapter const &) override;
    virtual bool const & isLastFetchedBitmapUpToDate() const override;
    virtual ALLEGRO_BITMAP * fetchBitmap() override;
    virtual I_ObservableId const & getObservableId() const override;

    // Inherited via I_ConstantObserver
    virtual void notifyObserver(I_ObservableId const &) override;
  };
}