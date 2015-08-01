#ifndef PLATYPUS_BOARD_H
#define PLATYPUS_BOARD_H

#include <Arduino.h>

namespace platypus
{
namespace board
{

// Version structure.
struct Version
{ 
  int major;
  int minor;
  int patch;
};

// Board type definitions
struct Led
{ 
  int r;
  int g;
  int b;
};

struct DrivePort
{ 
  int enable;
  int servo;
  int current;
};

struct MultiPort
{
  int rx_disable;
  int tx_enable;
  int rs485_te;
  int rs485_232;
  int gpio[4];
  int pwr_enable;
  int pwr_current;
  int analog;
  int half_duplex;
};

enum GPIO
{
  RX_POS = 0,
  RX_NEG = 1,
  TX_POS = 2,
  TX_NEG = 3
};

// TODO: move this to an external CPP class.

// Board version definition.
const Version VERSION = {4, 1, 0}

// Pin definitions.
const Led LED = { 54, 55, 56 };

const int HALF_DUPLEX01 = 38;
const int HALF_DUPLEX23 = 39;

const int V_BATT = A3;
const int CHG_CTRL = 51;

const int LOOPBACK = 40;

const int PWR_INT = 44;
const int PWR_KILL = 46;

const size_t NUM_DRIVE_PORTS = 2;

const DrivePort DRIVE_PORTS[NUM_DRIVE_PORTS] = {
  { 50, 11, A8 }, // Motor 0 
  { 48, 12, A9 }  // Motor 1
};

const size_t NUM_MULTI_PORTS = 4;

const MultiPort MULTI_PORTS[NUM_MULTI_PORTS] = {
  { 32, 30, 36, 34, { 21, 2, 20, 3 }, 66,  A8, A7, HALF_DUPLEX01 }, // Sensor 0
  { 33, 31, 37, 35, { 19, 4, 18, 5 }, 67,  A9, A6, HALF_DUPLEX01 }, // Sensor 1
  { 24, 22, 28, 26, { 17, 6, 16, 7 }, 68, A10, A5, HALF_DUPLEX23 }, // Sensor 2
  { 25, 23, 29, 27, { 15, 8, 14, 9 }, 69, A11, A4, HALF_DUPLEX23 }  // Sensor 3
};

// TODO: Switch to using HardwareSerial.
USARTClass *MULTI_SERIAL_PORTS[NUM_MULTI_PORTS] = {
  NULL,
  &Serial1,
  &Serial2,
  &Serial3,
};

// ADK USB Host configuration 
const char ADK_APPLICATION_NAME[] = "Platypus Server"; // the Android app
const char ADK_ACCESSORY_NAME[] = "Platypus Controller"; // the Arduino app
const char ADK_COMPANY_NAME[] = "Platypus LLC";
const char ADK_VERSION_NUMBER[] = "4.1.0"; // TODO: construct this programmatically.
const char ADK_SERIAL_NUMBER[] = "4";
const char ADK_URL[] = "http://senseplatypus.com";

// Time betweeen commands before we consider the Android
// server to be unresponsive.
const size_t ADK_TIMEOUT_MS = 500;

}
}

#endif // PLATYPUS_BOARD_H
