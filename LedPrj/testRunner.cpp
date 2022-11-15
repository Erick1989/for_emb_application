#include <iostream>
#include <gtest/gtest.h>
#include "LibraryCode.hpp"

TEST(TestCountPositives, BasicTest)
{
    //Arrange
    std::vector<int> inputVector{1, -2, 3, -4, 5, -6, -7};
    //Act
    int count = countPositives(inputVector);
    //Assert
    ASSERT_EQ(3, count);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}