#include "PlanarDimensions.h"

namespace it
{
  PlanarDimensions::PlanarDimensions (unsigned int const & width, unsigned int const & height) :
    width_ (width),
    height_ (height)
  {
  }



  unsigned int const & PlanarDimensions::getWidth() const
  {
    return width_;
  }



  unsigned int const & PlanarDimensions::getHeight() const
  {
    return height_;
  }
}

