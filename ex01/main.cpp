#include "RPN.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc == 1)
        std::cout << "Enter a expression\n";
    else if (argc == 2)
        RPN::printAnswer(argv[1]);
    else
        std::cout << "Error only one expression \n";
    return 0;
}