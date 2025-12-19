#pragma once

class IRegulator
{
public:
    virtual ~IRegulator() = default;
    virtual double compute(double error, double time) = 0;

protected:
    static constexpr double K = 0.01;
};
