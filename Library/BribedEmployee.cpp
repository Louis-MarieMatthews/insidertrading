#include "BribedEmployee.h"

#include <set>

#include "Sec.h"

namespace it
{
  void BribedEmployee::updateTarget()
  {
    for (auto n : allNodes_) {
      delete n;
    }

    std::set<Node *> openList;
    std::set<Node *> closedList;
    Node * node (createNode (position_, nullptr));
    openList.insert (node);

    while (!openList.empty()) {
      Node * q (nodeWithTheLeastF (openList));
      openList.erase (q);

      std::set<Node *> successors (generateSuccessors (*q, allNodes_));

      for (auto s : successors) {
        if (&s->getPosition() == currentTarget_) {
          target_ = s;
          return;
        }
        s->setGValue (q->getGValue() + 1);
        s->setHValue (abs (s->getPosition().getX() - currentTarget_->getX()) + abs (s->getPosition().getY() - currentTarget_->getY()));

        bool skip (false);
        for (auto n : openList) {
          if (n->getPosition() == s->getPosition() && n->getFValue() < s->getFValue()) {
            skip = true;
          }
        }
        for (auto n : closedList) {
          if (n->getPosition() == s->getPosition() && n->getFValue() < s->getFValue()) {
            skip = true;
          }
        }
        if (skip) {
          continue;
        }
        else {
          openList.insert (s);
        }
        closedList.insert (q);
      }
    }
  }



  Node * BribedEmployee::nodeWithTheLeastF (std::set<Node *> & set)
  {
    Node * nodeWithTheLeastF (nullptr);
    for (auto s : set) {
      if (nodeWithTheLeastF == nullptr || s->getFValue() < nodeWithTheLeastF->getFValue()) {
        nodeWithTheLeastF = s;
      }
    }
    return nodeWithTheLeastF;
  }



  std::set<Node *> BribedEmployee::generateSuccessors (Node & node, std::set<Node *> &)
  {
    std::set<Node *> successors;
    PlanarPosition p (node.getPosition());
    Node * node0 (createNode (PlanarPosition (p.getX() - 1, p.getY()), &node));
    if (node0->isPassable()) {
      successors.insert (node0);
    }
    Node * node1 (createNode (PlanarPosition (p.getX() + 1, p.getY()), &node));
    if (node1->isPassable()) {
      successors.insert (node1);
    }
    Node * node2 (createNode (PlanarPosition (p.getX(), p.getY() - 1), &node));
    if (node2->isPassable()) {
      successors.insert (node2);
    }
    Node * node3 (createNode (PlanarPosition (p.getX(), p.getY() + 1), &node));
    if (node3->isPassable()) {
      successors.insert (node3);
    }
    return successors;
  }



  Node * BribedEmployee::createNode (PlanarPosition const & position, Node * parent)
  {
    I_CompanyMapItem const * item (map_.getItem (position.getX(), position.getY()));
    bool passable;
    if (item == nullptr || item->isTraversable()) {
      passable = true;
    }
    else {
      passable = false;
    }

    Node * node (new Node (parent, passable, position));
    allNodes_.insert (node);
    return node;
  }



  std::set<Node> BribedEmployee::getNodesWithSmallestFValue (std::set<Node> const &)
  {
    return std::set<Node>();
  }



  BribedEmployee::BribedEmployee (I_GameData & gameData, PlanarPosition const & position, Company & company) :
    company_ (company),
    currentTarget_ (new PlanarPosition (40, 40)),
    lastSavedSecond_ (-1),
    map_ (company.getMap()),
    position_ (position),
    secInspecting_ (false),
    secTarget_ (gameData.getSec().getObservableTarget()),
    time_ (gameData.getTime())
  {
    ObserverListSingleton::getInstance().addObserver (time_.getObservableId(), *this);
    ObserverListSingleton::getInstance().addObserver (secTarget_.getObservableId(), *this);
  }



  BribedEmployee::~BribedEmployee()
  {
    ObserverListSingleton::getInstance().removeObserver (secTarget_.getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (secTarget_.getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObservable (observableId_);
    for (auto n : allNodes_) {
      delete n;
    }
  }



  Node * BribedEmployee::getTarget()
  {
    return target_;
  }



  PlanarPosition const & BribedEmployee::getPosition()
  {
    return position_;
  }



  void BribedEmployee::notifyObserver (I_ObservableId const & observableId)
  {
    if (&secTarget_.getObservableId() == &observableId) {
      if (secTarget_.getPointer() == &company_ && secTarget_.getPointer()->hasInsiders()) {
        secInspecting_ = true;
      }
      else {
        secInspecting_ = false;
      }
    }
    if (&time_.getObservableId() == &observableId) {
      if (time_.getSecond() != lastSavedSecond_ && secInspecting_) {
        lastSavedSecond_ = time_.getSecond();
        map_.moveBribedEmployee (up);
        ObserverListSingleton::getInstance().notifyObservers (observableId_);
      }
    }
  }



  I_ObservableId const & BribedEmployee::getObservableId() const
  {
    return observableId_;
  }
}