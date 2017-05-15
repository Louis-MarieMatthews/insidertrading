#include "CompanyIcon.h"

#include "ObserverListSingleton.h"
#include "ContextualMenuBitmapSingleton.h"

namespace it
{
  void CompanyIcon::setHovered (bool const & isHovered)
  {
    if (isHovered_ != isHovered) {
      isHovered_ = isHovered;
      isLastFetchedBitmapUpToDate_ = false;
      ObserverListSingleton::getInstance().notifyObservers (observableId_);
    }
  }



  CompanyIcon::CompanyIcon (Company & company, I_GameData & gameData, PlanarPosition const & position) :
    bitmapHovered_ (al_load_bitmap ("../gamefiles/images/interactivebitmap/hovered/company.bmp")),
    bitmapNotHovered_ (al_load_bitmap ("../gamefiles/images/interactivebitmap/nothovered/company.bmp")),
    company_ (company),
    contextualMenu_ (company, gameData),
    isLastFetchedBitmapUpToDate_ (false),
    position_ (position),
    rectangle_ (position, PlanarDimensions (200, 200)) // TODO: hard-coded values!
  {
  }



  CompanyIcon::~CompanyIcon()
  {
    al_destroy_bitmap (bitmapHovered_);
    al_destroy_bitmap (bitmapNotHovered_);
  }



  Company const & CompanyIcon::getCompany()
  {
    return company_;
  }



  I_ObservableId const & CompanyIcon::getObservableId() const
  {
    return observableId_;
  }



  void CompanyIcon::reset()
  {
  }



  void CompanyIcon::processEvent (I_AllegroEventAdapter const & e)
  {
    if (e.isCausedByAMouseMove()) {
      if (e.didTheMouseEnter (*this)) {
        setHovered (true);
      }
      else if (e.didTheMouseLeave (*this)) {
        setHovered (false);
      }
    }
    else if (e.wasTheMouseLeftClickReleased() && e.isMouseWithin(*this)) {
      ContextualMenuBitmapSingleton::getInstance().setContextualMenu (&contextualMenu_, position_);
    }
  }



  bool const & CompanyIcon::isLastFetchedBitmapUpToDate() const
  {
    return isLastFetchedBitmapUpToDate_;
  }



  ALLEGRO_BITMAP * CompanyIcon::fetchBitmap()
  {
    isLastFetchedBitmapUpToDate_ = true;
    if (isHovered_) {
      return bitmapHovered_;
    }
    else {
      return bitmapNotHovered_;
    }
  }



  unsigned int const & CompanyIcon::getWidth() const
  {
    return rectangle_.getWidth();
  }



  unsigned int const & CompanyIcon::getHeight() const
  {
    return rectangle_.getHeight();
  }



  bool CompanyIcon::contains (PlanarPosition const & position) const
  {
    return rectangle_.contains (position);
  }



  int const & CompanyIcon::getX() const
  {
    return position_.getX();
  }



  int const & CompanyIcon::getY() const
  {
    return position_.getY();
  }



  PlanarPosition const & CompanyIcon::getCenter() const
  {
    return rectangle_.getCenter();
  }



  PlanarPosition const & CompanyIcon::getPosition() const
  {
    return position_;
  }



  bool operator< (CompanyIcon const & c0, CompanyIcon const & c1)
  {
    return &c0 < &c1;
  }
}