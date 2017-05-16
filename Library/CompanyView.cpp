#include "CompanyView.h"

#include "DefaultGameData.h"
#include "FontFormat.h"

namespace it
{
  void CompanyView::stopObserving()
  {
    ObserverListSingleton::getInstance().removeObserver (mapBitmap_.getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (company_.getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (isPlayerInTheGame_.getObservableId(), *this);
  }



  CompanyView::CompanyView (Company & company, ViewData & viewData, PlanarDimensions const & dimensions) :
    mapBitmap_ (MapFormat (company.getMap(), dimensions), company.getMap(), PlanarPosition (0, 0)),
    company_ (company),
    companyMap_ (company.getMap()),
    dimensions_ (dimensions),
    isLastFetchedBitmapUpToDate_ (false),
    isPlayerInTheGame_ (viewData.getGameData().getPointer()->isPlayerInTheGame()),
    itemHeight_ (15),
    itemWidth_ (15),
    justOpened_ (true),
    mapFormat_ (company.getMap(), dimensions),
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
    justOpened_ = true;
    mapBitmap_.reset();
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
      al_draw_bitmap (mapBitmap_.fetchBitmap(), 0, 0, 0);

      FontFormat ff (20, 40, 40);

      //viewData_.getGameData().getSec().getInspectingDuration().getString().c_str()
      al_draw_text (ff.getFont(), al_map_rgb (0, 0, 0), dimensions_.getWidth() - ff.getXPadding(), ff.getYPadding(), ALLEGRO_ALIGN_RIGHT, viewData_.getGameData().getPointer()->getSec().getInspectingDuration().getString().c_str());

      al_set_target_bitmap (targetBitmap);
    }
    justOpened_ = false;
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
  }



  void CompanyView::close()
  {
    stopObserving();
  }



  void CompanyView::notifyObserver (I_ObservableId const & observableId)
  {
    if (&mapBitmap_.getObservableId() == &observableId) {
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