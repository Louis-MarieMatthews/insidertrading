#include "SimpleViewTransition.h"

namespace it
{
  SimpleViewTransition::SimpleViewTransition (I_BitmapView * target) :
    target_ (target)
  {
  }



  I_BitmapView * SimpleViewTransition::getTarget()
  {
    return target_;
  }



  void SimpleViewTransition::setTarget (I_BitmapView * target)
  {
    target_ = target;
  }



  void SimpleViewTransition::prepare()
  {
  }
}