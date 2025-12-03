#include <gtest/gtest.h>
#include "../src/function.h" 

class PIDTestFixture : public ::testing::Test {
protected:
    PID* pid;

    void SetUp() override {
        pid = new PID(10.0, 0.1, 0.05, 1.0);
    }

    void TearDown() override {
        delete pid;
    }
};

TEST_F(PIDTestFixture, InitialCompute) {
    double u = pid->compute(1.0);
    EXPECT_NEAR(u, 110.5, 0.001);
}

TEST_F(PIDTestFixture, SecondCompute) {
    pid->compute(1.0); 
    double u = pid->compute(0.5);
    EXPECT_NEAR(u, 254.75, 0.001);
}

TEST_F(PIDTestFixture, ZeroError) {
    double u = pid->compute(0.0);
    EXPECT_NEAR(u, 0.0, 0.001);
}

TEST_F(PIDTestFixture, NegativeError) {
    double u = pid->compute(-1.0);
    EXPECT_NEAR(u, -110.5, 0.001);
}

TEST(PIDTest, POnly) {
    PID pid(10.0, 1e10, 0.0, 1.0); 
    double u = pid.compute(1.0);
    EXPECT_NEAR(u, 10.0, 0.001); 
}

TEST(PIDTest, PIOnly) {
    PID pid(10.0, 0.1, 0.0, 1.0);
    double u = pid.compute(1.0);
    EXPECT_NEAR(u, 110.0, 0.001);
}

class ObjectTestFixture : public ::testing::Test {
protected:
    Object* obj;

    void SetUp() override {
        obj = new Object(10.0, 1.0, 1.0);
    }

    void TearDown() override {
        delete obj;
    }
};

TEST_F(ObjectTestFixture, InitialUpdate) {
    double y = obj->update(1.0);
    EXPECT_NEAR(y, 0.095163, 0.000001);
}

TEST_F(ObjectTestFixture, SecondUpdate) {
    obj->update(1.0);  
    double y = obj->update(1.0);
    EXPECT_NEAR(y, 0.181269, 0.000001);
}

TEST_F(ObjectTestFixture, ZeroInput) {
    double y = obj->update(0.0);
    EXPECT_NEAR(y, 0.0, 0.000001);
}


TEST(ObjectTest, DifferentTau) {
    Object obj(5.0, 1.0, 1.0);  
    double y = obj.update(1.0);
    EXPECT_NEAR(y, 0.181269, 0.000001);
}

TEST_F(ObjectTestFixture, SteadyState) {
    double u = 1.0;
    for (int i = 0; i < 100; ++i) {
        obj->update(u);
    }
    double y = obj->update(u);
    EXPECT_NEAR(y, 1.0, 0.001); 
}

TEST(IntegrationTest, PIDWithObject) {
    PID pid(1.0, 10.0, 0.0, 1.0); 
    Object obj(10.0, 1.0, 1.0);
    double w = 1.0;
    double y = 0.0;
    for (int k = 0; k < 10; ++k) {
        double e = w - y;
        double u = pid.compute(e);
        y = obj.update(u);
    }
    EXPECT_GT(y, 0.5); 
    EXPECT_LT(y, 1.5);
}