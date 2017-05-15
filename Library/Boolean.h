#pragma once

#include "DefaultObservableId.h"
#include "I_ConstantObservable.h"

namespace it
{
  class Boolean : public I_ConstantObservable
  {
    bool                value_;
    DefaultObservableId observableId_;

  public:
    Boolean (bool const &);
    bool const & getValue() const;
    void setValue (bool const &);
    void operator= (bool const &);

    // Inherited via I_ConstantObservable
    virtual I_ObservableId const & getObservableId() const override;
  };

}