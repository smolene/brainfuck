#include <iostream>
#include "brainfuck.h"

int main() {
    using namespace brainfuck;

    std::cout << "Enter program:" << std::endl;

    std::string code;
    std::cin >> code;
    executor bf(code, 256);

    std::cout << "- Start" << std::endl;
    bf.run();
    std::cout << "- End" << std::endl;

    return 0;
}
