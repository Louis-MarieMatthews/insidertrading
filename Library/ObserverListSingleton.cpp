#include "ObserverListSingleton.h"

#include "DefaultObservableId.h"

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
    //for (auto o : observers_[&id]) {
    //  o->notifyObserver (id);
    //}

    bool finished (false);
    while (!finished) {
      size_t const size (observers_[&id].size());
      bool forFinished (true);
      for (auto o : observers_[&id]) {
        o->notifyObserver (id);
        if (observers_[&id].size() != size) {
          forFinished = false;
          break;
        }
      }
      if (forFinished) {
        finished = true;
      }
      else {
        finished = false;
      }
    }
  }
}