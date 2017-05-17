#include "CompanyIcon.h"

#include "allegro5\allegro_font.h"

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
    bitmapHovered_ (al_load_bitmap ("../gamefiles/images/interactivebitmap/hovered/company.tga")),
    bitmapNotHovered_ (al_load_bitmap ("../gamefiles/images/interactivebitmap/nothovered/company.tga")),
    company_ (company),
    contextualMenu_ (company, gameData),
    fontFormat_ (PlanarDimensions (WIDTH_, HEIGHT_), small),
    isHovered_ (false),
    isLastFetchedBitmapUpToDate_ (false),
    position_ (position),
    rectangle_ (position, PlanarDimensions (200, 200)) // TODO: hard-coded values!
  {
  }



  CompanyIcon::~CompanyIcon()
  {
    if (bitmap_ != nullptr) {
      al_destroy_bitmap (bitmap_);
    }
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
    if (!isLastFetchedBitmapUpToDate_) {
      ALLEGRO_BITMAP * targetBitmap (al_get_target_bitmap());

      if (bitmap_ != nullptr) {
        al_destroy_bitmap (bitmap_);
      }
      bitmap_ = al_create_bitmap (WIDTH_, HEIGHT_);
      al_set_target_bitmap (bitmap_);
      if (isHovered_) {
        al_draw_bitmap (bitmapHovered_, 0, 0, 0);
      }
      else {
        al_draw_bitmap (bitmapNotHovered_, 0, 0, 0);
      }
      al_draw_text (fontFormat_.getFont(), al_map_rgb (255, 255, 255), 200 + fontFormat_.getXPadding(), 0, ALLEGRO_ALIGN_LEFT, company_.getDividendString().c_str());

      al_set_target_bitmap (targetBitmap);
    }
    isLastFetchedBitmapUpToDate_ = true;
    return bitmap_;
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
}