#ifndef PLATYPUS_ADKSTREAM_H
#define PLATYPUS_ADKSTREAM_H

#include <adk.h>
#include <Arduino.h>

namespace platypus
{
namespace impl
{

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

    // Android send/receive buffers
    static constexpr size_t INPUT_BUFFER_SIZE = 512;
    char adkInputBuffer_[INPUT_BUFFER_SIZE+1];
    char serialInputBuffer_[INPUT_BUFFER_SIZE+1];
    size_t serialInputIdx_;

    static constexpr size_t OUTPUT_BUFFER_SIZE = 576;
    char outputBuffer_[OUTPUT_BUFFER_SIZE+3];
    size_t outputIdx_;

private:
    AdkStream(ADK const &) = delete;
    void operator=(AdkStream const &) = delete;
};

} // impl
} // platypus

#endif // PLATYPUS_ADKSTREAM_H
