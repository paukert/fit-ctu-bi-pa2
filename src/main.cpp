#include <iostream>
#include <exception>

#include "CApplication.h"

using namespace std;

int main() {

    try {
        CApplication().run();
    }
    catch (const exception & e) {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
    catch (...) {
        cerr << "Something went wrong :(" << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
