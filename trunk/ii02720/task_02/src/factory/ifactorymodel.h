#pragma once

#include "../model/isimulatedmodel.h"
#include <memory>

class IFactoryModel_2720
{
public:
    virtual std::unique_ptr<ISimulatedModel_2720> getModel() const = 0;
    virtual ~IFactoryModel_2720() = default;
};