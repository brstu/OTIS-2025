#pragma once
#include "../model/isimulatedmodel.hpp"
#include <memory>

/**
 * @brief Interface for factory classes that produce simulated models.
 *
 * This abstract class defines a contract for creating default instances
 * of ISimulatedModel.
 */
class IFactoryModel
{
public:
    /**
     * @brief Virtual destructor for safe polymorphic usage.
     */
    virtual ~IFactoryModel() = default;

    /**
     * @brief Creates and returns a default simulated model.
     *
     * @return A unique pointer to a newly created ISimulatedModel instance.
     */
    virtual std::unique_ptr<ISimulatedModel> getDefaultModel() const = 0;

};