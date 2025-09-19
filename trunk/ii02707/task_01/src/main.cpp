#include <iostream>
#include <math.h>

class SimulatedModel
{
public:
    SimulatedModel(float a, float b)
        : m_a(a), m_b(b) 
    {}

    virtual void simulate(float y, float u, float t) = 0;

protected:
    float m_a, m_b;

};
class LinearModel : public SimulatedModel
{
public:
    LinearModel(float a, float b)
        : SimulatedModel(a, b)
    {}

    void simulate(float y, float u, float t) override
    {   
        for(int i = 0; i <= t; i++)
        {
            std::cout << i << ' ' << y << std::endl;
            y = m_a * y + m_b * u;
        } 
    }
};
class NonLinearModel : public SimulatedModel
{
public:
    NonLinearModel(float a, float b, float c, float d)
            : SimulatedModel(a, b), m_c(c), m_d(d) 
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
    float m_c, m_d;

};


class FactoryModel
{
public:
    FactoryModel()
        : m_a(0.5), m_b(0.5)
    {}

    virtual SimulatedModel* getModel() const = 0;

protected:
    const float m_a;
    const float m_b;

};
class FactoryLinearModel : public FactoryModel
{
public:
    FactoryLinearModel()
        : FactoryModel()
    {}

    SimulatedModel* getModel() const override
    { return new LinearModel(m_a, m_b); }

};
class FactoryNonLinearModel : public FactoryModel
{
public:
    FactoryNonLinearModel()
        : FactoryModel(), m_c(0.5), m_d(0.5)
    {}

    SimulatedModel* getModel() const override
    { return new NonLinearModel(m_a, m_b, m_c, m_d); }

private:
    const float m_c;
    const float m_d;

};

int main() 
{
    FactoryModel* factory;
    SimulatedModel* model;
    
    float y, u, t;
    std::cout << "Write necessary data for calculation:" << std::endl;
    std::cout << "y:"; std::cin >> y;
    std::cout << "u:"; std::cin >> u;
    std::cout << "t:"; std::cin >> t;
    std::cout << std::endl;

    std::cout << "Linear simulation:" << std::endl;
    factory = new FactoryLinearModel();
    model = factory->getModel();
    model->simulate(y, u, t);
    std::cout << std::endl;
    delete model;
    delete factory;

    std::cout << "Nonlinear simulation:" << std::endl;
    factory = new FactoryNonLinearModel();
    model = factory->getModel();
    model->simulate(y, u, t);
    std::cout << std::endl;
    delete model;
    delete factory;

    system("pause");
    return 0;
}