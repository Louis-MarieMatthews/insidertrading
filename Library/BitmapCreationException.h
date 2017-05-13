#pragma once

#include <exception>

namespace it
{
  class BitmapCreationException : public std::exception
  {
  public:
    BitmapCreationException();
    ~BitmapCreationException();
    const char* what() const throw ();
  };
}