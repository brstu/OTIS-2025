#include <iostream>
#include <memory>
#include <math.h>

class ISimulatedModel
{
public:
    virtual void simulate(float y, float u, float t) = 0;

};
class LinearModel : public ISimulatedModel
{
public:
    LinearModel(float a, float b)
        : m_a(a), m_b(b) 
    {}

    void simulate(float y, float u, float t) override
    {   
        for(int i = 0; i <= t; i++)
        {
            std::cout << i << ' ' << y << std::endl;
            y = m_a * y + m_b * u;
        } 
    }

private:
    float m_a, m_b;

};
class NonLinearModel : public ISimulatedModel
{
public:
    NonLinearModel(float a, float b, float c, float d)
            : m_a(a), m_b(b), m_c(c), m_d(d) 
    {}

    void simulate(float y, float u, float t) override
    {
        float prevY = 0;
        for(int i = 0; i <= t; i++)
        {
            std::cout << i << ' ' << y << std::endl;
            float nextY = m_a * y - m_b * prevY * prevY + m_c * u + m_d * sin(u);
            prevY = y;
            y = nextY;
        }
    }

private:
    float m_a, m_b, m_c, m_d;

};


class IFactoryModel
{
public:
    virtual std::unique_ptr<ISimulatedModel> getModel() const = 0;

};
class FactoryLinearModel : public IFactoryModel
{
public:
    FactoryLinearModel()
        : m_a(0.5), m_b(0.5)
    {}

    std::unique_ptr<ISimulatedModel> getModel() const override
    { return std::make_unique<LinearModel>(m_a, m_b); }

private:
    float m_a, m_b;

};
class FactoryNonLinearModel : public IFactoryModel
{
public:
    FactoryNonLinearModel()
        : m_a(0.5), m_b(0.5), m_c(0.5), m_d(0.5)
    {}

    std::unique_ptr<ISimulatedModel> getModel() const override
    { return std::make_unique<NonLinearModel>(m_a, m_b, m_c, m_d); }

private:
    float m_a, m_b, m_c, m_d;

};

int main() 
{
    std::unique_ptr<IFactoryModel> factory;
    std::unique_ptr<ISimulatedModel> model;
    
    float y, u, t;
    std::cout << "Write necessary data for calculation:" << std::endl;
    std::cout << "y:"; std::cin >> y;
    std::cout << "u:"; std::cin >> u;
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

    system("pause");
    return 0;
}