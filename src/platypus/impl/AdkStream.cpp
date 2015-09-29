#include "AdkStream.h"

using namespace platypus::impl;

AdkStream::AdkStream(ADK &adk, Stream &serial)
: adk_(adk)
, serial_(serial)
, serialInputIdx_(0)
, outputIdx_(0)
{
    // Ensure the buffers will be null terminated strings.
    adkInputBuffer_[0] = '\0';
    adkInputBuffer_[sizeof(adkInputBuffer_) - 1] = '\0';
    serialInputBuffer_[0] = '\0';
    serialInputBuffer_[sizeof(serialInputBuffer_) - 1] = '\0';
    outputBuffer_[0] = '\0';
    outputBuffer_[sizeof(outputBuffer_) - 1] = '\0';
}

AdkStream::~AdkStream()
{

}

int AdkStream::available()
{
    // Intentionally short-circuit this so read fails fast.
    return 0;
}

void AdkStream::flush()
{
    // Add newline termination.
    size_t len = outputIdx_;
    outputBuffer_[len++] = '\r';
    outputBuffer_[len++] = '\n';
    outputBuffer_[len] = '\0';
    
    // Write string to USB.
    if (adk_.isReady())
        adk_.write(len, (uint8_t*)outputBuffer_);
    
    // Copy string to debugging console.
    serial_.print(outputBuffer_);

    // Clear output buffer.
    outputBuffer_[0] = '\0';
    outputIdx_ = 0;
}

int AdkStream::peek()
{
    // Intentionally short-circuit this so read fails fast.
    return -1;
}

int AdkStream::read()
{
    // Intentionally short-circuit this so read fails fast.
    return -1;
}

size_t AdkStream::write(uint8_t val)
{
    if (outputIdx_ < OUTPUT_BUFFER_SIZE)
    {
        outputBuffer_[outputIdx_] = val;
        ++outputIdx_;
        return 1;
    }
    else
    {
        return 0;
    }
}

size_t AdkStream::write(const uint8_t buf[], size_t len)
{
    len = min(len, OUTPUT_BUFFER_SIZE - outputIdx_);
    memcpy(outputBuffer_, buf, len);
    return len;
}
