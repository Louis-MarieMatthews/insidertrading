// Launcher.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Library/Controller.h"

// TODO: divide the Library into 3 libraries (Model, View, Controller?)
// TODO: update Git's email address

using namespace it;

int main()
{
  Controller & program (Controller::getInstance());
  program.startProgram();
  return 0;
}