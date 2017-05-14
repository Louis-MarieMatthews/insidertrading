#include "I_LocatedRectangle.h"
#include "DefaultLocatedRectangle.h"

namespace it
{
  DefaultLocatedRectangle::DefaultLocatedRectangle (const PlanarPosition& position, const PlanarDimensions& dimensions) :
    center_ (calculateCenter (dimensions, position)),
    position_ (position),
    dimensions_ (dimensions)
  {
  }



  PlanarPosition DefaultLocatedRectangle::calculateCenter (PlanarDimensions const & dimensions, PlanarPosition const & position)
  {
    int x (position.getX() + dimensions.getWidth() / 2);
    int y (position.getY() + dimensions.getHeight() / 2);
    return PlanarPosition (x, y);
  }



  const unsigned int & DefaultLocatedRectangle::getWidth() const
  {
    return dimensions_.getWidth();
  }



  const unsigned int & DefaultLocatedRectangle::getHeight() const
  {
    return dimensions_.getHeight();
  }



  bool DefaultLocatedRectangle::contains (const PlanarPosition& position) const
  {
    bool withinHorizontalRange = position.getX() >= position_.getX() && position.getX() <= position_.getX() + dimensions_.getWidth();
    bool withinVerticalRange   = position.getY() >= position_.getY() && position.getY() <= position_.getY() + dimensions_.getHeight();
    return withinHorizontalRange && withinVerticalRange;
  }



  const int& DefaultLocatedRectangle::getX() const
  {
    return position_.getX();
  }



  const int& DefaultLocatedRectangle::getY() const
  {
    return position_.getY();
  }



  PlanarPosition const & DefaultLocatedRectangle::getCenter() const
  {
    return center_;
  }
}