#include <gtest/gtest.h>

int multiply(int a, int b){
    return a * b;
}

TEST(MultiplyTest, PlusNumbers){
    EXPECT_EQ(4, multiply(2, 2));
}


TEST(MultiplyTest, MinusNumbers){
    EXPECT_EQ(-4, multiply(-2, 2));
    EXPECT_EQ(4, multiply(-2, -2));
    EXPECT_EQ(-4, multiply(2, -2));
    EXPECT_EQ(4, multiply(2, 2));
}

int main(int argc, char* argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}