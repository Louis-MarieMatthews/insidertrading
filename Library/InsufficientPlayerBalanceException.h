#pragma once

#include <exception>

namespace it
{
  class InsufficientPlayerBalanceException : public std::exception
  {
  };
}