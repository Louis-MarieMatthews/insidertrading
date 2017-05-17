#pragma once

#include "PlanarPosition.h"

namespace it
{
  class Node
  {
    unsigned short fValue_;
    unsigned short gValue_;
    unsigned short hValue_;
    bool           passable_;
    Node *         parent_;
    PlanarPosition position_;

  public:
    Node (Node * parent, bool const &, PlanarPosition const &);

    unsigned short const & getFValue();
    unsigned short const & getGValue();
    unsigned short const & getHValue();
    Node * getParent();
    PlanarPosition const & getPosition();
    bool const & isPassable() const;
    void setFValue (unsigned short const &);
    void setGValue (unsigned short const &);
    void setHValue (unsigned short const &);
  };
}