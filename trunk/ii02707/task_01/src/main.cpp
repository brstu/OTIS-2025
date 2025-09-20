#include <iostream>
#include <memory>
#include <cmath>

class ISimulatedModel
{
public:
    virtual void simulate(float y, float u, float t) const = 0;
    virtual ~ISimulatedModel() = default;

};
class LinearModel : public ISimulatedModel
{
public:
    LinearModel(float a, float b)
        : m_a(a), m_b(b) 
    {}
    ~LinearModel() override = default;

    void simulate(float y, const float u, float t) const override
    {   
        for(int i = 0; i <= static_cast<int>(t); i++)
        {
            std::cout << i << ' ' << y << std::endl;
            y = m_a * y + m_b * u;
        } 
    }

private:
    const float m_a;
    const float m_b;

};
class NonLinearModel : public ISimulatedModel
{
public:
    NonLinearModel(float a, float b, float c, float d)
            : m_a(a), m_b(b), m_c(c), m_d(d) 
    {}
    ~NonLinearModel() override = default;

    void simulate(float y, const float u, float t) const override
    {
        float prevY = 0;
        for(int i = 0; i <= static_cast<int>(t); i++)
        {
            std::cout << i << ' ' << y << std::endl;
            float nextY = m_a * y - m_b * prevY * prevY + m_c * u + m_d * sin(u);
            prevY = y;
            y = nextY;
        }
    }

private:
    const float m_a;
    const float m_b;
    const float m_c;
    const float m_d;

};


class IFactoryModel
{
public:
    virtual std::unique_ptr<ISimulatedModel> getModel() const = 0;
    virtual ~IFactoryModel() = default;

};
class FactoryLinearModel : public IFactoryModel
{
public:
    ~FactoryLinearModel() override = default;

    std::unique_ptr<ISimulatedModel> getModel() const override
    { return std::make_unique<LinearModel>(m_a, m_b); }

private:
    float m_a { 0.5f };
    float m_b { 0.5f };

};
class FactoryNonLinearModel : public IFactoryModel
{
public:
    ~FactoryNonLinearModel() override = default;

    std::unique_ptr<ISimulatedModel> getModel() const override
    { return std::make_unique<NonLinearModel>(m_a, m_b, m_c, m_d); }

private:
    float m_a { 0.5f };
    float m_b { 0.5f };
    float m_c { 0.5f };
    float m_d { 0.5f };

};

int main() 
{
    std::unique_ptr<IFactoryModel> factory;
    std::unique_ptr<ISimulatedModel> model;
    
    std::cout << "Write necessary data for calculation:" << std::endl;
    float y;
    std::cout << "y:"; std::cin >> y;
    float u;
    std::cout << "u:"; std::cin >> u;
    float t;
    std::cout << "t:"; std::cin >> t;
    std::cout << std::endl;

    std::cout << "Linear simulation:" << std::endl;
    factory = std::make_unique<FactoryLinearModel>();
    model = factory->getModel();
    model->simulate(y, u, t);
    std::cout << std::endl;

    std::cout << "Nonlinear simulation:" << std::endl; 
    factory = std::make_unique<FactoryNonLinearModel>();
    model = factory->getModel();
    model->simulate(y, u, t);
    std::cout << std::endl;

    std::cin.get();
    return 0;
}