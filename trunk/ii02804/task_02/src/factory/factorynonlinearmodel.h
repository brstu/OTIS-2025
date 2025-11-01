#pragma once
#include "ifactorymodel.h"
#include "../model/nonlinearmodel.h"
#include <memory>

class FactoryNonlinearModel : public IFactoryModel<NonlinearModel> {
public:
    std::unique_ptr<NonlinearModel> create() const override {
        return std::make_unique<NonlinearModel>(0.9, 0.1, 0.05, 0.02);
    }
};
