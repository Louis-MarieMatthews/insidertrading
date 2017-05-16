#pragma once

#include "DefaultObservableId.h"
#include "I_ConstantObservable.h"
#include "ObserverListSingleton.h"

namespace it
{
  template <class T>
  class ObservablePointer : public I_ConstantObservable
  {
    T * ptr_;

    DefaultObservableId observableId_;

  public:
    ObservablePointer();
    ~ObservablePointer();
    ObservablePointer (T *);
    T * getPointer();
    void setPointer (T *);

    // Inherited via I_ConstantObservable
    virtual I_ObservableId const & getObservableId() const override;
  };



  template<class T>
  inline ObservablePointer<T>::ObservablePointer() :
    ptr_ (nullptr)
  {
  }



  template<class T>
  inline ObservablePointer<T>::~ObservablePointer()
  {
    ObserverListSingleton::getInstance().removeObservable (observableId_);
  }



  template<class T>
  inline ObservablePointer<T>::ObservablePointer (T * ptr) :
    ptr_ (ptr)
  {
  }



  template<class T>
  inline T * ObservablePointer<T>::getPointer()
  {
    return ptr_;
  }



  template<class T>
  inline void ObservablePointer<T>::setPointer (T * ptr)
  {
    ptr_ = ptr;
    ObserverListSingleton::getInstance().notifyObservers (observableId_);
  }



  template<class T>
  inline I_ObservableId const & ObservablePointer<T>::getObservableId() const
  {
    return observableId_;
  }
}