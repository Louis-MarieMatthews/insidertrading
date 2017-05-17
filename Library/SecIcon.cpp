#include "SecIcon.h"

#include "BitmapLoadingException.h"
#include "ObserverListSingleton.h"

namespace it
{
  SecIcon::SecIcon (Sec & sec) :
    bitmapHovered_ (al_load_bitmap ("../gamefiles/images/interactivebitmap/hovered/sec.tga")),
    bitmapNotHovered_ (al_load_bitmap ("../gamefiles/images/interactivebitmap/nothovered/sec.tga")),
    isHovered_ (false),
    isLastFetchedBitmapUpToDate_ (false),
    position_ (sec.getPosition()),
    rectangle_ (sec.getPosition(), PlanarDimensions (200, 200)),
    sec_ (sec)
  {
  }



  SecIcon::~SecIcon()
  {
    if (bitmapHovered_ != nullptr) {
      al_destroy_bitmap (bitmapHovered_);
    }
    if (bitmapNotHovered_ != nullptr) {
      al_destroy_bitmap (bitmapNotHovered_);
    }
    if (bitmap_ != nullptr) {
      al_destroy_bitmap (bitmap_);
    }
  }



  I_ObservableId const & SecIcon::getObservableId() const
  {
    return observableId_;
  }



  void SecIcon::reset()
  {
    isHovered_ = false;
  }



  void SecIcon::processEvent (I_AllegroEventAdapter const & e)
  {
    if (e.didTheMouseEnter (*this)) {
      isHovered_ = true;
    }
    else if (e.didTheMouseLeave (*this)) {
      isHovered_ = false;
    }
  }



  bool const & SecIcon::isLastFetchedBitmapUpToDate() const // TODO: should be deleted. Instead, parents would be notified with the observer pattern?
  {
    return isLastFetchedBitmapUpToDate_;
  }



  ALLEGRO_BITMAP * SecIcon::fetchBitmap()
  {
    if (isHovered_) {
      return bitmapHovered_;
    }
    else {
      return bitmapNotHovered_;
    }
  }



  unsigned int const & SecIcon::getWidth() const
  {
    return rectangle_.getWidth();
  }



  unsigned int const & SecIcon::getHeight() const
  {
    return rectangle_.getHeight();
  }



  bool SecIcon::contains (PlanarPosition const & position) const
  {
    return rectangle_.contains (position);
  }



  int const & SecIcon::getX() const
  {
    return position_.getX();
  }



  int const & SecIcon::getY() const
  {
    return position_.getY();
  }



  PlanarPosition const & SecIcon::getCenter() const
  {
    return rectangle_.getCenter();
  }



  PlanarPosition const & SecIcon::getPosition() const
  {
    return position_;
  }



  void SecIcon::notifyObserver (I_ObservableId const & observableId)
  {
  }
}