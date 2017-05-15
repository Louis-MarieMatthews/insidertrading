#include "WallCompanyMapItem.h"

namespace it
{
  WallCompanyMapItem::WallCompanyMapItem (PlanarPosition const & position) :
    isDocument_ (false),
    isTraversable_ (false),
    position_ (position)
  {
  }



  bool const & WallCompanyMapItem::isTraversable() const
  {
    return isTraversable_;
  }



  bool const & WallCompanyMapItem::isDocument() const
  {
    return isDocument_;
  }



  PlanarPosition const & WallCompanyMapItem::getPosition() const
  {
    return position_;
  }
}