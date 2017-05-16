#pragma once

#include "I_ViewTransition.h"
#include "ViewData.h"

namespace it
{
  class NewGameViewTransition : public I_ViewTransition
  {
    ViewData &     viewData_;
    std::string    gameFilename_;

  public:
    NewGameViewTransition (ViewData &, std::string const &);

    // Inherited via I_ViewTransition
    virtual I_BitmapView * getTarget() override;
    virtual void setTarget (I_BitmapView *) override;
    virtual void prepare() override;
  };
}