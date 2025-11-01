#pragma once
#include "ifactorymodel.hpp"
#include "../model/nonlinearmodel.hpp"
#include <memory>

/**
 * @brief Factory class that produces NonLinearModel.
 */
class FactoryNonLinearModel : public IFactoryModel
{
public:
    /**
     * @brief Default constructor.
     */
    explicit FactoryNonLinearModel() = default;
    /**
     * @brief Virtual destructor for safe polymorphic usage.
     */
    ~FactoryNonLinearModel() override = default;

    /**
     * @brief Creates and returns a default NonLinearModel.
     *
     * @return A unique pointer to a newly created NonLinearModel instance.
     */
    std::unique_ptr<ISimulatedModel> getDefaultModel() const override
    { 
        constexpr double DEFUALT_A = 0.5;
        constexpr double DEFUALT_B = 0.5;
        constexpr double DEFUALT_C = 0.5;
        constexpr double DEFUALT_D = 0.5;
        return std::make_unique<NonLinearModel>(DEFUALT_A, DEFUALT_B, DEFUALT_C, DEFUALT_D); 
    }

};