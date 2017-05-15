#pragma once

#include "DefaultObservableId.h"
#include "I_ConstantObservable.h"

namespace it
{
  class PlanarPosition : public I_ConstantObservable
  {
    int                 x_;
    int                 y_;
    DefaultObservableId observableId_;

  public:
    PlanarPosition (const int&, const int&);
    const int& getX() const;
    const int& getY() const;
    void setX (int const &);
    void setY (int const &);
    void update (PlanarPosition const &);
    bool isNearby (PlanarPosition const &, int const &) const;
    bool operator== (const PlanarPosition&) const;
    bool operator!= (const PlanarPosition&) const;

    // Inherited via I_ConstantObservable
    virtual I_ObservableId const & getObservableId() const override;
  };
}

