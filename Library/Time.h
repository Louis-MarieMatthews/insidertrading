#pragma once

#include <set>

#include "I_ConstantObservable.h"
#include "I_ObservableId.h"

namespace it
{
  class Time : public I_ConstantObservable
  {
    unsigned short int second_;
    unsigned short int minute_;
    unsigned short int hour_;
    unsigned short int day_;
    unsigned short int month_;
    unsigned short int year_;

    I_ObservableId     observableId_;

  public:
    Time();
    ~Time();
    void tick();
    unsigned short int const & getSecond() const;
    unsigned short int const & getMinute() const;
    unsigned short int const & getHour() const;
    unsigned short int const & getDay() const;
    unsigned short int const & getMonth() const;
    unsigned short int const & getYear() const;
    std::string getString() const;

    // Inherited via I_ConstantObservable
    virtual I_ObservableId const & getObservableId() const override;
  };
}