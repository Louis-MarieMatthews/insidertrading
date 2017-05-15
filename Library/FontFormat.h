#pragma once

#include "allegro5\allegro_font.h"

#include "PlanarDimensions.h"

// TODO: separate interface & implementation
namespace it
{
  class FontFormat
  {
    ALLEGRO_FONT * font_;
    unsigned short fontSize_;
    short          paddingX_;
    short          paddingY_;

    static unsigned short getFontSize (PlanarDimensions const &);
    static unsigned short getYPadding (PlanarDimensions const &);

  public:
    FontFormat (unsigned short const &, short const &, short const &);
    FontFormat (PlanarDimensions const &, unsigned short const &);
    FontFormat (PlanarDimensions const &);
    ~FontFormat();

    ALLEGRO_FONT * getFont() const; // TODO: return const font
    unsigned short const & getFontSize() const;
    short const & getXPadding() const;
    short const & getYPadding() const;
  };
}