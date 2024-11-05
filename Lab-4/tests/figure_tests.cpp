#include <gtest/gtest.h>
#include "classes/figure.h"
#include "classes/point.h"

TEST(FigureTest, DefaultConstructor) {
    Figure<double> fig;
    EXPECT_EQ(fig.getCenter(), Point<double>(0, 0));
}

TEST(FigureTest, InitializerListConstructor) {
    Figure<double> fig = {Point<double>(0, 0), Point<double>(1, 1)};
    EXPECT_EQ(fig.getCenter(), Point<double>(0.5, 0.5));
}

TEST(FigureTest, CopyConstructor) {
    Figure<double> fig1 = {Point<double>(0, 0), Point<double>(1, 1)};
    Figure<double> fig2(fig1);
    EXPECT_EQ(fig2.getCenter(), fig1.getCenter());
}

TEST(FigureTest, MoveConstructor) {
    Figure<double> fig1 = {Point<double>(0, 0), Point<double>(1, 1)};
    Figure<double> fig2(std::move(fig1));
    EXPECT_EQ(fig2.getCenter(), Point<double>(0.5, 0.5));
}

TEST(FigureTest, AssignmentOperator) {
    Figure<double> fig1 = {Point<double>(0, 0), Point<double>(1, 1)};
    Figure<double> fig2;
    fig2 = fig1;
    EXPECT_EQ(fig2.getCenter(), fig1.getCenter());
}

TEST(FigureTest, MoveAssignmentOperator) {
    Figure<double> fig1 = {Point<double>(0, 0), Point<double>(1, 1)};
    Figure<double> fig2;
    fig2 = std::move(fig1);
    EXPECT_EQ(fig2.getCenter(), Point<double>(0.5, 0.5));
}

TEST(FigureTest, EqualityOperator) {
    Figure<double> fig1 = {Point<double>(0, 0), Point<double>(1, 1)};
    Figure<double> fig2 = {Point<double>(0, 0), Point<double>(1, 1)};
    Figure<double> fig3 = {Point<double>(2, 2)};

    EXPECT_TRUE(fig1 == fig2);
    EXPECT_FALSE(fig1 == fig3);
}

TEST(FigureTest, AreaCalculation) {
    Figure<double> triangle = {Point<double>(0, 0), Point<double>(1, 0), Point<double>(0, 1)};
    double area = triangle;
    EXPECT_DOUBLE_EQ(area, 0.5);
}

TEST(FigureTest, GetCenter) {
    Figure<double> fig = {Point<double>(0, 0), Point<double>(2, 0), Point<double>(0, 2)};
    Point<double> center = fig.getCenter();
    EXPECT_DOUBLE_EQ(center.x, 2.0 / 3.0);
    EXPECT_DOUBLE_EQ(center.y, 2.0 / 3.0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}