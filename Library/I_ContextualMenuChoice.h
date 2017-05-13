#pragma once

#include <string>

#include "I_ConstantObservable.h"

namespace it
{
  class I_ContextualMenuChoice : public I_ConstantObservable
  {
  public:
    virtual ~I_ContextualMenuChoice() {};
    virtual std::string const & getText() const = 0;
    virtual bool const & isDisabled() const = 0;
    virtual void select() = 0;
  };
}