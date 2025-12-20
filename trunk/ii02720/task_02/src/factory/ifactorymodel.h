#pragma once

#include "../model/isimulatedmodel.h"
#include <memory>

class IFactoryModel123
{
public:
    virtual std::unique_ptr<ISimulatedModel> getModel() const = 0;
    virtual ~IFactoryModel() = default;

};

