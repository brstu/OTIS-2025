#pragma once
#include "ifactorymodel.h"
#include "../model/linearmodel.h"
#include <memory>

class FactoryLinearModel : public IFactoryModel<LinearModel> {
public:
    std::unique_ptr<LinearModel> create() const override {
        return std::make_unique<LinearModel>(0.9, 0.1);
    }
};
