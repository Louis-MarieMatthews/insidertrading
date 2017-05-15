#include "ContextualMenuBitmapSingleton.h"
#include "DefaultContextualMenuBitmap.h"
#include "DefaultObservableId.h"
#include "ObserverListSingleton.h"

namespace it
{
  ContextualMenuBitmapSingleton::ContextualMenuBitmapSingleton() :
    contextualMenuBitmap_ (nullptr),
    lineHeight_ (30),
    padding_ (10),
    margin_ (20),
    observableId_ (DefaultObservableId())
  {

  }



  ContextualMenuBitmapSingleton & ContextualMenuBitmapSingleton::getInstance()
  {
    static ContextualMenuBitmapSingleton instance_;
    return instance_;
  }



  void ContextualMenuBitmapSingleton::setContextualMenuBitmap (I_LocatedInteractiveBitmap * contextualMenuBitmap)
  {
    contextualMenuBitmap_ = contextualMenuBitmap;
    ObserverListSingleton::getInstance().notifyObservers (observableId_);
  }



  void ContextualMenuBitmapSingleton::setContextualMenu (I_ContextualMenu * menu, PlanarPosition const & iconPosition)
  {
    PlanarPosition menuPosition (iconPosition.getX(), iconPosition.getY() - menu->getNumberOfChoices() * lineHeight_ - 2 * padding_ - margin_);
    contextualMenuBitmap_ = new DefaultContextualMenuBitmap (menu, menuPosition); // TODO: created pointer must be deleted!
    ObserverListSingleton::getInstance().notifyObservers (observableId_);
  }



  I_LocatedInteractiveBitmap * ContextualMenuBitmapSingleton::getContextualMenuBitmap() const
  {
    return contextualMenuBitmap_;
  }



  I_ObservableId const & ContextualMenuBitmapSingleton::getObservableId() const
  {
    return observableId_;
  }
}