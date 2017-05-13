#include "GameMenu.h"

#include "ObserverListSingleton.h"

namespace it
{
  std::set<CompanyIcon *> GameMenu::getCompanyIcons (GameData & gameData)
  {
    std::set<CompanyIcon *> icons;
    std::set<Company> companies (gameData.getCompanies());
    for (auto c : companies) {
      icons.insert (new CompanyIcon (c.getPosition()));
    }
    return icons;
  }



  GameMenu::GameMenu (ViewData & viewData, PlanarDimensions const & dimensions) :
    companyIcons_ (getCompanyIcons (viewData.getGameData())),
    dimensions_ (dimensions),
    isLastFetchedBitmapUpToDate_ (false),
    gameData_ (viewData.getGameData()),
    menuBar_ (viewData.getGameData(), PlanarDimensions (dimensions.getWidth(), 40), PlanarPosition (0, 0)),
    next_ (this),
    viewData_ (viewData)
  {
    ObserverListSingleton::getInstance().addObserver (menuBar_.getObservableId(), *this);

    for (auto ci : companyIcons_) {
      ObserverListSingleton::getInstance().addObserver (ci->getObservableId(), *this);
    }
  }



  GameMenu::~GameMenu()
  {
    ObserverListSingleton::getInstance().removeObserver (menuBar_.getObservableId(), *this);
    
    for (auto ci : companyIcons_) {
      ObserverListSingleton::getInstance().removeObserver (ci->getObservableId(), *this);
    }
  }



  I_ObservableId const & GameMenu::getObservableId() const
  {
    return observableId_;
  }



  void GameMenu::reset()
  {
    next_ = this;
    menuBar_.reset();
  }



  void GameMenu::processEvent (I_AllegroEventAdapter const & e)
  {
    if (e.wasEscapeKeyPressed()) {
      next_ = viewData_.getMainMenu();
    }
    else {
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

      al_clear_to_color (al_map_rgb (33, 55, 170));

      for (auto ci : companyIcons_) {
        al_draw_bitmap (ci->fetchBitmap(), ci->getX(), ci->getY(), 0);
      }

      al_draw_bitmap (menuBar_.fetchBitmap(), menuBar_.getX(), menuBar_.getY(), 0);

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
    isLastFetchedBitmapUpToDate_ = false;
  }
}