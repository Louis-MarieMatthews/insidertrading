#include "CompanyMap.h"

#include <cmath>
#include <fstream>
#include <string>

#include "Company.h"
#include "DocumentMapItem.h"
#include "FloorCompanyMapItem.h"
#include "WallCompanyMapItem.h"

namespace it
{
  PlanarPosition CompanyMap::move (Direction const & direction, PlanarPosition const & position)
  {
    PlanarPosition targetPosition (0, 0);
    switch (direction) {
    case up:
      targetPosition.update (PlanarPosition (position.getX(), position.getY() + speed_));
      break;         
                     
    case down:       
      targetPosition.update (PlanarPosition (position.getX(), position.getY() - speed_));
      break;         
                     
    case left:       
      targetPosition.update (PlanarPosition (position.getX() - speed_, position.getY()));
      break;         
                     
    case right:      
      targetPosition.update (PlanarPosition (position.getX() + speed_, position.getY()));
      break;
    }
    I_CompanyMapItem * targetDestination (items_[targetPosition.getX()][targetPosition.getY()]);
    if (targetDestination == nullptr || targetDestination->isTraversable()) {
      return targetPosition;
    }
    else {
      return position;
    }
  }



  CompanyMap::CompanyMap (I_GameData & gameData, Company & company, std::string const & filename) :
    bribedEmployee_ (new BribedEmployee (gameData, bribedEmployeePosition_, company)),
    bribedEmployeePosition_ (3, 3),
    company_ (company),
    playerEntryPoint_ (1, 1),
    playerPosition_ (1, 1),
    speed_ (1),
    filename_ (filename)
  {
    reset();
  }



  CompanyMap::~CompanyMap()
  {
  }



  I_CompanyMapItem const * CompanyMap::getItem (unsigned short const & row, unsigned short const & column) const
  {
    return items_[row][column];
  }



  unsigned short const & CompanyMap::getNumberOfRows() const
  {
    return N_ROWS_;
  }



  unsigned short const & CompanyMap::getNumberOfColums() const
  {
    return N_COLUMNS_;
  }



  PlanarPosition const & CompanyMap::getPlayerEntryPoint() const
  {
    return playerEntryPoint_;
  }



  PlanarPosition const & CompanyMap::getPlayerPosition() const
  {
    return playerPosition_;
  }



  BribedEmployee * CompanyMap::getBribedEmployee()
  {
    return bribedEmployee_;
  }



  void CompanyMap::movePlayer (Direction const & direction)
  {
    playerPosition_.update (move (direction, PlanarPosition (playerPosition_.getX(), playerPosition_.getY())));
    I_CompanyMapItem * & destination (items_[playerPosition_.getX()][playerPosition_.getY()]);
    if (destination != nullptr && destination->isDocument()) {
      documents_.erase (destination);
      destination = nullptr;
    }
  }



  void CompanyMap::moveBribedEmployee (Direction const & direction)
  {
    bribedEmployeePosition_.update (move (direction, PlanarPosition (bribedEmployeePosition_.getX(), bribedEmployeePosition_.getY())));
    I_CompanyMapItem * & destination (items_[bribedEmployeePosition_.getX()][bribedEmployeePosition_.getY()]);
    if (destination != nullptr && destination->isDocument()) {
      documents_.erase (destination);
      destination = nullptr;
    }
  }



  ObservableSet<I_CompanyMapItem *> const & CompanyMap::getDocuments() const
  {
    return documents_;
  }



  //void CompanyMap::movePlayerTowards (PlanarPosition const & target) const
  //{
  //  puts (std::string (std::to_string (rand() % 20) + "  ::  " + std::to_string (playerPosition_.getX()) + "  :  " + std::to_string (playerPosition_.getY())).c_str());
  //  //puts (std::string (std::to_string (rand() % 20) + "  ::  " + std::to_string (target.getX()) + "  :  " + std::to_string (target.getY())).c_str());
  //  PlanarPosition const start (playerPosition_);
  //  PlanarPosition * newPosition (nullptr);

  //  float const x0 (playerPosition_.getX());
  //  float const y0 (playerPosition_.getY());
  //  float const x1 (target.getX());
  //  float const y1 (target.getY());

