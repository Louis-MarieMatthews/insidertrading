#include "DocumentMapItem.h"

namespace it
{
  DocumentMapItem::DocumentMapItem (PlanarPosition const & position) :
    isDocument_ (true),
    isTraversable_ (true),
    position_ (position)
  {
  }



  bool const & DocumentMapItem::isTraversable() const
  {
    return isTraversable_;
  }



  bool const & DocumentMapItem::isDocument() const
  {
    return isDocument_;
  }



  PlanarPosition const & DocumentMapItem::getPosition() const
  {
    return position_;
  }
}