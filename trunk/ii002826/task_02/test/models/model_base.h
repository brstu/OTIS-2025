#ifndef MODEL_BASE_H
#define MODEL_BASE_H

class ISimulatedModel {
public:
    virtual void simulate(double initial_value, double input, int time_steps) const = 0;
    virtual ~ISimulatedModel() = default;
};

class IModelFactory {
public:
    virtual std::unique_ptr<ISimulatedModel> createModel() const = 0;
    virtual ~IModelFactory() = default;
};

#endif