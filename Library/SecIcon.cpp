#include "SecIcon.h"

#include "BitmapLoadingException.h"
#include "ObserverListSingleton.h"

namespace it
{
  SecIcon::SecIcon (Sec & sec) :
    mapBitmap_ (al_load_bitmap ("../gamefiles/images/interactivebitmap/sec.bmp")),
    isLastFetchedBitmapUpToDate_ (false),
    position_ (sec.getPosition()),
    rectangle_ (sec.getPosition(), PlanarDimensions (200, 200)),
    sec_ (sec)
  {
    if (mapBitmap_ == nullptr) {
      throw BitmapLoadingException();
    }
  }



  SecIcon::~SecIcon()
  {
  }



  I_ObservableId const & SecIcon::getObservableId() const
  {
    return observableId_;
  }



  void SecIcon::reset()
  {
  }



  void SecIcon::processEvent (I_AllegroEventAdapter const & e)
  {
  }



  bool const & SecIcon::isLastFetchedBitmapUpToDate() const // TODO: should be deleted. Instead, parents would be notified with the observer pattern?
  {
    return isLastFetchedBitmapUpToDate_;
  }



  ALLEGRO_BITMAP * SecIcon::fetchBitmap()
  {
    return mapBitmap_;
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