#include <iostream>
#include <math.h>

class SimulatedModel
{
public:
    SimulatedModel(double a, double b)
        : m_a(a), m_b(b) 
    {}

    virtual void simulate(double y, double u, double t, double i = 1) = 0;

protected:
    double m_a, m_b;

};

class LinearModel : public SimulatedModel
{
public:
    LinearModel(double a, double b)
        : SimulatedModel(a, b)
    {}

    virtual void simulate(double y, double u, double t, double i = 1) 
    {   
        if (i != t) 
        {
            std::cout << i << ' ' << y << std::endl;
            simulate(m_a * y + m_b * u, u, t, i + 1);
        } 
    }
};

class NonLinearModel : public SimulatedModel
{
public:
    NonLinearModel(double a, double b, double c, double d)
            : SimulatedModel(a, b), m_c(c), m_d(d) 
    {}

    virtual void simulate(double y, double u, double t, double i = 1)
    {
        static double y1 = y;
        if (i != t) 
        {
            std::cout << i << ' ' << y << std::endl;
            double nextY = m_a * y - m_b * y1 * y1 + m_c * u + m_d * sin(u);
            simulate(nextY, u, t, i + 1);
        }
    }

private:
    double m_c, m_d;

};


class FactoryModel
{
public:
    FactoryModel()
        : m_a(0.5), m_b(0.5)
    {}
    virtual SimulatedModel* getModel() const = 0;

protected:
    const double m_a;
    const double m_b;

};
class FactoryLinearModel : public FactoryModel
{
public:
    FactoryLinearModel()
        : FactoryModel()
    {}

    virtual SimulatedModel* getModel() const 
    { return new LinearModel(m_a, m_b); }

};
class FactoryNonLinearModel : public FactoryModel
{
public:
    FactoryNonLinearModel()
        : FactoryModel(), m_c(0.5), m_d(0.5)
    {}

    virtual SimulatedModel* getModel() const 
    { return new NonLinearModel(m_a, m_b, m_c, m_d); }

private:
    const double m_c;
    const double m_d;

};

int main() 
{
    FactoryModel* factory;
    SimulatedModel* model;
    
    double y, u, t;
    std::cout << "Write necessary data:" << std::endl;
    std::cout << "y:"; std::cin >> y;
    std::cout << "u:"; std::cin >> u;
    std::cout << "t:"; std::cin >> t;
    std::cout << std::endl;

    std::cout << "Linear simulation:" << std::endl;
    factory = new FactoryLinearModel();
    model = factory->getModel();
    model->simulate(y, u, t);
    std::cout << std::endl;

    std::cout << "Nonlinear simulation:" << std::endl;
    factory = new FactoryNonLinearModel();
    model = factory->getModel();
    model->simulate(y, u, t);
    std::cout << std::endl;

    system("pause");

    delete model;
    delete factory;
    return 0;
}