#pragma once

#include <iostream>

#include "Deltoida.h"
#include "Basic.h"

namespace MS2 {
    void Menu();
    void Dialog(Deltoida &deltoida);
    void Set_Radius(Deltoida &deltoida);
    void Get_Radius(Deltoida &deltoida);
    void Get_Curve_Length(Deltoida &deltoida);
    void Get_Intersection_Area_Length(Deltoida &deltoida);
    void Get_Bounded_Area_Square(Deltoida &deltoida);
    void Get_X(Deltoida &deltoida);
    void Get_Y(Deltoida &deltoida);
    void Get_Equation(Deltoida &deltoida);
}
