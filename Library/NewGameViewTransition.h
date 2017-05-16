#pragma once

#include "I_ViewTransition.h"
#include "ViewData.h"

namespace it
{
  class NewGameViewTransition : public I_ViewTransition
  {
    ViewData &     viewData_;

  public:
    NewGameViewTransition (ViewData &);

    // Inherited via I_ViewTransition
    virtual I_BitmapView * getTarget() override;
    virtual void prepare() override;
  };
}