
#include "BitcoinExchange.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

std::queue <dateValuePair> BitcoinExchange::loadFile(const std::string filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file '" << filename << "'" << std::endl;
        return std::queue<dateValuePair>();
    }

    std::queue <dateValuePair> ret;
    std::queue<char> delimiter;
    std::string line;
    if (std::getline(file, line)) {
        for (size_t i = 0; i < line.length(); ++i) {
            char c = line[i];
            if (c == ',' || c == '|') {
                delimiter.push(c);
            }
        }
        if (delimiter.size() != 1) {
            std::cerr << "Error: Invalid data form '" << filename << "'" << std::endl;
            return std::queue<dateValuePair>();
        }
        while (getline(file, line)) {
            size_t delimPos = line.find(delimiter.front());
            dateValuePair dataValue = std::make_pair(std::string(), std::string());
            if (delimPos == std::string::npos) {
                dataValue.first = line;
            }
            else {
                dataValue.first = line.substr(0, delimPos);
                dataValue.second = line.substr(delimPos + 1);
            }
            ret.push(dataValue);
        }
    }
    return ret;
}

void BitcoinExchange::printBitcoinValue() {
    std::queue <dateValuePair> database = loadFile("data.csv");
    std::queue <dateValuePair> inputData = loadFile("input.txt");

    /*

    while (!database.empty()) {
        std::cout << database.front().first << "\n" << database.front().second << '\n';
        database.pop();
    }
    while (!inputData.empty()) {
        std::cout << inputData.front().first << "\n" << inputData.front().second << '\n';
        inputData.pop();
    }
     */

    while (!inputData.empty()) {
        std::stringstream ss(inputData.front().second);
        double value;
        if (ss >> value){
            if (value < 0.0) {
                std::cout << "Error: not a positive number.\n";
            }
            else if (value > 1000.0) {
                std::cout << "Error: too large a number.\n";
            }
            else {
                std::cout << value << '\n';
            }
        }
        else {
            std::cout << "Error bad input => \n";   // 내용 구체화? cerr?
        }
        inputData.pop();
    }

    /**
     * 날짜 비교?
     *
     */
}