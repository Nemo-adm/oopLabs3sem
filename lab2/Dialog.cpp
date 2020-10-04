#include "Dialog.h"
#include <stdio.h>
#define options_number 8

namespace MS2 {
    typedef void(*opt_t)(Deltoida&);

    static const opt_t options[options_number] = {
        &Set_Radius,
        &Get_Radius,
        &Get_Intersection_Area_Length,
        &Get_Curve_Length,
        &Get_Bounded_Area_Square,
        &Get_X,
        &Get_Y,
        &Get_Equation
    };

    void Dialog(Deltoida &deltoida) {
        std::cout << "------------------------------------------------------------" << std::endl;
        while (true) {
           Menu();
           std::cout << "------------------------------------------------------------" << std::endl;
           int choice = 0;
           choice = getNum<int>("Option->");
           std::cout << "------------------------------------------------------------" << std::endl;
           if (!choice) {
              break;
           }
           else if (choice < 0 || choice > options_number) {
              std::cout << "Invalid option detected!" << std::endl;
           }
           else {
              options[choice - 1](deltoida);
           }
           std::cout << "------------------------------------------------------------" << std::endl;
        }
    }

    void Menu() {
        std::cout <<
            "0. Quit" << std::endl <<
            "1. Set radius" << std::endl <<
            "2. Get radius" << std::endl <<
            "3. Get intersection area length" << std::endl <<
            "4. Get curve length" << std::endl <<
            "5. Get bounded area square" << std::endl <<
            "6. Get X(t) coordinate" << std::endl <<
            "7. Get Y(t) coordinate" << std::endl <<
            "8. Get equation" << std::endl;
    }

    void Set_Radius(Deltoida &deltoida) {
        double r = 0;

        r = MS2::getNum<double>("Enter the radius: ");
        try {
            deltoida.Set_Radius(r);
        }
        catch (const char *error) {
            std::cerr << error << std::endl;
        }
    }

    void Get_Radius(Deltoida &deltoida){
     std::cout << "Radius = " << deltoida.Get_Radius() << std::endl;
    }

    void Get_Intersection_Area_Length(Deltoida &deltoida) {
        std::cout << "Intersection area length = " << deltoida.Get_Intersection_Area_Length() << std::endl;
    }

    void Get_Curve_Length(Deltoida &deltoida) {
      std::cout << "Curve length: " << deltoida.Get_Curve_Length() << std::endl;
    }

    void Get_Bounded_Area_Square(Deltoida &deltoida) {
      std::cout << "Bounded area square: " << deltoida.Get_Bounded_Area_Square() << std::endl;
    }

    void Get_X(Deltoida &deltoida) {
        double t = 0;

        t = MS2::getNum<double>("Angle value in degrees: ");
        if (deltoida.Get_X(t) >= 0) {
           std::cout << "X coordinate = " << deltoida.Get_X(t) << std::endl;
        }
        else {
           std::cout << "Invalid polar angle coordinate!" << std::endl;
        }
    }

    void Get_Y(Deltoida &deltoida) {
        double t = 0;

        t = getNum<double>("Angle value in degrees: ");
        if (deltoida.Get_Y(t) >= 0) {
           std::cout << "Y coordinate = " << deltoida.Get_Y(t) << std::endl;
        }
        else {
           std::cout << "Invalid polar angle coordinate!" << std::endl;
        }
     }

    void Get_Equation(Deltoida &deltoida) {
        std::cout << deltoida.Get_Equation() << std::endl;
    }
}
