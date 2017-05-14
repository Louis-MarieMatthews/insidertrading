#include "CompanyMap.h"

#include <string>
#include <fstream>

#include "FloorCompanyMapItem.h"
#include "WallCompanyMapItem.h"

namespace it
{
  CompanyMap::CompanyMap()
  {
    std::ifstream file;
    file.open ("../gamefiles/maps/map0.map", std::ios::in);
    if (!file) {
      throw std::exception(); // TODO: custom ex
    }

    std::string line;
    unsigned short currentRow (0);
    for (unsigned short currentRow (0); currentRow < 1; currentRow++)
    {
      getline (file, line);
      
      for (unsigned short currentColumn (0); currentColumn < N_COLUMNS_; currentColumn++) {
        std::string item (line.substr (currentColumn, 1));
        if (item == "0") {
          items_[currentRow][currentColumn] = new FloorCompanyMapItem();
        }
        else if (item == "1") {
          items_[currentRow][currentColumn] = new WallCompanyMapItem();
        }
      }
    }
  }



  CompanyMap::~CompanyMap()
  {
  }
}