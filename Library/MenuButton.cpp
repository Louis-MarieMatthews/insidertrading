#include "MenuButton.h"

#include "allegro5\allegro_ttf.h"

namespace it
{
  MenuButton::MenuButton (PlanarPosition const & position, std::string const & text) :
    bitmap_ (nullptr),
    dimensions_ (500, 200),
    fontFormat_ (dimensions_, TEXT_PADDING_),
    position_ (position),
    text_ (text)
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




  void MenuButton::processEvent (I_AllegroEventAdapter const &)
  {
  }



  bool const & MenuButton::isLastFetchedBitmapUpToDate() const
  {
    return bitmap_ != nullptr;
  }



  PlanarPosition const & MenuButton::getPosition() const
  {
    return position_;
  }



  ALLEGRO_BITMAP * MenuButton::fetchBitmap()
  {
    if (bitmap_ == nullptr) {
      ALLEGRO_BITMAP * targetBitmap (al_get_target_bitmap());
      bitmap_ = al_create_bitmap (dimensions_.getWidth(), dimensions_.getHeight()); // TODO: hard-coded values
      al_set_target_bitmap (bitmap_);
      al_clear_to_color (al_map_rgb (255, 255, 255));
      al_draw_text (fontFormat_.getFont(), al_map_rgb (0, 0, 0), fontFormat_.getXPadding(),  fontFormat_.getYPadding(), ALLEGRO_ALIGN_LEFT, text_.c_str());
      al_set_target_bitmap (targetBitmap);
    }
    return bitmap_;
  }



  I_ObservableId const & MenuButton::getObservableId() const
  {
    return observableId_;
  }
}