  //  if (x0 == x1 && y0 == y1) {
  //    return;
  //  }
  //  else if (x0 == x1) {
  //    if (abs (y0 - y1) < speed_) {
  //      newPosition = new PlanarPosition (x1, y1);
  //    }
  //    else if (y0 > y1) {
  //      newPosition = new PlanarPosition (x1, y0 - speed_);
  //    }
  //    else {
  //      newPosition = new PlanarPosition (x1, y0 + speed_);
  //    }
  //  }
  //  else if (y0 == y1) {
  //    if (abs(x0 - x1) < speed_) {
  //      newPosition = new PlanarPosition (x1, y1);
  //    }
  //    else if (x0 > x1) {
  //      newPosition = new PlanarPosition (x0 - speed_, y1);
  //    }
  //    else {
  //      newPosition = new PlanarPosition (x0 + speed_, y1);
  //    }
  //  }
  //  else {
  //    float a ((y0 - y1) / (x0 - x1));
  //    float b (y0 - a * x0);

  //    // TEMP //
  //    if (x0 > x1) {
  //      int const x (x0 - speed_);
  //      int const y (a * x + b);
  //      newPosition = new PlanarPosition (x, y);
  //    }
  //    else {
  //      int const x (x0 + speed_);
  //      int const y (a * x + b);
  //      newPosition = new PlanarPosition (x, y);
  //    }
  //    // TEMP //
  //    
  //    //int sgn = x0 > x1 ? -1 : 1;
  //    //float x (x0 + sgn * sqrt (pow (speed_, 2) / (pow ((a + b), 2) + 1)));
  //    //float y (a * x + b);
  //    //newPosition = new PlanarPosition (x, y);

  //    //float A (1 + pow (a, 2));
  //    //float B (2 * pow (a, 2) * x0 + 2 * a * b);
  //    //float C (pow (a, 2) * pow (x0, 2) + 2 * a * x0 + pow (b, 2) - pow (speed_, 2));
  //    //float delta (pow (B, 2) - 4 * A * C);

  //    //// We assume delta is always above 0
  //    //if (delta <= 0) {
  //    //  throw std::exception();
  //    //}

  //    //if (x0 < x1) {
  //    //  int x (-B + sqrt (delta) / 2 * A);
  //    //  int y (a * x + b);
  //    //  newPosition = new PlanarPosition (x, y);
  //    //}
  //    //else {
  //    //  int x (-B - sqrt (delta) / 2 * A);
  //    //  int y (a * x + b);
  //    //  newPosition = new PlanarPosition (x, y);
  //    //}
  //  }

  //  if (newPosition == nullptr) { // if it's the case there's an error in the code.
  //    delete newPosition;
  //    throw std::exception(); // 
  //  }

  //  if (target.isNearby (*newPosition, speed_)) {
  //    playerPosition_.update (target);
  //  }
  //  else {
  //    playerPosition_.update (*newPosition);
  //  }

  //  delete newPosition;
  //}


  
  void CompanyMap::reset()
  {
    std::ifstream file;
    file.open ((std::string ("../gamefiles/maps/" + filename_)).c_str(), std::ios::in);
    if (!file) {
      throw std::exception(); // TODO: custom ex
    }

    std::string line;
    unsigned short currentRow (0);
    for (unsigned short currentRow (0); currentRow < N_ROWS_; currentRow++)
    {
      getline (file, line);
      
      for (unsigned short currentColumn (0); currentColumn < N_COLUMNS_; currentColumn++) {
        std::string item (line.substr (currentColumn, 1));
        if (item == "0") {
          items_[currentColumn][currentRow] = nullptr;
        }
        else if (item == "1") {
          items_[currentColumn][currentRow] = new WallCompanyMapItem (PlanarPosition (currentColumn, currentRow));
        }
        else if (item == "2") {
          items_[currentColumn][currentRow] = new DocumentMapItem (PlanarPosition (currentColumn, currentRow));
          documents_.insert (items_[currentColumn][currentRow]);
        }
        else if (item == "3") {
          items_[currentColumn][currentRow] = nullptr;
          playerEntryPoint_ = PlanarPosition (currentColumn, currentRow);
        }
      }
    }
  }
}