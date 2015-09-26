/**
 * Platypus Controller API
 * =======================
 *
 * Copyright (c) 2014, Platypus LLC. All rights reserved.
 */
#ifndef PLATYPUS_H
#define PLATYPUS_H

#include <Arduino.h>
#include <limits>

// Currently, only the Due and similar boards are supported.
#if !defined(ARDUINO_ARCH_SAM)
    #error “This library only supports boards with a SAM processor.”
#endif

namespace platypus
{

/**
 * Serial::Mode
 * ============
 * This is an enumeration of all the serial modes supported by the MultiPort.
 */ 
enum class SerialMode
{
    RS232,
    RS485,
    RS422
};

/**
 * Multi::Pin
 * ============
 * This is an enumeration of all of the GPIO pins available on the MultiPort.
 */ 
enum class MultiPin
{
  RX_P,
  RX_N,
  TX_P,
  TX_N,
  ANALOG
};

/**
 * Status
 * ======
 * This is an enumeration of all the connectivity states to the Platypus Server.
 */
enum Status
{
  /** There is no ADK USB device currently plugged in. */
  DISCONNECTED,
  /** There is an ADK USB device detected, but it is unresponsive. */
  CONNECTED,
  /** There is a Platypus Server currently communicating. */
  RUNNING  
};

/**
 * Configurable
 * ============
 * The configurable interface is defined for objects that can receive
 * parameters from JSON key-value tuples.  These tuples are pairs of
 * strings that can be passed through the console or from a server.
 */
class Configurable
{
public:     
    virtual bool set(const String &param, const String &value);
};

/**
 * LED
 * ===
 * This is the interface for a tri-color LED, which can be configured to
 * display a range of colors.  This LED can be set directly, or configured
 * through Configurable key-value pairs.
 */
class Led 
{ 
public:
    virtual void rgb(float red, float green, float blue);
    virtual void R(float red);
    virtual float R();
    virtual void G(float green);
    virtual float G();
    virtual void B(float blue);
    virtual float B();

protected:
    Led() = default;
    virtual ~Led() = 0;

    Led(const Led&) = delete;
    void operator=(const Led&) = delete;
};

/**
 * DrivePort
 * =========
 * This class represents the functionality of one of the driveports on a
 * Platypus Controller.  The driveport can be used to command a servo or
 * a motor controller such as an ESC.
 */
class DrivePort
{ 
public:
    /**
     * Set a servo command between -1.0 (full reverse) and 1.0 (full forward).
     */
    virtual void command(float cmd);
    virtual float command() const;
    
    /**
     * Turns on and off the high-power supply pin of this port.
     *
     * This toggles the high-power pin, which can provide up to 25A at the
     * available battery voltage (+VBatt).
     */
    virtual bool isPowered() const;
    virtual void power(bool isPowered);
    virtual void powerOn();
    virtual void powerOff();
    
    virtual float current();

    virtual void reset();

protected:
    DrivePort() = default;
    virtual ~DrivePort() = 0;

    DrivePort(const DrivePort&) = delete;
    void operator=(const DrivePort&) = delete;
};

/**
 * MultiPort
 * =========
 * This class represents the functionality of one of the multiports on a
 * Platypus Controller.  The multiport can be configured for serial, digital,
 * or analog I/O operation, or certain combinations of the above.  It also
 * includes two mechanisms for powering electronics, an always-on, current-
 * limited +5V, and a switchable +VBat.
 */

class MultiPort
{
public:
    /**
     * Initialize the serial device for this port using given settings.
     *
     * If the pins are already in use or the settings are invalid,
     * this will return a `nullptr`.  Otherwise, it will return a `Stream`
     * that can be used to read and write from the port.
     */
    virtual Stream *beginSerial(int baud, SerialMode mode,
                                bool tx_enabled=true, bool rx_enabled=true);
    virtual void endSerial();
    virtual Stream &serial() const;

