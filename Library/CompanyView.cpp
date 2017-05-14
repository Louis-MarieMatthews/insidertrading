#include "CompanyView.h"

namespace it
{
  CompanyView::CompanyView (ViewData & viewData, PlanarDimensions const & dimensions) :
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

      al_set_target_bitmap (targetBitmap);
    }
    return bitmap_;
  }



  I_BitmapView * CompanyView::getNext()
  {
    return next_;
  }
}