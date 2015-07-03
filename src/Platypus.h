/**
 * Platypus Controller API
 * =======================
 *
 * Copyright (c) 2014, Platypus LLC. All rights reserved.
 */
#ifndef PLATYPUS_H
#define PLATYPUS_H

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
namespace Serial
{
    enum {
        RS232, RS485, RS422,
        NUM_MODES
    } Mode;
}

/**
 * Multi::Pin
 * ============
 * This is an enumeration of all of the GPIO pins available on the MultiPort.
 */ 
namespace Multi
{
    enum {
        RX_P, RX_N, TX_P, TX_N, ANA,
        NUM_PINS
    } Pin
}

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
    virtual bool set(String param, String value);
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
    virtual void rgb(int red, int green, int blue);
    virtual void R(int red);
    virtual int R();
    virtual void G(int green);
    virtual int G();
    virtual void B(int blue);
    virtual int B();

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
    virtual void command(float cmd);
    virtual float command() const;
    
    virtual bool isPowered() const;
    virtual void power(bool isPowered);
    virtual void powerOn();
    virtual void powerOff();
    
    virtual float current();

    virtual void reset();

protected:
    DrivePort() = default;
    virtual ~DrivePort() = 0;

    DrivePort(const &DrivePort) = delete;
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
    virtual bool beginSerial(int baud, Serial::Mode mode,
                             bool tx_enabled=false, bool rx_enabled=false);
    virtual void endSerial();
    virtual Stream &serial() const;

    virtual bool beginAnalog(float scale=1.0, float offset=0.0,
                             float min_val=-INF, float max_val=INF);
    virtual void endAnalog();
    virtual float analog() const;

    virtual bool beginDigital(Multi::Pin pin, bool is_output, int initial_value);
    virtual void endDigital(Multi::Pin pin);
    virtual bool read(Multi::Pin pin) const;
    virtual void write(Multi::Pin pin, bool value);

    virtual bool isPowered() const;
    virtual void power(bool isPowered);
    virtual void powerOn();
    virtual void powerOff();

    virtual float current() const;

    virtual void reset();

protected:
    MultiPort() = default;
    virtual ~MultiPort() = 0;

    MultiPort(const &MultiPort) = delete;
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
    virtual String name() const = 0;

protected:
    DriveModule() = default;
    virtual ~DriveModule() = 0;

    DriveModule(const &DriveModule) = delete;
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
    virtual String name() const = 0;

protected:
    MultiModule() = default;
    virtual ~MultiModule() = 0;

    MultiModule(const &MultiModule) = delete;
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
    virtual int numDrives() const;
    virtual bool setDriveModule(int which, DriveModule &device);
    virtual bool setDriveModules(DriveModule device[]);

    virtual MultiPort &multi(int which);
    virtual int numMultis() const;
    virtual bool setMultiModule(int which, MultiModule &device);
    virtual bool setMultiModules(MultiModule device[]);

    virtual Led& led() const;
    virtual float battery() const;

    virtual Stream &command() const;
    virtual Stream &console() const;

protected:
    Controller() = default;
    virtual ~Controller() = 0;

    Controller(const &Controller) = delete;
    void operator=(const Controller&) = delete;
};

/** 
 * Returns a reference to the Platypus Controller.
 */
static Controller &getController();

}

#endif //PLATYPUS_H
