#include "GameOverBitmap.h"

#include "allegro5\allegro_font.h"

namespace it
{
  GameOverBitmap::GameOverBitmap (PlanarDimensions const & dimensions) :
    fontFormat_ (calculateDimensions (dimensions)),
    isLastFetchedBitmapUpToDate_ (false),
    position_ (calculatePosition (dimensions)),
    rectangle_ (calculatePosition (dimensions), calculateDimensions (dimensions)),
    text_ ("Game Over!")
  {
  }



  GameOverBitmap::~GameOverBitmap()
  {
    if (mapBitmap_ != nullptr) {
      al_destroy_bitmap (mapBitmap_);
    }
  }



  I_ObservableId const & GameOverBitmap::getObservableId() const
  {
    return observableId_;
  }



  PlanarDimensions it::GameOverBitmap::calculateDimensions (PlanarDimensions const & dimensions)
  {
    return PlanarDimensions (dimensions.getWidth(), dimensions.getHeight() / 2);
  }

  PlanarPosition GameOverBitmap::calculatePosition (PlanarDimensions const &)
  {
    return PlanarPosition (0, 100); // TODO:
  }



  void GameOverBitmap::reset()
  {
  }



  void GameOverBitmap::processEvent (I_AllegroEventAdapter const &)
  {
  }



  bool const & GameOverBitmap::isLastFetchedBitmapUpToDate() const
  {
    return isLastFetchedBitmapUpToDate_;
  }



  ALLEGRO_BITMAP * GameOverBitmap::fetchBitmap()
  {
    if (!isLastFetchedBitmapUpToDate_) {
      ALLEGRO_BITMAP * targetBitmap (al_get_target_bitmap());


      if (mapBitmap_ != nullptr) {
        al_destroy_bitmap (mapBitmap_);
      }
      mapBitmap_ = al_create_bitmap (rectangle_.getWidth(), rectangle_.getHeight());
      al_set_target_bitmap (mapBitmap_);
      al_clear_to_color (al_map_rgb (0, 0, 0));
      al_draw_text (fontFormat_.getFont(), al_map_rgb (255, 255, 255), rectangle_.getWidth() / 2,  fontFormat_.getYPadding(), ALLEGRO_ALIGN_CENTER, text_.c_str());



      isLastFetchedBitmapUpToDate_ = true;
      al_set_target_bitmap (targetBitmap);
    }
    return mapBitmap_;
  }



  unsigned int const & GameOverBitmap::getWidth() const
  {
    return rectangle_.getWidth();
  }



  unsigned int const & GameOverBitmap::getHeight() const
  {
    return rectangle_.getHeight();
  }



  bool GameOverBitmap::contains (PlanarPosition const & position) const
  {
    return rectangle_.contains (position);
  }



  int const & GameOverBitmap::getX() const
  {
    return rectangle_.getX();
  }



  int const & GameOverBitmap::getY() const
  {
    return rectangle_.getY();
  }



  PlanarPosition const & GameOverBitmap::getCenter() const
  {
    return rectangle_.getCenter();
  }



  PlanarPosition const & GameOverBitmap::getPosition() const
  {
    return position_;
  }
}