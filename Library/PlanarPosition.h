#pragma once

namespace it
{
  class PlanarPosition
  {
    int x_;
    int y_;
  public:
    PlanarPosition (const int&, const int&);
    const int& getX() const;
    const int& getY() const;
    bool operator== (const PlanarPosition&) const;
    bool operator!= (const PlanarPosition&) const;
  };
}

