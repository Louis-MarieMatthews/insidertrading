#pragma once

#include "I_CompanyMapItem.h"

namespace it
{
  class FloorCompanyMapItem : public I_CompanyMapItem
  {
    bool const isDocument_;
    bool const isTraversable_;


  public:
    FloorCompanyMapItem();

    // Inherited via I_CompanyMapItem
    virtual bool const & isTraversable() const override;
    virtual bool const & isDocument() const override;
  };
}