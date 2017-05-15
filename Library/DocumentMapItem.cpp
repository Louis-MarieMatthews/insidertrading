#include "DocumentMapItem.h"

namespace it
{
  DocumentMapItem::DocumentMapItem() :
    isDocument_ (true),
    isTraversable_ (true)
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
}