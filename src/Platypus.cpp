#include "platypus/Board.h"
#include "platypus/impl/Controller.h"
#include "Platypus.h"

using namespace platypus;

void DriveModule::begin(DrivePort &port)
{
	// Do nothing.
}

void DriveModule::end()
{
	disarm();
}

void DriveModule::loop()
{
	// Do nothing.
}

void DriveModule::arm()
{
	// Do nothing.
}

void DriveModule::disarm()
{
	// Do nothing.
}

bool DriveModule::set(const String &param, const String &value)
{
	// By default, don't accept any commands.
	return false;
}

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