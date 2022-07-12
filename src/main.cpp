#include <iostream>
#include "ServerListener.h"

int main() {

    std::cout << "Hello world" << std::endl;
    ServerListener sl;
    sl.run();

    return 0;
}