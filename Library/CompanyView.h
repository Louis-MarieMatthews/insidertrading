#pragma once

#include "Company.h"
#include "DefaultObservableId.h"
#include "GameMenuBar.h"
#include "I_BitmapView.h"
#include "MapFormat.h"
#include "MapBitmap.h"
#include "ViewData.h"

namespace it
{
  class CompanyView : public I_BitmapView, public I_ConstantObserver
  {
    static unsigned short const MENU_BAR_HEIGHT_ {50};

    ALLEGRO_BITMAP *            bitmap_;
    Company &                   company_;
    CompanyMap &                companyMap_;
    Duration const &            countDown_;
    PlanarDimensions const &    dimensions_;
    bool                        isLastFetchedBitmapUpToDate_;
    Boolean const &             isPlayerInTheGame_;
    MapBitmap                   mapBitmap_;
    GameMenuBar                 menuBar_;
    I_BitmapView *              next_;
    DefaultObservableId         observableId_;
    PlanarPosition &            playerPosition_;
    ViewData &                  viewData_;

    void stopObserving();
    static PlanarPosition getMapBitmapPosition ();
    static PlanarDimensions getMapBitmapDimensions (PlanarDimensions const &);
    static PlanarDimensions getMenuBarDimensions (PlanarDimensions const &);
    static PlanarPosition getMenuBarPosition (PlanarDimensions const &);

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
    virtual void open() override;
    virtual void close() override;

    // Inherited via I_ConstantObserver
    virtual void notifyObserver (I_ObservableId const &) override;
  };
}