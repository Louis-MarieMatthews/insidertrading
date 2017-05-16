#pragma once

#include "I_ViewTransition.h"

namespace it
{
  class SimpleViewTransition : public I_ViewTransition
  {
    I_BitmapView * target_;

  public:
    SimpleViewTransition (I_BitmapView *);

    // Inherited via I_ViewTransition
    virtual I_BitmapView * getTarget() override;
    virtual void prepare() override;
  };
}