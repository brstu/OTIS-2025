#define _USE_MATH_DEFINES
#include <cmath>
#include <gtest/gtest.h>
#include "../src/model.h"

TEST(LinemodelTest, BasicCase) {
    float y = 1.0f;
    float u = 2.0f;
    float a = 1.5f;
    float b = -0.5f;
    int steps = 1;

    auto result = Linemodel(y, u, steps, a, b);
    ASSERT_EQ(result.size(), 1);
    float expected = a * y + b * u;
    EXPECT_FLOAT_EQ(result[0], expected);
}

TEST(LinemodelTest, MultipleSteps) {
    float y = 1.0f;
    float u = 1.0f;
    float a = 2.0f;
    float b = 0.5f;
    int steps = 3;

    auto result = Linemodel(y, u, steps, a, b);
    ASSERT_EQ(result.size(), 3);
    EXPECT_FLOAT_EQ(result[0], 2.0f * 1.0f + 0.5f * 1.0f);
    EXPECT_FLOAT_EQ(result[1], 2.0f * 2.5f + 0.5f * 1.0f);
    EXPECT_FLOAT_EQ(result[2], 2.0f * 5.5f + 0.5f * 1.0f);
}

TEST(LinemodelTest, ZeroCoefficients) {
    auto result = Linemodel(5.0f, 4.0f, 2, 0.0f, 0.0f);
    for (float val : result)
        EXPECT_FLOAT_EQ(val, 0.0f);
}

TEST(UnLinemodelTest, BasicCase) {
    Params p{2.0f, 1.0f, 0.5f, 1.0f, 0.5f, 1};
    float y = 1.0f;
    float y0 = 0.0f;

    auto result = UnLinemodel(p, y, y0);
    ASSERT_EQ(result.size(), 1);

    float expected = p.a * y - p.b * y0 * y0 + p.c * p.u + p.d * std::sin(p.u);
    EXPECT_NEAR(result[0], expected, 1e-5);
}

TEST(UnLinemodelTest, ZeroCoefficients) {
    Params p{0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 2};
    auto result = UnLinemodel(p, 2.0f, 1.0f);
    for (float val : result)
        EXPECT_FLOAT_EQ(val, 0.0f);
}

TEST(UnLinemodelTest, SinusoidalEffect) {
    Params p{0.0f, 0.0f, 0.0f, 2.0f, static_cast<float>(M_PI / 2), 1};
    auto result = UnLinemodel(p, 0.0f, 0.0f);
    ASSERT_EQ(result.size(), 1);

    float expected = 2.0f * static_cast<float>(std::sin(M_PI / 2));
    EXPECT_NEAR(result[0], expected, 1e-5f);
}
