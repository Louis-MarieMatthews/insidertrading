#include "WallCompanyMapItem.h"

namespace it
{
  WallCompanyMapItem::WallCompanyMapItem() :
    isDocument_ (false),
    isTraversable_ (false)
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
}