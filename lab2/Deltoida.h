#pragma once

#include <math.h>
#include <sstream>

namespace MS2 {
    class Deltoida {
    private:
        double r;
    public:
        Deltoida();
        Deltoida(double r);
        Deltoida &Set_Radius(double r);
        double Get_Radius() const;
        double Get_Intersection_Area_Length() const;
        double Get_Curve_Length() const;
        double Get_Bounded_Area_Square() const;
        double Get_X(double t) const;
        double Get_Y(double t) const;
        std::string Get_Equation() const;
    };
}
