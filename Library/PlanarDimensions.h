#pragma once

namespace it
{
  class PlanarDimensions
  {
    unsigned int width_;
    unsigned int height_;
  public:
    PlanarDimensions (const unsigned int&, const unsigned int&);
    const unsigned int& getWidth() const;
    const unsigned int& getHeight() const;
  };
}