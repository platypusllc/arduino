#include "Controller.h"
#include "Communication.h"
#include "Board.h"
#include <Arduino.h>

using platypus::impl::Controller;

uint32_t swap(uint32_t bytes)
{
  return ((bytes << 24) & 0xFF000000)
         | ((bytes <<  8) & 0x00FF0000)
         | ((bytes >>  8) & 0x0000FF00)
         | ((bytes >> 24) & 0x000000FF);
}

void driveLoop(void *data)
{
  size_t driveIdx = (size_t)data;
  Controller &controller = platypus::getController();
  while (true)
  {
    controller.driveModules_[driveIdx].loop();
  }
}

void multiLoop(void *data)
{
  size_t multiIdx = (size_t)data;
  Controller &controller = platypus::getController();
  while (true)
  {
    controller.multiModules_[multiIdx].loop();
  }
}

Controller::Controller()
: adk_(&usb_,
       platypus::board::ADK_COMPANY_NAME, platypus::board::ADK_APPLICATION_NAME,
       platypus::board::ADK_ACCESSORY_NAME, platypus::board::ADK_VERSION_NUMBER,
       platypus::board::ADK_URL, platypus::board::ADK_SERIAL_NUMBER);
, Stream_(adk_, Serial),
, serverStatus_(platypus::ServerStatus::DISCONNECTED)
{
  // Do nothing.
}

Controller::~Controller()
{
  // Do nothing.
  // This should never be reached, Controller is only instantiated as a singleton.
}

Controller &Controller::instance()
{
  static Controller instance;
  return instance;
}

Controller::begin()
{
  // Latch power shutdown line high to keep board from turning off.
  pinMode(platypus::board::PWR_KILL, OUTPUT);
  digitalWrite(platypus::board::PWR_KILL, HIGH);

  // Initialize serial console.
  Serial.begin(115200);

  // Print startup header to the command stream.
  sendHeader(this->command());

  // Start update loops for each drive module.
  for (size_t driveIdx = 0; driveIdx < platypus::board::NUM_DRIVE_PORTS; ++driveIdx)
  {
    Scheduler.start(driveLoop, (void *)driveIdx);
  }

  // Start update loops for each multi module.
  for (size_t multiIdx = 0; multiIdx < platypus::board::NUM_DRIVE_PORTS; ++multiIdx)
  {
    Scheduler.start(multiLoop, (void *)multiIdx);
  }

  // Create update loops for command stream.
  Scheduler.start(platypus::impl::commandLoop, (void *)this);
}
