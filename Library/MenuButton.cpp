#include "MenuButton.h"

#include "allegro5\allegro_ttf.h"

#include "ObserverListSingleton.h"

namespace it
{
  void MenuButton::setHovered (const bool & isHovered)
  {
    if (isHovered_ != isHovered) {
      isHovered_ = isHovered;
      isLastFetchedBitmapUpToDate_ = false;
      ObserverListSingleton::getInstance().notifyObservers (observableId_);
    }
  }



  MenuButton::MenuButton (PlanarPosition const & position, std::string const & text, I_BitmapView * & next, I_BitmapView * & target) :
    bitmap_ (nullptr),
    dimensions_ (WIDTH_, HEIGHT_),
    fontFormat_ (dimensions_, TEXT_PADDING_),
    isLastFetchedBitmapUpToDate_ (false),
    position_ (position),
    rectangle_ (position, dimensions_),
    target_ (target),
    text_ (text),
    next_ (next)
  {
  }



  MenuButton::~MenuButton()
  {
    if (bitmap_ != nullptr) {
      al_destroy_bitmap (bitmap_);
    }
  }



  void MenuButton::reset()
  {
  }




  void MenuButton::processEvent (I_AllegroEventAdapter const & e)
  {
    // TODO: add if firstDraw && e.isTheMouseWithin
    if (e.isCausedByAMouseMove()) {
      if (e.didTheMouseEnter (*this)) {
        setHovered (true);
      }
      else if (e.didTheMouseLeave (*this)) {
        setHovered (false);
      }
    }
    else if (e.wasTheMouseLeftClickReleased()) {
      if (e.isMouseWithin (*this)) {
        next_ = target_;
      }
    }
  }



  bool const & MenuButton::isLastFetchedBitmapUpToDate() const
  {
    return isLastFetchedBitmapUpToDate_;
  }



  PlanarPosition const & MenuButton::getPosition() const
  {
    return position_;
  }



  ALLEGRO_BITMAP * MenuButton::fetchBitmap()
  {
    if (!isLastFetchedBitmapUpToDate_) {
      if (bitmap_ != nullptr) {
        al_destroy_bitmap (bitmap_);
      }
      bitmap_ = al_create_bitmap (dimensions_.getWidth(), dimensions_.getHeight()); // TODO: hard-coded values
      ALLEGRO_BITMAP * targetBitmap (al_get_target_bitmap());
      al_set_target_bitmap (bitmap_);
      if (isHovered_) {
        al_clear_to_color (al_map_rgb (40, 40, 40));
      }
      else {
        al_clear_to_color (al_map_rgb (20, 20, 20));
      }
      al_draw_text (fontFormat_.getFont(), al_map_rgb (255, 255, 255), WIDTH_ / 2,  fontFormat_.getYPadding(), ALLEGRO_ALIGN_CENTER, text_.c_str());
      al_set_target_bitmap (targetBitmap);
      isLastFetchedBitmapUpToDate_ = true;
    }
    return bitmap_;
  }



  I_ObservableId const & MenuButton::getObservableId() const
  {
    return observableId_;
  }



  unsigned int const & MenuButton::getWidth() const
  {
    return rectangle_.getWidth();
  }



  unsigned int const & MenuButton::getHeight() const
  {
    return rectangle_.getHeight();
  }



  bool MenuButton::contains (PlanarPosition const & position) const
  {
    return rectangle_.contains (position);
  }



  int const & MenuButton::getX() const
  {
    return rectangle_.getX();
  }



  int const & MenuButton::getY() const
  {
    return rectangle_.getY();
  }



  PlanarPosition const & MenuButton::getCenter() const
  {
    return rectangle_.getCenter();
  }
}