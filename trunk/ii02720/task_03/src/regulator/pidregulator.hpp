#pragma once
#include "iregulator.hpp"
#include <array>

class PIDRegulator : public IRegulator
{
public:
    PIDRegulator()
    {
        m_errors.fill(0);
        m_controls.fill(0);
    }
    
    ~PIDRegulator() override = default;

    double compute(double error, double time) override
    {
        int idx = static_cast<int>(time / T0);
        m_errors[idx % 3] = error;

        m_controls[1] = q0 * m_errors[0] + q1 * m_errors[1] + q2 * m_errors[2];
        double control = m_controls[0] + m_controls[1];
        m_controls[0] = m_controls[1];
        
        return control;
    }

private:
    static constexpr double T = 0.05;
    static constexpr double T0 = 1.0;
    static constexpr double TD = 10.0;

    static constexpr double q0 = K * (1 + TD / T0);
    static constexpr double q1 = -K * (1 + 2 * (TD / T0) - (T0 / T));
    static constexpr double q2 = K * (TD / T0);

    std::array<double, 3> m_errors;
    std::array<double, 2> m_controls;
};
