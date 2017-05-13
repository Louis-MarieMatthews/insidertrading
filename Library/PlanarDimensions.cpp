#include "PlanarDimensions.h"

namespace it
{
  PlanarDimensions::PlanarDimensions (const unsigned int& width, const unsigned int& height) :
    width_ (width),
    height_ (height)
  {
  }



  const unsigned int& PlanarDimensions::getWidth() const
  {
    return width_;
  }



  const unsigned int& PlanarDimensions::getHeight() const
  {
    return height_;
  }
}

