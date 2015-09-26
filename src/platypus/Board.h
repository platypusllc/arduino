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
Version const VERSION = {4, 2, 0};

// Pin definitions.
Led const LED = { 54, 55, 56 };

int const HALF_DUPLEX01 = 38;
int const HALF_DUPLEX23 = 39;

int const V_BATT = A3;
int const CHG_CTRL = 51;

int const LOOPBACK = 40;

int const PWR_INT = 44;
int const PWR_KILL = 46;

size_t const NUM_DRIVE_PORTS = 2;

DrivePort const DRIVE_PORTS[NUM_DRIVE_PORTS] = {
  { 50, 11, A8 }, // Motor 0 
  { 48, 12, A9 }  // Motor 1
};

size_t const NUM_MULTI_PORTS = 4;

MultiPort const MULTI_PORTS[NUM_MULTI_PORTS] = {
  { 32, 30, 36, 34, { 21, 2, 20, 3 }, 66,  A8, A7, HALF_DUPLEX01 }, // Sensor 0
  { 33, 31, 37, 35, { 19, 4, 18, 5 }, 67,  A9, A6, HALF_DUPLEX01 }, // Sensor 1
  { 24, 22, 28, 26, { 17, 6, 16, 7 }, 68, A10, A5, HALF_DUPLEX23 }, // Sensor 2
  { 25, 23, 29, 27, { 15, 8, 14, 9 }, 69, A11, A4, HALF_DUPLEX23 }  // Sensor 3
};

// TODO: Switch to using HardwareSerial.
USARTClass * const MULTI_SERIAL_PORTS[NUM_MULTI_PORTS] = {
  NULL,
  &Serial1,
  &Serial2,
  &Serial3,
};

// ADK USB Host configuration 
char const ADK_APPLICATION_NAME[] = "Platypus Server"; // the Android app
char const ADK_ACCESSORY_NAME[] = "Platypus Controller"; // the Arduino app
char const ADK_COMPANY_NAME[] = "Platypus LLC";
char const ADK_VERSION_NUMBER[] = "4.1.0"; // TODO: construct this programmatically.
char const ADK_SERIAL_NUMBER[] = "4";
char const ADK_URL[] = "http://senseplatypus.com";

// Time betweeen commands before we consider the Android
// server to be unresponsive.
size_t const ADK_TIMEOUT_MS = 500;

}
}

#endif // PLATYPUS_BOARD_H
