#include <iostream>
#include <stdio.h>
#include "Deltoida.h"
#include "Dialog.h"
#include "Basic.h"

using namespace MS2;

int main() {
    try {
        Deltoida deltoida;
        Dialog(deltoida);
    }
    catch (std::bad_alloc &ba) {
        std::cout << "Error in allocating memory: " << ba.what() << std::endl;
    }
    catch (std::exception &ex) {
        std::cout << "Exception detected: " << ex.what() << std::endl;
    }
    catch (...) {
        std::cout << "Unknown error occured!" << std::endl;
    }
    return 0;
}
