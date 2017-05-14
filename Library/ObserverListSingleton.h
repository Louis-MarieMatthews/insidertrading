#pragma once

#include <map>
#include <set>

#include "I_ObservableId.h"
#include "I_ConstantObserver.h"

// TODO: needs a method to remove observables
namespace it
{
  class ObserverListSingleton
  {
    ObserverListSingleton();
    ObserverListSingleton (const ObserverListSingleton&) = delete;
    ObserverListSingleton & operator= (const ObserverListSingleton&) = delete;

    std::map<I_ObservableId const *, std::set<I_ConstantObserver *>> observers_;

  public:
    static ObserverListSingleton & getInstance();
    void addObserver (I_ObservableId const &, I_ConstantObserver &); // TODO: only the observer itself should be able to call these functions
    void removeObserver (I_ObservableId const &, I_ConstantObserver &); // TODO: only the observer itself should be able to call these functions
    void notifyObservers (I_ObservableId &);
  };
}