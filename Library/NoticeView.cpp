#include "NoticeView.h"

#include "allegro5\allegro_font.h"

namespace it
{
  void NoticeView::updateColor()
  {
    unsigned short color (-pow ((timeItsBeenOn_ - 2.5), 6) + 255);
    fontColor_ = al_map_rgb (color, color, color);
    isLastFetchedBitmapUpToDate_ = false;
  }



  NoticeView::NoticeView (I_BitmapView * after, PlanarDimensions const & dimensions, std::vector<std::string> const & lines, ViewData & viewData) :
    after_ (after),
    dimensions_ (dimensions),
    displayTime_ (5.0),
    fontColor_ (al_map_rgb (0, 0, 0)),
    fontFormat_ (dimensions, small),
    lines_ (lines),
    next_ (this),
    viewData_ (viewData)
  {
  }



  NoticeView::~NoticeView()
  {
    if (bitmap_ != nullptr) {
      al_destroy_bitmap (bitmap_);
    }
  }



  I_ObservableId const & NoticeView::getObservableId() const
  {
    return observableId_;
  }



  void NoticeView::reset()
  {
    next_ = this;
    timeItsBeenOn_ = 0;
  }



  void NoticeView::processEvent (I_AllegroEventAdapter const & e)
  {
    if (timeItsBeenOn_ > displayTime_) {
      next_ = after_;
    }
    else if (e.isNewCentisecond()) {
      timeItsBeenOn_ += 0.01;
      updateColor();
    }
  }



  bool const & NoticeView::isLastFetchedBitmapUpToDate() const
  {
    return isLastFetchedBitmapUpToDate_;
  }



  ALLEGRO_BITMAP * NoticeView::fetchBitmap()
  {
    if (!isLastFetchedBitmapUpToDate_) {
      ALLEGRO_BITMAP * targetBitmap (al_get_target_bitmap());


      if (bitmap_ != nullptr) {
        al_destroy_bitmap (bitmap_);
      }
      bitmap_ = al_create_bitmap (dimensions_.getWidth(), dimensions_.getHeight());
      al_set_target_bitmap (bitmap_);
      al_clear_to_color (al_map_rgb (0, 0, 0));

      unsigned short i (0);
      for (auto l : lines_) {
        al_draw_text (fontFormat_.getFont(), fontColor_, dimensions_.getWidth() / 2, fontFormat_.getYPadding() + i * fontFormat_.getFontSize(), ALLEGRO_ALIGN_CENTER, l.c_str());
        i++;
      }


      al_set_target_bitmap (targetBitmap);
    }
    return bitmap_;
  }



  I_BitmapView * NoticeView::getNext()
  {
    return next_;
  }



  void NoticeView::open()
  {
  }



  void NoticeView::close()
  {
  }
}