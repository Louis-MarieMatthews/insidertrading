#pragma once

#include "I_Menu.h"
#include "I_ConstantObserver.h"
#include "MenuLink.h"

namespace it
{
  class MainMenu : public I_Menu, public I_ConstantObserver
  {
  private :
    bool                            isRenderUpToDate_;
    MenuLink *                      quitButton_;
    MenuLink *                      playButton_;
    I_Menu*                         next_;
    bool                            wasDrawnAtLeastOnce_;


  public :
    MainMenu();
    ~MainMenu();
    virtual void draw() override;
    virtual I_Menu* const getNext() const override;
    virtual void setNext (I_Menu*) override;
    virtual void processFrame (const I_AllegroEventAdapter*) override;
    virtual void notifyObserver(I_ObservableId const &) override;

    // Inherited via I_Menu
    virtual void resetNext() override;
  };
}