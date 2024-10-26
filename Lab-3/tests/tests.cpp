#include <gtest/gtest.h>
#include "classes/triangle.h"
#include "classes/rectangle.h"
#include "classes/square.h"
#include "classes/array.h"


TEST(SquareTest, AreaTest) {
    SquareVertices v = {.x1=Point(0, 0), .x2=Point(0, 2), .x3=Point(2, 2), .x4=Point(2, 0)};
    Square sq(v);
    EXPECT_DOUBLE_EQ(double(sq), 4.0);
}

TEST(SquareTest, AreaWithZeroesTest) {
    Square sq;
    EXPECT_DOUBLE_EQ(double(sq), 0);
}

TEST(SquareTest, CenterTest) {

    SquareVertices v = {.x1=Point(0, 0), .x2=Point(0, 2), .x3=Point(2, 2), .x4=Point(2, 0)};
    Square sq(v);
    auto center = sq.getCenter();
    EXPECT_DOUBLE_EQ(center.x, 1);
    EXPECT_DOUBLE_EQ(center.y, 1);
}

TEST(RectangleTest, AreaTest) {
    RectangleVertices v = {.x1=Point(0, 0), .x2=Point(0, 3), .x3=Point(4, 3), .x4=Point(4, 0)};
    Rectangle rt(v);
    EXPECT_DOUBLE_EQ(double(rt), 12.0);
}

TEST(RectangleTest, CenterTest) {
    RectangleVertices v = {.x1=Point(0, 0), .x2=Point(0, 3), .x3=Point(4, 3), .x4=Point(4, 0)};
    Rectangle rt(v);
    auto center = rt.getCenter();
    EXPECT_DOUBLE_EQ(center.x, 2);
    EXPECT_DOUBLE_EQ(center.y, 1.5);
}

TEST(TriangleTest, AreaTest) {
    TriangleVertices v = {.x1=Point(1, 1), .x2=Point(-1, 2), .x3=Point(0, 3)};
    Triangle tr(v);
    EXPECT_DOUBLE_EQ(double(tr), 1.5);
}

TEST(TriangleTest, CenterTest) {
    TriangleVertices v = {.x1=Point(1, 1), .x2=Point(-1, 2), .x3=Point(0, 3)};
    Triangle tr(v);
    auto center = tr.getCenter();
    EXPECT_DOUBLE_EQ(center.x, 0);
    EXPECT_DOUBLE_EQ(center.y, 2);
}

TEST(Array, TotalArea) {
    SquareVertices v1 = {.x1=Point(0, 0), .x2=Point(0, 2), .x3=Point(2, 2), .x4=Point(2, 0)};
    Square sq(v1);
    RectangleVertices v2 = {.x1=Point(0, 0), .x2=Point(0, 3), .x3=Point(4, 3), .x4=Point(4, 0)};
    Rectangle rt(v2);
    TriangleVertices v3 = {.x1=Point(1, 1), .x2=Point(-1, 2), .x3=Point(0, 3)};
    Triangle tr(v3);

    Array figures(3);
    figures.add(0, &sq);
    figures.add(1, &rt);
    figures.add(2, &tr);
    EXPECT_DOUBLE_EQ(figures.total_area(), 17.5);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}