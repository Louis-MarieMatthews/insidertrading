#include "CompanyView.h"

#include "DefaultGameData.h"
#include "FontFormat.h"
#include "Sec.h"

namespace it
{
  void CompanyView::stopObserving()
  {
    ObserverListSingleton::getInstance().removeObserver (mapBitmap_.getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (company_.getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (isPlayerInTheGame_.getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (menuBar_.getObservableId(), *this);
  }



  PlanarPosition CompanyView::getMapBitmapPosition()
  {
    return PlanarPosition (0, MENU_BAR_HEIGHT_);
  }



  PlanarDimensions CompanyView::getMapBitmapDimensions (PlanarDimensions const & windowsDimensions)
  {
    return PlanarDimensions (windowsDimensions.getWidth(), windowsDimensions.getHeight() - MENU_BAR_HEIGHT_);
  }



  PlanarDimensions CompanyView::getMenuBarDimensions (PlanarDimensions const & dimensions)
  {
    return PlanarDimensions (dimensions.getWidth(), MENU_BAR_HEIGHT_);
  }



  PlanarPosition CompanyView::getMenuBarPosition (PlanarDimensions const & position)
  {
    return PlanarPosition (0, 0);
  }



  CompanyView::CompanyView (Company & company, ViewData & viewData, PlanarDimensions const & dimensions) :
    company_ (company),
    companyMap_ (company.getMap()),
    dimensions_ (dimensions),
    isLastFetchedBitmapUpToDate_ (false),
    isPlayerInTheGame_ (viewData.getGameData().getPointer()->isPlayerInTheGame()),
    mapBitmap_ (MapFormat (company.getMap(), getMapBitmapDimensions (dimensions)), company.getMap(), getMapBitmapPosition()),
    menuBar_ (*viewData.getGameData().getPointer(), getMenuBarDimensions (dimensions), getMenuBarPosition (dimensions)),
    next_ (this),
    playerPosition_ (viewData.getGameData().getPointer()->getPlayerPosition()),
    viewData_ (viewData)
  {
  }



  CompanyView::~CompanyView()
  {
    stopObserving();
    if (bitmap_ != nullptr) {
      al_destroy_bitmap (bitmap_);
    }
  }



  I_ObservableId const & CompanyView::getObservableId() const
  {
    return observableId_;
  }



  void CompanyView::reset()
  {
    next_ = this;
    mapBitmap_.reset();
    menuBar_.reset();
  }



  void CompanyView::processEvent (I_AllegroEventAdapter const & e)
  {
    if (e.wasEscapeKeyPressed()) {
      next_ = viewData_.getGameView();
    }
    else if (e.wasUpKeyReleased()) {
      companyMap_.movePlayer (up);
    }
    else if (e.wasDownKeyReleased()) {
      companyMap_.movePlayer (down);
    }
    else if (e.wasLeftKeyReleased()) {
      companyMap_.movePlayer (left);
    }
    else if (e.wasRightKeyReleased()) {
      companyMap_.movePlayer (right);
    }
    else {
    }
    menuBar_.processEvent (e);
  }



  bool const & CompanyView::isLastFetchedBitmapUpToDate() const
  {
    return isLastFetchedBitmapUpToDate_;
  }



  ALLEGRO_BITMAP * CompanyView::fetchBitmap()
  {
    if (!isLastFetchedBitmapUpToDate_) {
      ALLEGRO_BITMAP * targetBitmap (al_get_target_bitmap());

      
      if (bitmap_ != nullptr) {
        al_destroy_bitmap (bitmap_);
      }
      bitmap_ = al_create_bitmap (dimensions_.getWidth(), dimensions_.getHeight());
      al_set_target_bitmap (bitmap_);
      al_draw_bitmap (menuBar_.fetchBitmap(), menuBar_.getX(), menuBar_.getY(), 0);
      al_draw_bitmap (mapBitmap_.fetchBitmap(), mapBitmap_.getX(), mapBitmap_.getY(), 0);

      al_set_target_bitmap (targetBitmap);
    }
    return bitmap_;
  }



  I_BitmapView * CompanyView::getNext()
  {
    return next_;
  }



  void CompanyView::open()
  {
    ObserverListSingleton::getInstance().addObserver (mapBitmap_.getObservableId(), *this);
    ObserverListSingleton::getInstance().addObserver (company_.getObservableId(), *this);
    ObserverListSingleton::getInstance().addObserver (isPlayerInTheGame_.getObservableId(), *this);
    ObserverListSingleton::getInstance().addObserver (menuBar_.getObservableId(), *this);
  }



  void CompanyView::close()
  {
    stopObserving();
  }



  void CompanyView::notifyObserver (I_ObservableId const & observableId)
  {
    if (&mapBitmap_.getObservableId() == &observableId ||
        &menuBar_.getObservableId() == &observableId) {
      isLastFetchedBitmapUpToDate_ = false;
    }
    else if (&company_.getObservableId() == &observableId) {
      next_ = viewData_.getGameView();
    }
    else if (&isPlayerInTheGame_.getObservableId() == &observableId) {
      if (!isPlayerInTheGame_.getValue()) {
        next_ = viewData_.getGameView();
      }
    }
  }
}