#include "FontFormat.h"

#include "allegro5\allegro_ttf.h"

#include "AllegroInitializationException.h"

namespace it
{
  FontFormat::FontFormat (unsigned short const & fontSize, short const & paddingX, short const & paddingY) :
    fontFormat_ (al_load_ttf_font ("../gamefiles/fonts/good times rg.ttf", fontSize, 0)),
    fontSize_ (fontSize),
    paddingX_ (paddingX),
    paddingY_ (paddingY)
  {
    if (!fontFormat_) {
      throw AllegroInitializationException ("Could not initialise the font");
    }
  }



  FontFormat::~FontFormat()
  {
    al_destroy_font (fontFormat_);
  }



  ALLEGRO_FONT * FontFormat::getFont() const
  {
    return fontFormat_;
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