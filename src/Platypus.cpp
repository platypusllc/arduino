#include "platypus/Board.h"
#include "platypus/impl/Controller.h"
#include "Platypus.h"

using namespace platypus;

/** 
 * Creates a single instance of the controller singleton.
 * This instance is used within all instantiated controllers. 
 */
Controller& platypus::getController()
{
  return platypus::impl::Controller::instance();
}

Controller::~Controller() {}
DriveModule::~DriveModule() {}
DrivePort::~DrivePort() {}
Led::~Led() {}
MultiModule::~MultiModule() {}
MultiPort::~MultiPort() {}