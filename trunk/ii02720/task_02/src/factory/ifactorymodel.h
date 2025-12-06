#pragma once

#include "../model/isimulatedmodel.h"
#include <memory>

class IFactoryModel
{
public:
    virtual std::unique_ptr<ISimulatedModel> createModel() const = 0;
    virtual ~IFactoryModel() = default;
};
