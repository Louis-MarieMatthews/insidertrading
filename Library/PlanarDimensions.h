#pragma once

namespace it
{
  class PlanarDimensions
  {
    unsigned int width_;
    unsigned int height_;

  public:
    PlanarDimensions (unsigned int const &, unsigned int const &);
    unsigned int const & getWidth() const;
    unsigned int const & getHeight() const;
    void setWidth (unsigned const &);
    void setHeight (unsigned const &);
  };
}