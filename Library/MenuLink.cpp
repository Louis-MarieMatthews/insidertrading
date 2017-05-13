#include "MenuLink.h"

#include "BitmapLoadingException.h"
#include "DefaultObservableId.h"
#include "ObserverListSingleton.h"

namespace it
{
  const PlanarDimensions MenuLink::dimensions_ (100, 100);



  MenuLink::MenuLink (const PlanarPosition& position, const std::string& filename, I_Menu*& menuNext, I_Menu* targetMenu) :
    bitmapHovered_ (al_load_bitmap (std::string ("../gamefiles/images/interactivebitmap/hovered/" + filename + ".bmp").c_str())),
    bitmapNotHovered_ (al_load_bitmap (std::string ("../gamefiles/images/interactivebitmap/nothovered/" + filename + ".bmp").c_str())),
    cachedBitmap_ (nullptr),
    firstFrame_ (true),
    isLastFetchedBitmapUpToDate_ (false),
    menuNext_ (menuNext),
    observableId_ (DefaultObservableId()),
    rectangle_ (position, dimensions_),
    targetMenu_ (targetMenu)
  {
    if (bitmapHovered_ == false || bitmapNotHovered_ == false) {
      throw BitmapLoadingException();
    }
  }



  MenuLink::~MenuLink()
  {
    al_destroy_bitmap (bitmapHovered_);
    al_destroy_bitmap (bitmapNotHovered_);
  }



  void MenuLink::reset()
  {
    if (firstFrame_ == false) {
      firstFrame_ = true;
      isLastFetchedBitmapUpToDate_ = false;
    }
  }



  const unsigned int& MenuLink::getWidth() const
  {
    return rectangle_.getWidth();
  }



  const unsigned int& MenuLink::getHeight() const
  {
    return rectangle_.getHeight();
  }



  bool MenuLink::contains (const PlanarPosition& position) const
  {
    return rectangle_.contains (position);
  }



  const int& MenuLink::getX() const
  {
    return rectangle_.getX();
  }



  const int& MenuLink::getY() const
  {
    return rectangle_.getY();
  }



  ALLEGRO_BITMAP* MenuLink::fetchBitmap()
  {
    if (!isLastFetchedBitmapUpToDate_) {
      if (hovered_) {
        cachedBitmap_ = bitmapHovered_;
      }
      else {
        cachedBitmap_ = bitmapNotHovered_;
      }
    }
    isLastFetchedBitmapUpToDate_ = true;
    return cachedBitmap_;
  }



  void MenuLink::processEvent (const I_AllegroEventAdapter* e)
  {
    if (firstFrame_) {
      if (e->isMouseWithin (*this)) {
        hovered_ = true;
      }
      else {
        hovered_ = false;
      }
      firstFrame_ = false;
    }
    else if (e->didTheMouseEnter (*this)) {
      hovered_ = true;
      isLastFetchedBitmapUpToDate_ = false;
      ObserverListSingleton::getInstance().notifyObservers (observableId_);
    }
    else if (e->didTheMouseLeave (*this)) {
      hovered_ = false;
      isLastFetchedBitmapUpToDate_ = false;
      ObserverListSingleton::getInstance().notifyObservers (observableId_);
    }
    else if (e->wasTheMouseLeftClickReleased() && e->isMouseWithin (*this)) {
      menuNext_ = targetMenu_;
    }
  }



  I_ObservableId const & MenuLink::getObservableId() const
  {
    return observableId_;
  }
}