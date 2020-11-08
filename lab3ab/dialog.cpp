#include "dialog.h"

#define options_number 7

namespace Prog3A {
    typedef void(*opt_t)(train&);

    static const opt_t options[options_number] = {
        &set_train,
        &get_train_occupancy_information,
        &occupy_seats,
        &get_carriage_occupancy_information,
        &add_carriage,
        &unhook_train,
        &get_passengers_number
    };

    void dialog(train &main_train) {
        int choice = 0;

        std::cout << "------------------------------------------------------------" << std::endl;
        while (true) {
           menu();
           std::cout << "------------------------------------------------------------" << std::endl;
           choice = getNum<int>("Your choice: ");
           std::cout << "------------------------------------------------------------" << std::endl;
           if (!choice) {
              break;
           }
           else if (choice < 0 || choice > options_number) {
              std::cout << "Invalid option detected!" << std::endl;
           }
           else {
              options[choice - 1](main_train);
           }
           std::cout << "------------------------------------------------------------" << std::endl;
        }
    }

    void menu() {
        std::cout <<
            "0. Quit" << std::endl <<
            "1. Set train" << std::endl <<
            "2. Get train occupancy info" << std::endl <<
            "3. Occupy seat" << std::endl <<
            "4. Get carriage occupancy info" << std::endl <<
            "5. Add carriage to train" << std::endl <<
            "6. Unhook train" << std::endl <<
            "7. Get passengers number" << std::endl;
    }

    void set_train(train& main_train) {
        std::cout << "Train parameters: ";
        try {
            std::cin >> main_train;
        }
        catch (const std::invalid_argument& error) {
            std::cerr << "Error: " << error.what() << std::endl;
        }
    }

    void get_train_occupancy_information(train& main_train) {
        std::cout << main_train;
    }

    void occupy_seats(train& main_train) {
        int carriage_index = getNum<int>("Carriage index: ");
        int seats_number = getNum<int>("Number of seats to be occupied: ");

        try {
            main_train(carriage_index, seats_number);
        }
        catch (const std::invalid_argument& error) {
            std::cerr << "Error: " << error.what() << std::endl;
        }
    }

    void get_carriage_occupancy_information(train& main_train) {
        int carriage_index = getNum<int>("Carriage index: ");

        try {
            int result = main_train[carriage_index];
            std::cout << "Number of passengers in the carriage: " << result << std::endl;
        }
        catch (const std::invalid_argument& error) {
            std::cerr << "Error: " << error.what() << std::endl;
        }
    }

    void add_carriage(train& main_train) {
        int carriage_maximum_capacity = getNum<int>("Carriage maximum capacity: ");
        int carriage_occupied_seats_number = getNum<int>("Carriage occupied seats number: ");

        try {
            carriage main_carriage(carriage_maximum_capacity, carriage_occupied_seats_number);
            main_train += main_carriage;
        }
        catch (const std::invalid_argument& error) {
            std::cerr << "Error: " << error.what() << std::endl;
        }
        catch (const std::logic_error& error) {
            std::cerr << "Error: " << error.what() << std::endl;
        }
    }

    void unhook_train(train& main_train) {
        int carriages_number = getNum<int>("Number of carriages to unhook: ");
        int min_train[carriages_number];
        int length_1 = 2;
        int length_2 = 2;
        struct carriage cars_1[main_train.get_length() - carriages_number];
        struct carriage cars_2[carriages_number];


        std::cout << "Carriages indexes: ";
        for (int i = 0; i < carriages_number; i++) {
            min_train[i] = getNum<int>("");
        }
        try {
            train train_2;
            train_2 = main_train( carriages_number, min_train );
            printf("len1 = %d, len2 = %d\n", length_1, length_2);
            train train_3(cars_2, length_2);
            std::cout << "------------------------------------------------------------" << std::endl;
            std::cout << "Formed train_2 occupancy information: " << std::endl;
            std::cout << "------------------------------------------------------------" << std::endl;
            std::cout << train_2;
        }
        catch (const std::invalid_argument& error) {
            std::cerr << "Error: " << error.what() << std::endl;
        }
    }

    void get_passengers_number(train& main_train) {
        std::cout << "Number of passengers in the train: " << main_train.get_passengers_number() << std::endl;
    }
}
