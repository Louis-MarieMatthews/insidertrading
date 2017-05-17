#include "GameMenu.h"

#include "allegro5\allegro_primitives.h"

#include "CompanyView.h"
#include "ObserverListSingleton.h"

namespace it
{
  std::set<CompanyIcon *> GameMenu::getCompanyIcons (I_GameData & gameData, ContextualMenuBitmap * & parentContextualMenu)
  {
    std::set<CompanyIcon *> icons;
    std::set<Company *> const companies (gameData.getCompanies());
    for (auto c: companies) {
      icons.insert (new CompanyIcon (*c, gameData, c->getPosition()));
    }
    return icons;
  }



  void GameMenu::stopObserving()
  {
    ObserverListSingleton::getInstance().removeObserver (ContextualMenuBitmapSingleton::getInstance().getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (menuBar_.getObservableId(), *this);
    
    for (auto ci : companyIcons_) {
      ObserverListSingleton::getInstance().removeObserver (ci->getObservableId(), *this);
    }

    ObserverListSingleton::getInstance().removeObserver (secIcon_.getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (gameData_.getSec().getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (companyBeingCleaned_.getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (gameData_.isPlayerInTheGame().getObservableId(), *this);
    if (contextualMenuBitmapSingleton_.getContextualMenuBitmap() != nullptr) {
      ObserverListSingleton::getInstance().removeObserver (contextualMenuBitmapSingleton_.getContextualMenuBitmap()->getObservableId(), *this);
    }
  }



  CompanyIcon const * GameMenu::getIcon (Company const & company) const
  {
    for (auto & ci : companyIcons_) {
      if (&ci->getCompany() == &company) {
        return ci;
      }
    }
    return nullptr;
  }



  GameMenu::GameMenu (ViewData & viewData, PlanarDimensions const & dimensions) :
    bitmapBackground_ (al_load_bitmap ("../gamefiles/images/background.bmp")),
    companyBeingCleaned_ (viewData.getGameData().getPointer()->getCompanyBeingCleaned()),
    companyIcons_ (getCompanyIcons (*viewData.getGameData().getPointer(), contextualMenu_)),
    contextualMenuBitmapSingleton_ (ContextualMenuBitmapSingleton::getInstance()),
    dimensions_ (dimensions),
    isLastFetchedBitmapUpToDate_ (false),
    gameData_ (*viewData.getGameData().getPointer()),
    gameOverBitmap_ (dimensions),
    menuBar_ (*viewData.getGameData().getPointer(), PlanarDimensions (dimensions.getWidth(), 40), PlanarPosition (0, 0)),
    next_ (this),
    secIcon_ (viewData.getGameData().getPointer()->getSec()),
    viewData_ (viewData)
  {
  }



  GameMenu::~GameMenu()
  {
    if (bitmap_ != nullptr) {
      al_destroy_bitmap (bitmap_);
    }
    if (bitmapBackground_ != nullptr) {
      al_destroy_bitmap (bitmapBackground_);
    }
    stopObserving();
  }



  I_ObservableId const & GameMenu::getObservableId() const
  {
    return observableId_;
  }



  void GameMenu::reset()
  {
    next_ = this;
    menuBar_.reset();
    secIcon_.reset();
  }



  void GameMenu::processEvent (I_AllegroEventAdapter const & e)
  {
    if (e.wasEscapeKeyPressed()) {
      next_ = viewData_.getMainMenu();
    }
    else if (e.isNewCentisecond()) {

    }
    else if (gameData_.isPlayerInTheGame().getValue()) {
      I_LocatedInteractiveBitmap * menu (ContextualMenuBitmapSingleton::getInstance().getContextualMenuBitmap());
      if (menu != nullptr) {
        menu->processEvent (e);
      }

      for (auto ci : companyIcons_) {
        ci->processEvent (e);
      }
    }
    secIcon_.processEvent (e);
  }



  bool const & GameMenu::isLastFetchedBitmapUpToDate() const
  {
    return isLastFetchedBitmapUpToDate_;
  }



  ALLEGRO_BITMAP * GameMenu::fetchBitmap()
  {
    if (!isLastFetchedBitmapUpToDate_) {
      if (bitmap_ != nullptr) {
        al_destroy_bitmap (bitmap_);
      }
      bitmap_ = al_create_bitmap (dimensions_.getWidth(), dimensions_.getWidth());
      ALLEGRO_BITMAP * targetBitmap (al_get_target_bitmap());
      al_set_target_bitmap (bitmap_);

      al_draw_bitmap (bitmapBackground_, 0, 0, 0);

      Sec & sec (gameData_.getSec());
      if (sec.getTarget() != nullptr) {
        CompanyIcon const * company (getIcon (*sec.getTarget()));
        al_draw_line (secIcon_.getCenter().getX(), secIcon_.getCenter().getY(), company->getCenter().getX(), company->getCenter().getY(), al_map_rgb (255, 0, 0), 10);
      }

      al_draw_bitmap (secIcon_.fetchBitmap(), secIcon_.getX(), secIcon_.getY(), 0);

      for (auto ci : companyIcons_) {
        al_draw_bitmap (ci->fetchBitmap(), ci->getX(), ci->getY(), 0);
      }

      al_draw_bitmap (menuBar_.fetchBitmap(), menuBar_.getX(), menuBar_.getY(), 0);

      if (ContextualMenuBitmapSingleton::getInstance().getContextualMenuBitmap() != nullptr) {
        I_LocatedInteractiveBitmap * menu (ContextualMenuBitmapSingleton::getInstance().getContextualMenuBitmap());
        al_draw_bitmap (menu->fetchBitmap(), menu->getX(), menu->getY(), 0);
      }

      if (!gameData_.isPlayerInTheGame().getValue()) {
        al_draw_bitmap (gameOverBitmap_.fetchBitmap(), gameOverBitmap_.getX(), gameOverBitmap_.getY(), 0);
      }



      isLastFetchedBitmapUpToDate_ = true;
      al_set_target_bitmap (targetBitmap);
    }
    return bitmap_;
  }



  I_BitmapView * GameMenu::getNext()
  {
    return next_;
  }



  void GameMenu::open()
  {
    ObserverListSingleton::getInstance().addObserver (menuBar_.getObservableId(), *this);

    for (auto ci : companyIcons_) {
      ObserverListSingleton::getInstance().addObserver (ci->getObservableId(), *this);
    }

    ObserverListSingleton::getInstance().addObserver (ContextualMenuBitmapSingleton::getInstance().getObservableId(), *this);
    ObserverListSingleton::getInstance().addObserver (secIcon_.getObservableId(), *this);
    ObserverListSingleton::getInstance().addObserver (gameData_.getSec().getObservableId(), *this);
    ObserverListSingleton::getInstance().addObserver (companyBeingCleaned_.getObservableId(), *this);
    ObserverListSingleton::getInstance().addObserver (gameData_.isPlayerInTheGame().getObservableId(), *this);
  }



  void GameMenu::close()
  {
    stopObserving();
  }



  void GameMenu::notifyObserver (I_ObservableId const & observableId)
  {
    isLastFetchedBitmapUpToDate_ = false; // TODO: should only set this to false when a change is detected
    if (&gameData_.getSec().getObservableId() == &observableId) {
      if (secTarget_ != gameData_.getSec().getTarget()) {
        isLastFetchedBitmapUpToDate_ = false;
      }
    }
    else if (&companyBeingCleaned_.getObservableId() == &observableId) {
      if (companyBeingCleaned_.getPointer() != nullptr) {
        next_ = viewData_.getCompanyMenu (*companyBeingCleaned_.getPointer());
      }
    }
    else if (&contextualMenuBitmapSingleton_.getObservableId() == &observableId) {
      if (contextualMenuBitmapSingleton_.getContextualMenuBitmap() != nullptr) {
        ObserverListSingleton::getInstance().addObserver (contextualMenuBitmapSingleton_.getContextualMenuBitmap()->getObservableId(), *this);
      }
    }
    else if (&gameData_.isPlayerInTheGame().getObservableId() == &observableId) {
      if (!gameData_.isPlayerInTheGame().getValue()) {
        isLastFetchedBitmapUpToDate_ = false;
      }
    }
  }
}