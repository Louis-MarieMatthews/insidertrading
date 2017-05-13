#include "GameMenuBar.h"

namespace it
{
  GameMenuBar::GameMenuBar (PlanarDimensions const & dimensions, PlanarPosition const & position) :
    isLastFetchedBitmapUpToDate_ (false),
    position_ (position),
    rectangle_ (position, dimensions)
  {
  }



  GameMenuBar::~GameMenuBar()
  {
    if (bitmap_ != nullptr) {
      al_destroy_bitmap (bitmap_);
    }
  }



  I_ObservableId const & GameMenuBar::getObservableId() const
  {
    return observableId_;
  }



  void GameMenuBar::reset()
  {
  }



  void GameMenuBar::processEvent (I_AllegroEventAdapter const &)
  {
  }



  bool const & GameMenuBar::isLastFetchedBitmapUpToDate() const
  {
    return isLastFetchedBitmapUpToDate_;
  }



  ALLEGRO_BITMAP * GameMenuBar::fetchBitmap()
  {
    // fetchBitmap could be moved in an abstract class this class would inherit. It would call a function implement by this class to initialise the bitmap.
    if (!isLastFetchedBitmapUpToDate_) {
      if (bitmap_ != nullptr) {
        al_destroy_bitmap (bitmap_);
      }
      bitmap_ = al_create_bitmap (rectangle_.getWidth(), rectangle_.getHeight());
      ALLEGRO_BITMAP * targetBitmap (al_get_target_bitmap());
      al_set_target_bitmap (bitmap_);
      al_clear_to_color (al_map_rgb (0, 0, 0));
      al_set_target_bitmap (targetBitmap);
      isLastFetchedBitmapUpToDate_ = true;
    }
    return bitmap_;
  }



  unsigned int const & GameMenuBar::getWidth() const
  {
    return rectangle_.getWidth();
  }



  unsigned int const & GameMenuBar::getHeight() const
  {
    return rectangle_.getHeight();
  }



  bool GameMenuBar::contains (PlanarPosition const & position) const
  {
    return rectangle_.contains (position);
  }



  int const & GameMenuBar::getX() const
  {
    return rectangle_.getX();
  }



  int const & GameMenuBar::getY() const
  {
    return rectangle_.getY();
  }



  PlanarPosition const & GameMenuBar::getPosition() const
  {
    return position_;
  }
}