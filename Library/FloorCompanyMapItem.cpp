#include "FloorCompanyMapItem.h"

namespace it
{
  FloorCompanyMapItem::FloorCompanyMapItem() :
    isDocument_ (false),
    isTraversable_ (true)
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
}