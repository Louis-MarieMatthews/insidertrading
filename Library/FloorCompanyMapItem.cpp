#include "FloorCompanyMapItem.h"

namespace it
{
  FloorCompanyMapItem::FloorCompanyMapItem() :
    isTraversable_ (true)
  {
  }



  bool const & FloorCompanyMapItem::isTraversable() const
  {
    return isTraversable_;
  }
}