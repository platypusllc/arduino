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

Controller::~Controller()
{
    // Do nothing.
}

DriveModule::~DriveModule()
{
    // Do nothing.
}

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

DrivePort::~DrivePort() {}

void DrivePort::drivePowerOn()
{
    this->drivePower(true);
}

void DrivePort::drivePowerOff()
{
    this->drivePower(false);
}

void DrivePort::servoPowerOn()
{
    this->servoPower(true);
}

void DrivePort::servoPowerOff()
{
    this->servoPower(false);
}

Led::~Led()
{
    // Do nothing.
}

MultiModule::~MultiModule()
{
    // Do nothing.
}

MultiPort::~MultiPort()
{
    // Do nothing.
}

void MultiPort::powerOn()
{
    this->power(true);
}

void MultiPort::powerOff()
{
    this->power(false);
}

class DummyDrivePort : public DrivePort
{
    void command(float cmd) override
    {
        // Do nothing
    }
    float command() const override
    {
        return 0.0;
    }
    
    void drivePower(bool isPowered) override
    {
        // Do nothing.
    }
    
    bool isDrivePowered() const override
    {
        return false;
    }

    void servoPower(bool isPowered) override
    {
        // Do nothing.
    }

    bool isServoPowered() const override
    {
        return false;
    }
    
    float current() const override
    {
        return 0.0;
    }

    void reset() override
    {
        // Do nothing.
    }
};

DrivePort &DrivePort::dummy()
{
    static DummyDrivePort dummy;
    return dummy;
}

class DummyStream : public Stream
{
public:
    int available() override
    {
        return 0;
    }

    void flush() override
    {
        // Do nothing.
    }

    int peek() override
    {
        return 255;
    }

    int read() override
    {
        return 255;
    }

    size_t write(uint8_t val) override
    {
        return 0;
    }

    static DummyStream &instance()
    {
        static DummyStream dummy;
        return dummy;
    }
};

class DummyMultiPort : public MultiPort
{
    Stream *beginSerial(int baud, SerialMode mode,
                        bool tx_enabled=true, bool rx_enabled=true) override
    {
        return nullptr;    
    }

    void endSerial() override
    {
        // Do nothing.
    }

    Stream &serial() override
    {
        return DummyStream::instance();
    }

    int beginAnalog(float scale=1.0, float offset=0.0,
                    float min_val=-std::numeric_limits<float>::infinity(),
                    float max_val=std::numeric_limits<float>::infinity()) override
    {
        return -1;
    }

    void endAnalog() override
    {
        // Do nothing.
    }

    float analog() const override
    {
        return 0.0f;
    }

    int beginDigital(MultiPin pin, bool is_output, int initial_value) override
    {
        return -1;
    }

    void endDigital(MultiPin pin) override
    {
        // Do nothing.
    }

    bool read(MultiPin pin) const override
    {
        return false;
    }

    void write(MultiPin pin, bool value) override
    {
        // Do nothing.
    }

    void power(bool isPowered) override
    {
        // Do nothing.
    }

    bool isPowered() const override
    {
        return false;
    }

    float current() const override
    {
        return 0.0f;
    }

    void reset() override
    {
        // Do nothing.
    }
};

MultiPort &MultiPort::dummy()
{
    static DummyMultiPort dummy;
    return dummy;
}