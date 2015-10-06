/**
 * Copyright (c) 2014, Platypus LLC. All rights reserved.
 */
#ifndef PLATYPUS_MULTIPORT_H
#define PLATYPUS_MULTIPORT_H

#include "Platypus.h"
#include "platypus/Board.h"

namespace platypus
{
namespace impl
{

namespace Pin {
    // This pin enumeration follows order of the MultiCon pinout.
    enum {
        V5   = 0x01,
        RX_P = 0x02,
        RX_N = 0x04,
        V12  = 0x08,
        TX_P = 0x10,
        TX_N = 0x20,
        ANA  = 0x40,
        GND  = 0x80
    } Mask;
}

class MultiPort : public ::platypus::MultiPort
{
public:
    void begin(uint8_t port);
    void end();

    Stream *beginSerial(int baud, SerialMode mode,
                        bool tx_enabled=true, bool rx_enabled=true) override;
    void endSerial() override;
    Stream &serial() override;

    int beginAnalog(float scale=1.0, float offset=0.0,
                    float min_val=-std::numeric_limits<float>::infinity(),
                    float max_val=std::numeric_limits<float>::infinity()) override;
    void endAnalog() override;
    float analog() const override;

    int beginDigital(MultiPin pin, bool is_output, int initial_value) override;
    void endDigital(MultiPin pin) override;
    bool read(MultiPin pin) const override;
    void write(MultiPin pin, bool value) override;

    void power(bool isPowered) override;
    bool isPowered() const override;

    float current() const override;

    void reset() override;

protected:
    MultiPort();
    virtual ~MultiPort();

    bool isPowered_;
    uint8_t pinUsage_;
    const ::platypus::board::MultiConfig *port_;

private:
    MultiPort(MultiPort const &) = delete;
    void operator=(MultiPort const &) = delete;

    friend ::platypus::Controller;
};

}
}

#endif // PLATYPUS_MULTIPORT_H