#include "FloorCompanyMapItem.h"

namespace it
{
  FloorCompanyMapItem::FloorCompanyMapItem (PlanarPosition const & position) :
    isDocument_ (false),
    isTraversable_ (true),
    position_ (position)
  {
  }



  bool const & FloorCompanyMapItem::isTraversable() const
  {
    return isTraversable_;
  }



  bool const & FloorCompanyMapItem::isDocument() const
  {
    return isDocument_;
  }



  PlanarPosition const & FloorCompanyMapItem::getPosition() const
  {
    return position_;
  }
}