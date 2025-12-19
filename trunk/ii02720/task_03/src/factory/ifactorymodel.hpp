#pragma once
#include "../model/isimulatedmodel.hpp"
#include <memory>

class IFactoryModel
{
public:
    virtual ~IFactoryModel() = default;
    virtual std::unique_ptr<ISimulatedModel> createModel() const = 0;
};
