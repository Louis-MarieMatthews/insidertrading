#include "ObserverListSingleton.h"

namespace it
{
  ObserverListSingleton::ObserverListSingleton()
  {
  }



  ObserverListSingleton & ObserverListSingleton::getInstance()
  {
    static ObserverListSingleton instance;
    return instance;
  }



  void ObserverListSingleton::addObserver (I_ObservableId const & observable, I_ConstantObserver & observer)
  {
    observers_[&observable].insert (&observer);
  }



  void ObserverListSingleton::removeObserver (I_ObservableId const & observableId, I_ConstantObserver & observer)
  {
    observers_[&observableId].erase (&observer);
  }



  void ObserverListSingleton::removeObservable (I_ObservableId & observableId)
  {
    observers_.erase (&observableId);
  }



  void ObserverListSingleton::notifyObservers (I_ObservableId & id)
  {
    for (auto o : observers_[&id]) {
      o->notifyObserver (id);
    }
  }
}