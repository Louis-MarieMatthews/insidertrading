#pragma once

#include "I_BitmapView.h"
#include "DefaultObservableId.h"
#include "ViewData.h"
#include "GameMenuBar.h"
#include "I_ConstantObserver.h"
#include "GameData.h"
#include "CompanyIcon.h"
#include "SecIcon.h"
#include "DefaultContextualMenuBitmap.h"

namespace it
{
  class GameMenu : public I_BitmapView, public I_ConstantObserver
  {
    ALLEGRO_BITMAP *               bitmap_;
    std::set<CompanyIcon *>        companyIcons_;
    PlanarDimensions               dimensions_;
    GameData &                     gameData_;
    bool                           isLastFetchedBitmapUpToDate_;
    DefaultObservableId            observableId_;
    GameMenuBar                    menuBar_;
    I_BitmapView *                 next_; // TODO: needs to be const!!
    SecIcon                        secIcon_;
    ViewData &                     viewData_;
    static std::set<CompanyIcon *> getCompanyIcons (GameData &, DefaultContextualMenuBitmap * &);
    DefaultContextualMenuBitmap *  contextualMenu_;

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