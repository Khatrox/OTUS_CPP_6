//
// Created by xMellox on 10-Sep-20.
//
#include <gtest/gtest.h>
#include <Matrix.h>

TEST(OptionalTasks,MatrixSupportThreeIndexes)
{
    Matrix<int,3,0> m;
    m[1][1][1] = 10;

    std::stringstream ss;
    auto it = m.begin();
    auto v = *it;
    ss << v;

    ASSERT_STREQ(ss.str().c_str(), "1 1 1 10");
}

TEST(OptionalTasks,MatrixSupportSixIndexes)
{
    Matrix<int,6,0> m;
    m[1][1][1][1][1][1] = 10;

    std::stringstream ss;
    auto it = m.begin();
    auto v = *it;
    ss << v;

    ASSERT_STREQ(ss.str().c_str(), "1 1 1 1 1 1 10");
}

TEST(OptionalTasks,MatrixSupportTenIndexes)
{
    Matrix<int,10,0> m;
    m[1][2][3][4][5][6][7][8][9][10] = 99;

    std::stringstream ss;
    auto it = m.begin();
    auto v = *it;
    ss << v;

    ASSERT_STREQ(ss.str().c_str(), "1 2 3 4 5 6 7 8 9 10 99");
}


TEST(OptionalTasks,CanonicalOperatorEqual)
{
    Matrix<int,2,0> m;

    ((m[1][2] = 10) = 11) = 12;

    ASSERT_EQ(m[1][2], 12);
}


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}