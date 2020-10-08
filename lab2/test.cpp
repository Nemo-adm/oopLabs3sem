#include <math.h>

#include "gtest/gtest.h"
#include "Deltoida.h"

using namespace MS2;

TEST(Deltoida_Constructor, Default_Constructor) {
    Deltoida deltoida;
    ASSERT_NO_THROW(deltoida);
    ASSERT_EQ(0, deltoida.Get_Radius());
}

TEST(Deltoida_Constructor, Initial_Constructor) {
    Deltoida deltoida_1(4);
    ASSERT_NO_THROW(deltoida_1);
    ASSERT_EQ(4, deltoida_1.Get_Radius());
    ASSERT_ANY_THROW(Deltoida deltoida_2(-7));
}

TEST(Deltoida_Methods, Setters) {
    Deltoida deltoida;
    ASSERT_NO_THROW(deltoida.Set_Radius(8));
    ASSERT_EQ(8, deltoida.Get_Radius());
    ASSERT_ANY_THROW(deltoida.Set_Radius(-4));
}

TEST(Deltoida_Methods, Get_Intersection_Area_Length) {
    Deltoida deltoida(6);
    ASSERT_EQ(24, deltoida.Get_Intersection_Area_Length());
}

TEST(Deltoida_Methods, Get_Curve_Length) {
    Deltoida deltoida(5);
    ASSERT_EQ(80, deltoida.Get_Curve_Length());
}

TEST(Deltoida_Methods, Get_Bounded_Area_Square) {
    Deltoida deltoida(5);
    ASSERT_EQ(M_PI*25, deltoida.Get_Bounded_Area_Square());
}

TEST(Deltoida_Methods, Get_X) {
    Deltoida deltoida(4);
    ASSERT_EQ(2*4*cos(2 * 30 * M_PI / 180) + 4*cos(2*2 * 30 * M_PI / 180), deltoida.Get_X(30));
}

TEST(Deltoida_Methods, Get_y) {
    Deltoida deltoida(4);
    ASSERT_EQ(2*4*sin(2 * 30 * M_PI / 180) - 4*sin(2*2 * 30 * M_PI / 180), deltoida.Get_Y(30));
}

TEST(Deltoida_Methods, Equation_NULL) {
    Deltoida deltoida;
    ASSERT_EQ("equation doesn't exist when r = 0", deltoida.Get_Equation());
}

TEST(Deltoida_Methods, Equation_Not_NULL) {
    Deltoida deltoida(2);
    ASSERT_EQ("(x^2 + y+2)^2 + (x^2 + y^2) = 8x^3 -24y^2x^2 + 27", deltoida.Get_Equation());
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
