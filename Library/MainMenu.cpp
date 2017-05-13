#include "MainMenu.h"

namespace it
{
  MainMenu::MainMenu (PlanarDimensions const & dimensions) :
    bitmap_ (nullptr),
    dimensions_ (dimensions),
    isLastFetchedBitmapUpToDate_ (false)
  {
  }



  MainMenu::~MainMenu()
  {
    if (bitmap_ != nullptr) {
      al_destroy_bitmap (bitmap_);
    }
  }



  I_BitmapView * MainMenu::getNext()
  {
    return this;
  }



  void MainMenu::reset()
  {
    
  }



  void MainMenu::processEvent (I_AllegroEventAdapter const &)
  {
  }



  bool const & MainMenu::isLastFetchedBitmapUpToDate() const
  {
    return isLastFetchedBitmapUpToDate_;
  }



  ALLEGRO_BITMAP * MainMenu::fetchBitmap()
  {
    if (bitmap_ == nullptr) {
      bitmap_ = al_create_bitmap (dimensions_.getWidth(), dimensions_.getHeight());
      al_set_target_bitmap (bitmap_);
      al_clear_to_color (al_map_rgb (0, 0, 255));
    }
    return bitmap_;
  }
}