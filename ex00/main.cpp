#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2)
        std::cerr << "Error: could not open file." << std::endl;
    else {
        try {
            BitcoinExchange::printBitcoinValue(argv[1]);
        } catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }
    return 0;
}