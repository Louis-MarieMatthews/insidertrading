#include "Node.h"

namespace it
{
  Node::Node (Node * parent, bool const & passable, PlanarPosition const & position) :
    passable_ (passable),
    parent_ (parent),
    position_ (position)
  {
  }



  unsigned short const & Node::getFValue()
  {
    return fValue_;
  }



  unsigned short const & Node::getGValue()
  {
    return gValue_;
  }



  unsigned short const & Node::getHValue()
  {
    return hValue_;
  }



  Node * Node::getParent()
  {
    return parent_;
  }



  PlanarPosition const & Node::getPosition()
  {
    return position_;
  }



  bool const & Node::isPassable() const
  {
    return passable_;
  }



  void Node::setFValue (unsigned short const & fValue)
  {
    fValue_ = fValue;
  }



  void Node::setGValue (unsigned short const & gValue)
  {
    gValue_ = gValue;
  }



  void Node::setHValue (unsigned short const & hValue)
  {
    hValue_ = hValue;
  }
}