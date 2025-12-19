#include <gtest/gtest.h>
#include "../src/pid.h"
#include "../src/model.h"

TEST(PIDControllerTest, ConstructorAndParameters)
{
    PIDController pid(2.0, 1.0, 0.5, 1.0);
    auto coeffs = pid.getCoefficients();

    EXPECT_NEAR(coeffs[0], 2.0 * (1.0 + 0.5 / 1.0), 1e-6);
    EXPECT_NEAR(coeffs[1], -2.0 * (1.0 + 2.0 * 0.5 / 1.0 - 1.0 / 1.0), 1e-6);
    EXPECT_NEAR(coeffs[2], 2.0 * 0.5 / 1.0, 1e-6);
}

TEST(PIDControllerTest, Calculate)
{
    PIDController pid(1.0, 1.0, 0.0, 1.0); // П-регулятор
    pid.reset();

    double u1 = pid.calculate(1.0);
    double u2 = pid.calculate(0.5);
    double u3 = pid.calculate(0.0);

    EXPECT_NEAR(u1, 1.0, 1e-6); // K * e = 1.0 * 1.0
    EXPECT_NEAR(u2, 1.5, 1e-6); // 1.0 + 1.0 * 0.5
    EXPECT_NEAR(u3, 1.5, 1e-6); // 1.5 + 1.0 * 0.0
}

TEST(PIDControllerTest, Limits)
{
    PIDController pid(10.0, 1.0, 0.0, 1.0);
    pid.setLimits(5.0);
    pid.reset();

    double u = pid.calculate(1.0); // Должно быть ограничено до 5.0

    EXPECT_NEAR(u, 5.0, 1e-6);
}

TEST(PlantModelTest, LinearStep)
{
    PlantModel plant(0.5, 0.5, 0.0, 0.0);
    plant.setState(1.0, 0.0);

    double y1 = plant.linearStep(1.0);
    EXPECT_NEAR(y1, 0.5 * 1.0 + 0.5 * 1.0, 1e-6);

    double y2 = plant.linearStep(2.0);
    EXPECT_NEAR(y2, 0.5 * y1 + 0.5 * 2.0, 1e-6);
}

TEST(PlantModelTest, NonlinearStep)
{
    PlantModel plant(0.5, 0.1, 0.3, 0.1);
    plant.setState(1.0, 0.5);

    double y = plant.nonlinearStep(0.5);
    double expected = 0.5 * 1.0 - 0.1 * std::pow(1.0, 2) + 0.3 * 0.5 + 0.1 * std::sin(0.5);

    EXPECT_NEAR(y, expected, 1e-6);
}

TEST(SystemIntegrationTest, PControllerWithLinearPlant)
{
    PlantModel plant(0.8, 0.2, 0.0, 0.0);
    PIDController p_controller(2.0, 1.0, 0.0, 1.0);

    plant.setState(0.0, 0.0);
    p_controller.reset();

    std::vector<double> outputs;
    for (int i = 0; i < 10; i++)
    {
        double y = plant.getOutput();
        double e = 1.0 - y;
        double u = p_controller.calculate(e);
        plant.linearStep(u);
        outputs.push_back(y);
    }

    // Система должна стабилизироваться
    EXPECT_GT(outputs.back(), 0.0);
    EXPECT_LT(outputs.back(), 1.0);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}