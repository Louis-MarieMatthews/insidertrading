#include "CompanyView.h"

namespace it
{
  void CompanyView::generateMapBitmap()
  {
    ALLEGRO_BITMAP * targetBitmap (al_get_target_bitmap());


    if (bitmapMap_ != nullptr) {
      al_destroy_bitmap (bitmapMap_);
    }
    bitmapMap_ = al_create_bitmap (companyMap_.getNumberOfRows() * itemWidth_, companyMap_.getNumberOfColums() * itemHeight_);
    al_set_target_bitmap (bitmapMap_);
    for (unsigned short r (0); r < companyMap_.getNumberOfRows(); r++) {
      for (unsigned short c (0); c < companyMap_.getNumberOfColums(); c++) {
        ALLEGRO_BITMAP * item (al_create_bitmap (itemWidth_, itemHeight_)); // TODO: hard-coded values
        al_set_target_bitmap (item);
        if (companyMap_.getItem (r, c).isTraversable()) {
          al_clear_to_color (al_map_rgb (0, 0, 0));
        }
        else {
          al_clear_to_color (al_map_rgb (255, 255, 255));
        }
        al_set_target_bitmap (bitmapMap_);
        al_draw_bitmap (item, r * itemWidth_, c * itemHeight_, 0); // TODO: hard-coded values
        al_destroy_bitmap (item);
      }
    }
    bitmapMapUpToDate_ = true;


    al_set_target_bitmap (targetBitmap);
  }



  CompanyView::CompanyView (Company & company, ViewData & viewData, PlanarDimensions const & dimensions) :
    bitmapMapUpToDate_ (false),
    company_ (company),
    companyMap_ (company.getMap()),
    dimensions_ (dimensions),
    isLastFetchedBitmapUpToDate_ (false),
    itemHeight_ (15),
    itemWidth_ (15),
    justOpened_ (true),
    next_ (this),
    playerPosition_ (viewData.getGameData().getPlayerPosition()),
    viewData_ (viewData)
  {
  }



  CompanyView::~CompanyView()
  {
    if (bitmap_ != nullptr) {
      al_destroy_bitmap (bitmap_);
    }
    if (bitmapMap_ != nullptr) {
      al_destroy_bitmap (bitmapMap_);
    }
  }



  I_ObservableId const & CompanyView::getObservableId() const
  {
    return observableId_;
  }



  void CompanyView::reset()
  {
    next_ = this;
    justOpened_ = true;
  }



  void CompanyView::processEvent (I_AllegroEventAdapter const & e)
  {
    if (e.wasEscapeKeyPressed()) {
      next_ = viewData_.getGameView();
    }
    else if (e.wasUpKeyReleased()) {
      companyMap_.movePlayer (up);
    }
    else if (e.wasDownKeyReleased()) {
      companyMap_.movePlayer (down);
    }
    else if (e.wasLeftKeyReleased()) {
      companyMap_.movePlayer (left);
    }
    else if (e.wasRightKeyReleased()) {
      companyMap_.movePlayer (right);
    }
    else {
    }
  }



  bool const & CompanyView::isLastFetchedBitmapUpToDate() const
  {
    return isLastFetchedBitmapUpToDate_;
  }



  ALLEGRO_BITMAP * CompanyView::fetchBitmap()
  {
    if (justOpened_) {
      playerPosition_ = companyMap_.getPlayerEntryPoint();
    }
    if (!isLastFetchedBitmapUpToDate_) {
      ALLEGRO_BITMAP * targetBitmap (al_get_target_bitmap());

      if (bitmap_ != nullptr) {
        al_destroy_bitmap (bitmap_);
      }
      bitmap_ = al_create_bitmap (dimensions_.getWidth(), dimensions_.getWidth());
      al_set_target_bitmap (bitmap_);
      al_clear_to_color (al_map_rgb (100, 100, 0));
      
      if (!bitmapMapUpToDate_) {
        generateMapBitmap();
      }
      al_draw_bitmap (bitmapMap_, 0, 0, 0);
      

      ALLEGRO_BITMAP * player (al_load_bitmap ("../gamefiles/images/player.bmp")); // TODO: hard-coded values
      al_draw_bitmap (player, playerPosition_.getX() * itemWidth_, playerPosition_.getY() * itemHeight_, 0);
      al_destroy_bitmap (player);

      al_set_target_bitmap (targetBitmap);
    }
    justOpened_ = false;
    return bitmap_;
  }



  I_BitmapView * CompanyView::getNext()
  {
    return next_;
  }
}