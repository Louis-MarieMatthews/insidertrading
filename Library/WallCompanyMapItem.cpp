#include "WallCompanyMapItem.h"

namespace it
{
  WallCompanyMapItem::WallCompanyMapItem() :
    isTraversable_ (false)
  {
  }



  bool const & WallCompanyMapItem::isTraversable() const
  {
    return isTraversable_;
  }
}