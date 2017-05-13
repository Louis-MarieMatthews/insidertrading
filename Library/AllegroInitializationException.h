#pragma once

#include <exception>
#include <string>

namespace it
{
  class AllegroInitializationException : public std::exception
  {
    const std::string message_;

  public:
    AllegroInitializationException (const std::string&);
    const char* what() const throw ();
  };
}