#include "FontFormat.h"

#include "allegro5\allegro_ttf.h"

#include "AllegroInitializationException.h"

namespace it
{
  unsigned short FontFormat::getFontSize (PlanarDimensions const & dimensions)
  {
    if (dimensions.getWidth() > dimensions.getHeight() * 10) {
      return dimensions.getHeight() * 0.90;
    }
    else {
      return dimensions.getHeight() * 0.40;
    }
  }



  unsigned short FontFormat::getYPadding (PlanarDimensions const & dimensions)
  {
    if (dimensions.getWidth() > dimensions.getHeight() * 10) {
      return dimensions.getHeight() * 0.05;
    }
    else {
      return dimensions.getHeight() * 0.30;
    }
  }



  FontFormat::FontFormat (unsigned short const & fontSize, short const & paddingX, short const & paddingY) :
    font_ (al_load_ttf_font ("../gamefiles/fonts/good times rg.ttf", fontSize, 0)),
    fontSize_ (fontSize),
    paddingX_ (paddingX),
    paddingY_ (paddingY)
  {
    if (!font_) {
      throw AllegroInitializationException ("Could not initialise the font");
    }
  }



  FontFormat::FontFormat (PlanarDimensions const & dimensions, unsigned short const & padding) :
    font_ (al_load_ttf_font ("../gamefiles/fonts/good times rg.ttf", dimensions.getHeight() - 2 * padding, 0)),
    fontSize_ (dimensions.getHeight() - 2 * padding),
    paddingX_ (padding),
    paddingY_ (padding)
  {
    if (!font_) {
      throw AllegroInitializationException ("Could not initialise the font");
    }
  }



  FontFormat::FontFormat (PlanarDimensions const & dimensions) :
    font_ (al_load_ttf_font ("../gamefiles/fonts/good times rg.ttf", getFontSize (dimensions), 0)),
    fontSize_ (getFontSize (dimensions)),
    paddingX_ (dimensions.getWidth() * 0.05),
    paddingY_ (getYPadding (dimensions))
  {
  }



  FontFormat::~FontFormat()
  {
    al_destroy_font (font_);
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
}