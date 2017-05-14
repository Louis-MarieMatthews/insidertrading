#include "CompanyView.h"

namespace it
{
  void CompanyView::displayMap() const
  {
    ALLEGRO_BITMAP * targetBitmap (al_get_target_bitmap());
    for (unsigned short r (0); r < companyMap_.getNumberOfRows(); r++) {
      for (unsigned short c (0); c < companyMap_.getNumberOfColums(); c++) {
        ALLEGRO_BITMAP * item (al_create_bitmap (5, 5)); // TODO: hard-coded values
        al_set_target_bitmap (item);
        if (companyMap_.getItem (r, c).isTraversable()) {
          al_clear_to_color (al_map_rgb (0, 0, 0));
        }
        else {
          al_clear_to_color (al_map_rgb (255, 255, 255));
        }
        al_set_target_bitmap (targetBitmap);
        al_draw_bitmap (item, r * 5, c * 5, 0); // TODO: hard-coded values
        al_destroy_bitmap (item);
      }
    }
  }



  CompanyView::CompanyView (Company & company, ViewData & viewData, PlanarDimensions const & dimensions) :
    company_ (company),
    companyMap_ (company.getMap()),
    dimensions_ (dimensions),
    isLastFetchedBitmapUpToDate_ (false),
    next_ (this),
    viewData_ (viewData)
  {
  }



  CompanyView::~CompanyView()
  {
    if (bitmap_ != nullptr) {
      al_destroy_bitmap (bitmap_);
    }
  }



  I_ObservableId const & CompanyView::getObservableId() const
  {
    return observableId_;
  }



  void CompanyView::reset()
  {
    next_ = this;
  }



  void CompanyView::processEvent (I_AllegroEventAdapter const & e)
  {
    if (e.wasEscapeKeyPressed()) {
      next_ = viewData_.getGameView();
    }
  }



  bool const & CompanyView::isLastFetchedBitmapUpToDate() const
  {
    return isLastFetchedBitmapUpToDate_;
  }



  ALLEGRO_BITMAP * CompanyView::fetchBitmap()
  {
    if (!isLastFetchedBitmapUpToDate_) {
      ALLEGRO_BITMAP * targetBitmap (al_get_target_bitmap());

      if (bitmap_ != nullptr) {
        al_destroy_bitmap (bitmap_);
      }
      bitmap_ = al_create_bitmap (dimensions_.getWidth(), dimensions_.getWidth());
      al_set_target_bitmap (bitmap_);
      al_clear_to_color (al_map_rgb (100, 100, 0));
      displayMap();
      al_set_target_bitmap (targetBitmap);
    }
    return bitmap_;
  }



  I_BitmapView * CompanyView::getNext()
  {
    return next_;
  }
}