#pragma once

namespace it
{
  class I_CompanyMapItem
  {
  public:
    virtual ~I_CompanyMapItem() {};
    virtual bool const & isTraversable() const = 0;
    virtual bool const & isDocument() const = 0;
  };
}