#include "AllegroInitializationException.h"

namespace it
{
  AllegroInitializationException::AllegroInitializationException (const std::string& message) :
    message_ (message)
  {
  }



  const char* AllegroInitializationException::what() const throw()
  {
    return message_.c_str();
  }
}