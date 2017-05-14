#pragma once

#include "I_CompanyMapItem.h"

namespace it
{
  class WallCompanyMapItem : public I_CompanyMapItem
  {
    bool const isTraversable_;

  public:
    WallCompanyMapItem();
    //~WallCompanyMapItem();

    // Inherited via I_CompanyMapItem
    virtual bool const & isTraversable() const override;
  };
}