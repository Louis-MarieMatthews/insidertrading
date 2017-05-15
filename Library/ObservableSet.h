#pragma once

#include <set>

#include "I_ConstantObservable.h"
#include "DefaultObservableId.h"
#include "ObserverListSingleton.h"

namespace it
{
  template <class T>
  class ObservableSet : public I_ConstantObservable
  {
    std::set<T>    set_;
    I_ObservableId observableId_;

  public:
    ObservableSet();
    void insert (T const &);
    void erase (T const &);
    std::set<T> const & getSet() const;
    bool contains (T const &) const;
    size_t getSize() const;

    virtual I_ObservableId const & getObservableId() const override;
  };



  template<class T>
  inline ObservableSet<T>::ObservableSet() :
    observableId_ (DefaultObservableId())
  {
  }



  template<class T>
  inline void ObservableSet<T>::insert  (T const & element)
  {
    set_.insert (element);
    ObserverListSingleton::getInstance().notifyObservers (observableId_);
  }



  template<class T>
  inline void ObservableSet<T>::erase (T const & element)
  {
    set_.erase (element);
    ObserverListSingleton::getInstance().notifyObservers (observableId_);
  }



  template<class T>
  inline std::set<T> const & ObservableSet<T>::getSet() const
  {
    return set_;
  }



  template<class T>
  inline bool ObservableSet<T>::contains (T const & researched) const
  {
    for (auto t : set_) {
      if (&t == &researched) {
        return true;
      }
    }
    return false;
  }



  template<class T>
  inline size_t ObservableSet<T>::getSize() const
  {
    return set_.size();
  }



  template<class T>
  inline I_ObservableId const & ObservableSet<T>::getObservableId() const
  {
    return observableId_;
  }
}