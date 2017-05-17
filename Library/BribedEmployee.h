#pragma once

#include "Duration.h"
#include "I_GameData.h"
#include "PlanarPosition.h"
#include "ObservableSet.h"
#include "I_CompanyMapItem.h"
#include "I_CompanyMap.h"
#include "Node.h"

namespace it
{
  class BribedEmployee : public I_ConstantObserver, public I_ConstantObservable
  {
    std::set<Node *>                   allNodes_;
    Company &                          company_;
    unsigned short                     lastSavedSecond_;
    I_CompanyMap &                     map_;
    DefaultObservableId                observableId_;
    PlanarPosition const &             position_;
    ObservablePointer<Company const> & secTarget_;
    bool                               secInspecting_;
    Duration const &                   time_;
    PlanarPosition *                   currentTarget_;
    Node *                             target_;

    Node * nodeWithTheLeastF (std::set<Node *> &);
    std::set<Node *> generateSuccessors (Node &, std::set<Node *> &);
    Node * createNode (PlanarPosition const &, Node *);
    std::set<Node> getNodesWithSmallestFValue (std::set<Node> const &);

  public:
    BribedEmployee (I_GameData &, PlanarPosition const &, Company &);
    ~BribedEmployee();
    Node * getTarget();
    void updateTarget();
    PlanarPosition const & getPosition();

    // Inherited via I_ConstantObserver
    virtual void notifyObserver (I_ObservableId const &) override;

    // Inherited via I_ConstantObservable
    virtual I_ObservableId const & getObservableId() const override;
  };
}