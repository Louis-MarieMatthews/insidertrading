#include "MenuButton.h"

namespace it
{
  MenuButton::MenuButton (PlanarPosition const & position) :
    bitmap_ (nullptr),
    position_ (position)
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
      bitmap_ = al_create_bitmap (500, 100); // TODO: hard-coded values
      al_set_target_bitmap (bitmap_);
      al_clear_to_color (al_map_rgb (255, 255, 255));
      al_set_target_bitmap (targetBitmap);
    }
    return bitmap_;
  }



  I_ObservableId const & MenuButton::getObservableId() const
  {
    return observableId_;
  }
}