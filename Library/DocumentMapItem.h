#pragma once

#include "I_CompanyMapItem.h"

namespace it
{
  class DocumentMapItem : public I_CompanyMapItem
  {
    bool isTraversable_;
    bool isDocument_;
    PlanarPosition position_;
    
  public:
    DocumentMapItem (PlanarPosition const &);

    // Inherited via I_CompanyMapItem
    virtual bool const & isTraversable() const override;
    virtual bool const & isDocument() const override;
    virtual PlanarPosition const & getPosition() const override;
  };
}