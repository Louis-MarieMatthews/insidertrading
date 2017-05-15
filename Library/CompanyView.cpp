#include "CompanyView.h"

namespace it
{
  CompanyView::CompanyView (Company & company, ViewData & viewData, PlanarDimensions const & dimensions) :
    bitmap_ (MapFormat (company.getMap(), dimensions), company.getMap(), PlanarPosition (0, 0)),
    company_ (company),
    companyMap_ (company.getMap()),
    dimensions_ (dimensions),
    isLastFetchedBitmapUpToDate_ (false),
    itemHeight_ (15),
    itemWidth_ (15),
    justOpened_ (true),
    mapFormat_ (company.getMap(), dimensions),
    next_ (this),
    playerPosition_ (viewData.getGameData().getPlayerPosition()),
    viewData_ (viewData)
  {
    ObserverListSingleton::getInstance().addObserver (bitmap_.getObservableId(), *this);
  }



  CompanyView::~CompanyView()
  {
    ObserverListSingleton::getInstance().removeObserver (bitmap_.getObservableId(), *this);
  }



  I_ObservableId const & CompanyView::getObservableId() const
  {
    return observableId_;
  }



  void CompanyView::reset()
  {
    next_ = this;
    justOpened_ = true;
    bitmap_.reset();
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
    if (justOpened_) {
      playerPosition_ = companyMap_.getPlayerEntryPoint();
    }
    justOpened_ = false;
    return bitmap_.fetchBitmap();
  }



  I_BitmapView * CompanyView::getNext()
  {
    return next_;
  }



  void CompanyView::notifyObserver (I_ObservableId const & observableId)
  {
    if (&bitmap_.getObservableId() == &observableId) {
      isLastFetchedBitmapUpToDate_ = false;
    }
  }
}