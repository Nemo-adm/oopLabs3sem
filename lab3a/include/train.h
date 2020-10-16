#pragma once
#include <iosfwd>

namespace Prog3A {
    struct carriage {
        int maximum_capacity;
        int occupied_seats_number;
        carriage();
        carriage(int maximum_capacity, int occupied_seats_number);
        carriage& set_carriage(int maximum_capacity, int occupied_seats_number);
    };
    class train {
    private:
        struct carriage cars[100];
        int length;
    public:
        train();
        train(struct carriage *cars, int length);
        train& set_length(int length);
        train& set_carriages(struct carriage *cars);
        int get_length();
        struct carriage *get_carriages();
        friend std::istream& operator >> (std::istream& in, train& main_train);          // ввод экземпляров класса поезд
        friend std::ostream& operator << (std::ostream& out, const train& main_train);   // вывод инфы о занятости вагонов
        train& operator () (int carriage_index, int seats_number);                       // занять место
        int& operator [] (int carriage_index);                                           // определить кол-во занятых мест в вагоне
        train& operator += (carriage& main_carriage);                                    // добавить вагон к поезду
        train& operator ( ) (int carriages_number, int *min_train);                      // для расцепки
        int get_passengers_number();
    };
}
