#pragma once

#include <set>

#include "I_ConstantObservable.h"
#include "I_ObservableId.h"

namespace it
{
  class Duration : public I_ConstantObservable
  {
    unsigned short int centisecond_;
    unsigned short     second_;
    unsigned short int minute_;
    unsigned short int hour_;

    I_ObservableId     observableId_;

  public:
    Duration();
    ~Duration();
    void tick();
    void reset();
    unsigned short int const & getCentisecond() const;
    unsigned short int const & getSecond() const;
    unsigned short int const & getMinute() const;
    unsigned short int const & getHour() const;
    std::string getString() const;

    // Inherited via I_ConstantObservable
    virtual I_ObservableId const & getObservableId() const override;
  };
}