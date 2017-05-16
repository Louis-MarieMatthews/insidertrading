#include "InsiderTradingLegalNoticeView.h"

#include "allegro5\allegro_font.h"

namespace it
{
  void InsiderTradingLegalNoticeView::updateColor()
  {
    unsigned short color (-pow ((timeItsBeenOn_ - 2.5), 6) + 255);
    fontColor_ = al_map_rgb (color, color, color);
    isLastFetchedBitmapUpToDate_ = false;
  }



  InsiderTradingLegalNoticeView::InsiderTradingLegalNoticeView (PlanarDimensions const & dimensions, ViewData & viewData) :
    dimensions_ (dimensions),
    displayTime_ (5.0),
    fontColor_ (al_map_rgb (0, 0, 0)),
    fontFormat_ (dimensions, small),
    next_ (this),
    text_ ("Insider trading is illegal and severely punished in most countries."),
    viewData_ (viewData)
  {
  }



  InsiderTradingLegalNoticeView::~InsiderTradingLegalNoticeView()
  {
    if (bitmap_ != nullptr) {
      al_destroy_bitmap (bitmap_);
    }
  }



  I_ObservableId const & InsiderTradingLegalNoticeView::getObservableId() const
  {
    return observableId_;
  }



  void InsiderTradingLegalNoticeView::reset()
  {
    next_ = this;
    timeItsBeenOn_ = 0;
  }



  void InsiderTradingLegalNoticeView::processEvent (I_AllegroEventAdapter const & e)
  {
    if (timeItsBeenOn_ > displayTime_) {
      next_ = viewData_.getMainMenu();
    }
    else if (e.isNewCentisecond()) {
      timeItsBeenOn_ += 0.01;
      updateColor();
    }
  }



  bool const & InsiderTradingLegalNoticeView::isLastFetchedBitmapUpToDate() const
  {
    return isLastFetchedBitmapUpToDate_;
  }



  ALLEGRO_BITMAP * InsiderTradingLegalNoticeView::fetchBitmap()
  {
    if (!isLastFetchedBitmapUpToDate_) {
      ALLEGRO_BITMAP * targetBitmap (al_get_target_bitmap());


      if (bitmap_ != nullptr) {
        al_destroy_bitmap (bitmap_);
      }
      bitmap_ = al_create_bitmap (dimensions_.getWidth(), dimensions_.getHeight());
      al_set_target_bitmap (bitmap_);
      al_clear_to_color (al_map_rgb (0, 0, 0));
      al_draw_text (fontFormat_.getFont(), fontColor_, dimensions_.getWidth() / 2, fontFormat_.getYPadding(), ALLEGRO_ALIGN_CENTER, text_.c_str());


      al_set_target_bitmap (targetBitmap);
    }
    return bitmap_;
  }



  I_BitmapView * InsiderTradingLegalNoticeView::getNext()
  {
    return next_;
  }
}