    /**
     * Initialize the analog pin for this port using the given settings.
     *
     * If the pins are already in use or the settings are invalid, this will
     * return a value of `0`.  Otherwise, it will return the pin ID of the pin
     * that is being used.  This is not required anywhere, but can be used for
     * direct Arduino pin IO operations if desired.
     *
     * This internally uses the Arduino's analog read and write functions, but
     * applies a settable scale and offset to the raw reading and makes the
     * result available through the `analog()` call.
     *
     * The scale=1.0, offset=0.0 settings will return the pin voltage in volts.
     */
    virtual int beginAnalog(float scale=1.0, float offset=0.0,
                            float min_val=-std::numeric_limits<float>::infinity(),
                            float max_val=std::numeric_limits<float>::infinity());
    virtual void endAnalog();
    virtual float analog() const;

    /**
     * Initialize a digital pin for this port using the given settings.
     *
     * If the pins are already in use or the settings are invalid, this will
     * return a value of `0`.  Otherwise, it will return the pin ID of the pin
     * that is being used.  This is not required anywhere, but can be used for
     * direct Arduino pin IO operations if desired.
     */
    virtual int beginDigital(MultiPin pin, bool is_output, int initial_value);
    virtual void endDigital(MultiPin pin);
    virtual bool read(MultiPin pin) const;
    virtual void write(MultiPin pin, bool value);

    /**
     * Turns on and off the high-power supply pin of this port.
     *
     * This toggles the high-power pin, which can provide up to 4A at the
     * available battery voltage (+VBatt).
     */
    virtual void power(bool isPowered);
    virtual bool isPowered() const;
    virtual void powerOn();
    virtual void powerOff();

    /**
     * Returns the current draw (in amps) on the high-power pin of this port.
     */
    virtual float current() const;

    /**
     * Disables all IO and puts the port into its default "safe" settings.
     */
    virtual void reset();

protected:
    MultiPort() = default;
    virtual ~MultiPort() = 0;

    MultiPort(const MultiPort&) = delete;
    void operator=(const MultiPort&) = delete;
};

/**
 * DriveModule
 * ===========
 * Modules represent device-specific control code that can be attached to a
 * DrivePort or a MultiPort.  This is where the majority of device logic is
 * normally contained.
 */
class DriveModule : public Configurable
{ 
public:
    virtual void begin(DrivePort &port);
    virtual void end();
    virtual void loop();
    virtual void arm();
    virtual void disarm();
    virtual const String &name() const = 0;

protected:
    DriveModule() = default;
    virtual ~DriveModule() = 0;

    DriveModule(const DriveModule&) = delete;
    void operator=(const DriveModule&) = delete;
};

/**
 * MultiModule
 * ===========
 * Modules represent device-specific control code that can be attached to a
 * DrivePort or a MultiPort.  This is where the majority of device logic is
 * normally contained.
 */
class MultiModule : public Configurable
{ 
public:
    virtual void begin(MultiPort &port);
    virtual void end();
    virtual void loop();
    virtual const String &name() const = 0;

protected:
    MultiModule() = default;
    virtual ~MultiModule() = 0;

    MultiModule(const MultiModule&) = delete;
    void operator=(const MultiModule&) = delete;
};

/**
 * Controller
 * ==========
 * This class represents the hardware abstraction for a Platypus Controller.
 * The controller provides an interface from the Android server to hardware
 * devices such as motors and sensors.
 */
class Controller : public Configurable
{
public:
    virtual void begin();
    virtual void end();

    virtual DrivePort &drive(int which);
    virtual const DrivePort &drive(int which) const;
    virtual int numDrives() const;
    virtual bool setDriveModule(int which, DriveModule &device);

    virtual MultiPort &multi(int which);
    virtual const MultiPort &multi(int which) const;
    virtual int numMultis() const;
    virtual bool setMultiModule(int which, MultiModule &device);

    virtual Led& led();
    virtual const Led&led() const;
    virtual float battery() const;
    virtual Status status() const;
    virtual bool isConnected() const;

    virtual Stream &command() const;
    virtual Stream &console() const;

protected:
    Controller() = default;
    virtual ~Controller() = 0;

    Controller(const Controller&) = delete;
    void operator=(const Controller&) = delete;
};

/** 
 * Returns a reference to the Platypus Controller.
 */
Controller &getController();

}

#endif //PLATYPUS_H
