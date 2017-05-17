#pragma once

#include "DefaultObservableId.h"
#include "I_ConstantObservable.h"

namespace it
{
  class PlanarPosition : public I_ConstantObservable
  {
    DefaultObservableId observableId_;
    int                 x_;
    int                 y_;

  public:
    PlanarPosition (const int&, const int&);
    ~PlanarPosition();
    const int& getX() const;
    const int& getY() const;
    void setX (int const &);
    void setY (int const &);
    void update (PlanarPosition const &);
    bool isNearby (PlanarPosition const &, int const &) const;
    bool operator== (PlanarPosition const &) const;
    bool operator!= (PlanarPosition const &) const;

    // Inherited via I_ConstantObservable
    virtual I_ObservableId const & getObservableId() const override;
  };
}

