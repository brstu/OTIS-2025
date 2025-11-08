#pragma once
#include "iregulator.hpp"
#include <array>

/**
 * @brief Class for representing PIDRegulator that controls temperature
 * according to e(t) - deviation of the output variable y(t) from the desired value w(t).
 */
class PIDRegulator : public IRegulator
{
public:
    /**
     * @brief Default constructor.
     */
    explicit PIDRegulator()
    {
        std::fill(m_e.begin(), m_e.end(), 0); // Fill initial results of 'e' with 0
        std::fill(m_u.begin(), m_u.end(), 0); // Fill initial coefficients 'u' with 0
    }
    
    /**
     * @brief Virtual destructor for safe polymorphic usage.
     */
    ~PIDRegulator() override = default;

    /**
     * @brief Calculate next u - input warm according to e & t - and returns it.
     * 
     * Formula:
     * \f[
     * u(k) = u(k - 1) + \Delta u(k)
     * \f] 
     * \f[
     * \Delta u(k) = q_1 e(k) + q_2 e(k - 1) + q_3 e(k - 2)
     * \f]
     * \f[
     * q_0 = K \left( 1 + \frac{T_D}{T_0} \right)
     * \f]
     * \f[
     * q_1 = -K \left( 1 + 2 \frac{T_D}{T_0} - \frac{T_0}{T} \right)
     * \f]
     * \f[
     * q_2 = K \frac{T_D}{T_0}
     * \f]
     *
     * @param e Deviation of the output variable y(t) from the desired value w(t).
     * @param t Time step at which u is computed.
     * 
     * @return u - Input warm.
     */
    double step(double e, double t) override
    {
        auto k = static_cast<int>(t / T0); // k = 0,1,...,t/T0
        m_e[k % m_e.size()] = e;

        m_u[1] = q0*m_e[0] + q1*m_e[1] + q2*m_e[2];
        double u = m_u[0] + m_u[1]; // u(k) = u(k-1) + Δu(k) 
        m_u[0] = m_u[1];
        
        return u;
    }

private:
    static constexpr double T { 0.05 };  // Integration constant.
    static constexpr double T0 { 1 };    // Temperature step.
    static constexpr double TD { 10 };   // Differentiated constant.

    static constexpr double q0 { K*(1 + TD/T0) };
    static constexpr double q1 { -K*(1 + 2*(TD/T0) - (T0/T)) };
    static constexpr double q2 { K*(TD/T0) };

    std::array<double, 3> m_e; // e[0] = e(k), e[1] = e(k-1), e[2] = e(k-2).
    std::array<double, 2> m_u; // u[0] - previous calculated u [ u(k-1) ], u[1] - calculated delta u [ Δu(k) ].

};

