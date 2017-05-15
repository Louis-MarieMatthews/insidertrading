#pragma once

#include "I_CompanyMapItem.h"

namespace it
{
  class WallCompanyMapItem : public I_CompanyMapItem
  {
    bool const isDocument_;
    bool const isTraversable_;
    PlanarPosition position_;
    
  public:
    WallCompanyMapItem (PlanarPosition const &);

    // Inherited via I_CompanyMapItem
    virtual bool const & isTraversable() const override;
    virtual bool const & isDocument() const override;
    virtual PlanarPosition const & getPosition() const override;
  };
}