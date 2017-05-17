#include "FontFormat.h"

#include "allegro5\allegro_ttf.h"

#include "AllegroInitializationException.h"

namespace it
{
  unsigned short FontFormat::getFontSize (PlanarDimensions const & dimensions, Style const & style)
  {
    if (style == large) {
      if (dimensions.getWidth() > dimensions.getHeight() * 10) {
        return round (dimensions.getHeight() * 0.90);
      }
      else {
        return round (dimensions.getHeight() * 0.40);
      }
    }
    else if (style == small) {
      return 20;
    }
  }



  unsigned short FontFormat::getYPadding (PlanarDimensions const & dimensions, Style const & style)
  {
    if (style == large) {
      if (dimensions.getWidth() > dimensions.getHeight() * 10) {
        return 0;
      }
      else {
        return round (dimensions.getHeight() * 0.30);
      }
    }
    else if (style == small) {
      return round ((dimensions.getHeight() - 20) / 2);
    }
  }



  FontFormat::FontFormat (unsigned short const & fontSize, short const & paddingX, short const & paddingY) :
    font_ (al_load_ttf_font ("../gamefiles/fonts/good times rg.ttf", fontSize, 0)),
    fontSize_ (fontSize),
    isLastFetchedBitmapUpToDate_ (false),
    paddingX_ (paddingX),
    paddingY_ (paddingY),
    position_ (0, 0),
    rectangle_ (PlanarPosition (0, 0), PlanarDimensions (0, 0))
  {
    if (!font_) {
      throw AllegroInitializationException ("Could not initialise the font");
    }
  }



  FontFormat::FontFormat (PlanarDimensions const & dimensions, unsigned short const & padding) :
    font_ (al_load_ttf_font ("../gamefiles/fonts/good times rg.ttf", dimensions.getHeight() - 2 * padding, 0)),
    fontSize_ (dimensions.getHeight() - 2 * padding),
    isLastFetchedBitmapUpToDate_ (false),
    paddingX_ (padding),
    paddingY_ (padding),
    position_ (0, 0),
    rectangle_ (PlanarPosition (0, 0), PlanarDimensions (0, 0))
  {
    if (!font_) {
      throw AllegroInitializationException ("Could not initialise the font");
    }
  }



  FontFormat::FontFormat (PlanarDimensions const & dimensions) :
    font_ (al_load_ttf_font ("../gamefiles/fonts/good times rg.ttf", getFontSize (dimensions, large), 0)),
    fontSize_ (getFontSize (dimensions, large)),
    isLastFetchedBitmapUpToDate_ (false),
    paddingX_ (dimensions.getWidth() * 0.01),
    paddingY_ (getYPadding (dimensions, large)),
    position_ (0, 0),
    rectangle_ (PlanarPosition (0, 0), PlanarDimensions (0, 0))
  {
  }



  FontFormat::FontFormat (PlanarDimensions const & dimensions, Style const &) :
    font_ (al_load_ttf_font ("../gamefiles/fonts/good times rg.ttf", getFontSize (dimensions, small), 0)),
    fontSize_ (getFontSize (dimensions, small)),
    isLastFetchedBitmapUpToDate_ (false),
    paddingX_ (dimensions.getWidth() * 0.05),
    paddingY_ (getYPadding (dimensions, small)),
    position_ (0, 0),
    rectangle_ (PlanarPosition (0, 0), PlanarDimensions (0, 0))
  {
  }



  FontFormat::~FontFormat()
  {
    al_destroy_font (font_);
    al_destroy_bitmap (bitmap_);
  }



  ALLEGRO_FONT * FontFormat::getFont() const
  {
    return font_;
  }



  unsigned short const & FontFormat::getFontSize() const
  {
    return fontSize_;
  }



  short const & FontFormat::getXPadding() const
  {
    return paddingX_;
  }



  short const & FontFormat::getYPadding() const
  {
    return paddingY_;
  }



  short const & FontFormat::getLineHeight() const
  {
    return lineHeight_;
  }



  I_ObservableId const & FontFormat::getObservableId() const
  {
    return observableId_;
  }



  void FontFormat::reset()
  {
  }



  void FontFormat::processEvent (I_AllegroEventAdapter const &)
  {
  }



  bool const & FontFormat::isLastFetchedBitmapUpToDate() const
  {
    return isLastFetchedBitmapUpToDate_;
  }



  unsigned int const & FontFormat::getWidth() const
  {
    return rectangle_.getWidth();
  }



  unsigned int const & FontFormat::getHeight() const
  {
    return rectangle_.getHeight();
  }



  bool FontFormat::contains (PlanarPosition const & position) const
  {
    return rectangle_.contains (position);
  }



  int const & FontFormat::getX() const
  {
    return rectangle_.getX();
  }



  int const & FontFormat::getY() const
  {
    return rectangle_.getY();
  }



  PlanarPosition const & FontFormat::getCenter() const
  {
    return rectangle_.getCenter();
  }



  PlanarPosition const & FontFormat::getPosition() const
  {
    return position_;
  }



  ALLEGRO_BITMAP * FontFormat::fetchBitmap()
  {
    if (!isLastFetchedBitmapUpToDate_) {
      ALLEGRO_BITMAP * targetBitmap (al_get_target_bitmap());

      if (bitmap_ != nullptr) {
        al_destroy_bitmap (bitmap_);
      }

      al_set_target_bitmap (targetBitmap);
    }
    return bitmap_;
  }
}