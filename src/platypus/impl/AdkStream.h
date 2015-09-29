#ifndef PLATYPUS_ADKSTREAM_H
#define PLATYPUS_ADKSTREAM_H

#include <adk.h>
#include <Arduino.h>

namespace platypus
{
namespace impl
{

void adkStreamLoop(void *data);
void serialStreamLoop(void *data);

class AdkStream : public Stream
{
public:
    AdkStream(ADK &adk, Stream &serial);
    virtual ~AdkStream();

    int available() override;
    void flush() override;
    int peek() override;
    int read() override;
    size_t write(uint8_t val) override;
    size_t write(const uint8_t buf[], size_t len) override;

protected:
    ADK &adk_;
    Stream &serial_;

    // Stream send buffer.
    static constexpr size_t OUTPUT_BUFFER_SIZE = 576;
    char outputBuffer_[OUTPUT_BUFFER_SIZE+3];
    size_t outputIdx_;

private:
    AdkStream(AdkStream const &) = delete;
    void operator=(AdkStream const &) = delete;
};

} // impl
} // platypus

#endif // PLATYPUS_ADKSTREAM_H
