#include <iostream>
#include <memory>
#include <cmath>

class ISimulatedModel
{
public:
    virtual void simulate(double y, const double u, int t) const = 0;
    virtual ~ISimulatedModel() = default;

};
class LinearModel : public ISimulatedModel
{
public:
    LinearModel(const double a, const double b)
        : m_a(a), m_b(b) 
    {}
    ~LinearModel() override = default;

    void simulate(double y, const double u, int t) const override
    {   
        for(int i = 0; i <= t; i++)
        {
            std::cout << i << ' ' << y << std::endl;
            y = m_a * y + m_b * u;
        } 
    }

private:
    const double m_a;
    const double m_b;

};
class NonLinearModel : public ISimulatedModel
{
public:
    NonLinearModel(const double a, const double b, const double c, const double d)
            : m_a(a), m_b(b), m_c(c), m_d(d) 
    {}
    ~NonLinearModel() override = default;

    void simulate(double y, const double u, int t) const override
    {
        double prevY = y;
        for(int i = 0; i <= t; i++)
        {
            std::cout << i << ' ' << y << std::endl;
            double nextY = m_a * y - m_b * prevY * prevY + m_c * u + m_d * sin(u);
            prevY = y;
            y = nextY;
        }
    }

private:
    const double m_a;
    const double m_b;
    const double m_c;
    const double m_d;

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
    const double m_a { 0.5 };
    const double m_b { 0.5 };

};
class FactoryNonLinearModel : public IFactoryModel
{
public:
    ~FactoryNonLinearModel() override = default;

    std::unique_ptr<ISimulatedModel> getModel() const override
    { return std::make_unique<NonLinearModel>(m_a, m_b, m_c, m_d); }

private:
    const double m_a { 0.5 };
    const double m_b { 0.5 };
    const double m_c { 0.5 };
    const double m_d { 0.5 };

};

template<typename T>
void validateInput(const std::string &txt, T& value);

int main() 
{
    std::unique_ptr<IFactoryModel> factory;
    std::unique_ptr<ISimulatedModel> model;
    
    std::cout << "Write necessary data for calculation:" << std::endl;
    double y;
	validateInput("y:", y);
    double u;
	validateInput("u:", u);
    int t;
	validateInput("t:", t);
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

    return 0;
}

template<typename T>
void validateInput(const std::string &txt, T& value)
{
	do
	{
		std::cout << txt; std::cin >> value;
	} while(value < 0);
}