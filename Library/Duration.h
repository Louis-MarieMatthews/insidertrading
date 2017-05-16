#pragma once

#include <set>

#include "I_ConstantObservable.h"
#include "I_ObservableId.h"

namespace it
{
  class Duration : public I_ConstantObservable
  {
    unsigned short centisecond_;
    unsigned short second_;
    unsigned short minute_;
    unsigned short hour_;

    I_ObservableId     observableId_;

  public:
    Duration();
    Duration (unsigned short const &, unsigned short const &, unsigned short const &, unsigned short const &);
    ~Duration();
    void tick();
    void untick();
    void reset();
    unsigned short int const & getCentisecond() const;
    unsigned short int const & getSecond() const;
    unsigned short int const & getMinute() const;
    unsigned short int const & getHour() const;
    std::string getString() const;

    // Inherited via I_ConstantObservable
    virtual I_ObservableId const & getObservableId() const override;
  };

  bool operator== (Duration const &, int const &);
}