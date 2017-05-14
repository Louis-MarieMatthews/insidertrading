#include "GameMenu.h"

#include "allegro5\allegro_primitives.h"

#include "ObserverListSingleton.h"

namespace it
{
  std::set<CompanyIcon *> GameMenu::getCompanyIcons (GameData & gameData, DefaultContextualMenuBitmap * & parentContextualMenu)
  {
    std::set<CompanyIcon *> icons;
    std::set<Company *> const companies (gameData.getCompanies());
    for (auto c: companies) {
      icons.insert (new CompanyIcon (*c, c->getPosition()));
    }
    return icons;
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
    companyIcons_ (getCompanyIcons (viewData.getGameData(), contextualMenu_)),
    dimensions_ (dimensions),
    isLastFetchedBitmapUpToDate_ (false),
    gameData_ (viewData.getGameData()),
    menuBar_ (viewData.getGameData(), PlanarDimensions (dimensions.getWidth(), 40), PlanarPosition (0, 0)),
    next_ (this),
    secIcon_ (viewData.getGameData().getSec()),
    viewData_ (viewData)
  {
    ObserverListSingleton::getInstance().addObserver (menuBar_.getObservableId(), *this);

    for (auto ci : companyIcons_) {
      ObserverListSingleton::getInstance().addObserver (ci->getObservableId(), *this);
    }

    ObserverListSingleton::getInstance().addObserver (secIcon_.getObservableId(), *this);
    ObserverListSingleton::getInstance().addObserver (gameData_.getSec().getObservableId(), *this);
  }



  GameMenu::~GameMenu()
  {
    ObserverListSingleton::getInstance().removeObserver (menuBar_.getObservableId(), *this);
    
    for (auto ci : companyIcons_) {
      ObserverListSingleton::getInstance().removeObserver (ci->getObservableId(), *this);
    }

    ObserverListSingleton::getInstance().removeObserver (secIcon_.getObservableId(), *this);
    ObserverListSingleton::getInstance().removeObserver (gameData_.getSec().getObservableId(), *this);
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
    else {
      I_EventSensitiveLocatedBitmap * menu (ContextualMenuBitmapSingleton::getInstance().getContextualMenuBitmap());
      if (menu != nullptr) {
        menu->processEvent (&e);
      }

      for (auto ci : companyIcons_) {
        ci->processEvent (e);
      }
    }
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

      al_clear_to_color (al_map_rgb (100, 100, 100));

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
        I_EventSensitiveLocatedBitmap * menu (ContextualMenuBitmapSingleton::getInstance().getContextualMenuBitmap());
        al_draw_bitmap (menu->fetchBitmap(), menu->getX(), menu->getY(), 0);
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



  void GameMenu::notifyObserver (I_ObservableId const & observableId)
  {
    isLastFetchedBitmapUpToDate_ = false; // TODO: should only set this to false when a change is detected
    if (&gameData_.getSec().getObservableId() == &observableId) {
      if (secTarget_ != gameData_.getSec().getTarget()) {
        isLastFetchedBitmapUpToDate_ = false;
      }
    }
  }
}