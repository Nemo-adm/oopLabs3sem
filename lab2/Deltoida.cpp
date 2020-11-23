#include <stdio.h>
#include <stdexcept>
#include "Deltoida.h"

namespace MS2 {
    Deltoida::Deltoida() {
        this->r = 0;
    }

    Deltoida::Deltoida(double r) {
        this->Set_Radius(r);
        if(r < 0){
          throw std::runtime_error("The radius should be a non-negative number!");
      }
    }

    Deltoida &Deltoida::Set_Radius(double r) {
        if (r < 0) {
           throw std::runtime_error("The radius should be a non-negative number!"); ;
        }
        this->r = r;
        return *this;
    }

    double Deltoida::Get_Radius() const {
        return this->r;
    }

    double Deltoida::Get_Intersection_Area_Length() const {
        if (r >= 0) {
           return 4 * r;
        }
        if (r < 0) {
           throw std::runtime_error("The radius should be a non-negative number!");
        }
        return -1;
    }

    double Deltoida::Get_Curve_Length() const {
        if (r >=0){
              return 16*r;
           }
           if (r < 0) {
             throw std::runtime_error("The radius should be a non-negative number!");
           }
           return -1;
    }

    double Deltoida::Get_Bounded_Area_Square() const {
      if (r >= 0) {
            return M_PI * r*r;
      }
      if (r < 0) {
        throw std::runtime_error("The radius should be a non-negative number!");
      }
      return -1;
    }

    double Deltoida::Get_X(double t) const {
      t = 2 * t * M_PI / 180;
      double x = 2*r*cos(t) + r*cos(2*t);
      return x;
    }

    double Deltoida::Get_Y(double t) const {
      t = 2 * t * M_PI / 180;
      double y = 2*r*sin(t) - r*sin(2*t);
      return y;
    }

    std::string Deltoida::Get_Equation() const {
           std::stringstream ss;
           if(this->r == 0) {
           ss << "equation doesn't exist when r = 0";
           }
            else {
           ss << "(x^2 + y+2)^2 + (x^2 + y^2) = 8x^3 -24y^2x^2 + 27";
           }
           return ss.str();
        }

}
