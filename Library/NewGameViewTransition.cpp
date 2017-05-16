#include "NewGameViewTransition.h"

namespace it
{
  NewGameViewTransition::NewGameViewTransition (ViewData & viewData) :
    viewData_ (viewData)
  {
  }



  I_BitmapView * NewGameViewTransition::getTarget()
  {
    return viewData_.getGameView();
  }



  void NewGameViewTransition::setTarget (I_BitmapView * view)
  {
  }



  void NewGameViewTransition::prepare()
  {
    viewData_.createNewGame();
  }
}