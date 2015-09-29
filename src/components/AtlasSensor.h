#ifndef PLATYPUS_ATLAS_SENSOR_H
#define PLATYPUS_ATLAS_SENSOR_H

#include "Components.h"

namespace platypus
{
    class AtlasSensor : public MultiModule 
    {
    public:
        AtlasSensor() = default;

        void begin(MultiPort &port) override;
        void loop() override;
        const String &name() const override;
    };
}

#endif // PLATYPUS_ATLAS_SENSOR_H
