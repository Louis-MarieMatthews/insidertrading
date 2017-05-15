#pragma once

#include "I_CompanyMapItem.h"

namespace it
{
  class FloorCompanyMapItem : public I_CompanyMapItem
  {
    bool const isDocument_;
    bool const isTraversable_;
    PlanarPosition position_;


  public:
    FloorCompanyMapItem (PlanarPosition const &);

    // Inherited via I_CompanyMapItem
    virtual bool const & isTraversable() const override;
    virtual bool const & isDocument() const override;
    virtual PlanarPosition const & getPosition() const override;
  };
}