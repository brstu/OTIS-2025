#include <gtest/gtest.h>
#include "../src/model.h"
#include <sstream>
#include <iostream>

// Тест на Linemodel
TEST(LinemodelTest, ProducesCorrectOutput) {
    std::ostringstream output;
    std::streambuf* old_buf = std::cout.rdbuf(output.rdbuf());

    Linemodel(1.0f, 0.5f, 2, 1.0f, 0.5f);

    std::cout.rdbuf(old_buf);
    std::string result = output.str();

    EXPECT_NE(result.find("y1 = 1"), std::string::npos);
    EXPECT_NE(result.find("y2 = 1.5"), std::string::npos);
    EXPECT_NE(result.find("end_Linemodel"), std::string::npos);
}

// Тест на UnLinemodel
TEST(UnLinemodelTest, ProducesCorrectOutput) {
    Params p{ 1.0f, 0.1f, 0.2f, 0.3f, 0.5f, 2 };
    std::ostringstream output;
    std::streambuf* old_buf = std::cout.rdbuf(output.rdbuf());

    UnLinemodel(p, 1.0f, 0.5f);

    std::cout.rdbuf(old_buf);
    std::string result = output.str();

    EXPECT_NE(result.find("y1 = 1"), std::string::npos);
    EXPECT_NE(result.find("end_UnLinemodel"), std::string::npos);
}

// Точка входа для Google Test
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}