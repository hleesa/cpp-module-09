
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
            std::string date = line.substr(0, delimPos - 1); // 두 파일을 분리해야 할까? 예외 데이터 처리를 어떻게 해야 하나?
            std::stringstream ss(line.substr(delimPos + 1));
            double value;
            ss >> value;
            ret.push(std::make_pair(date, value));
        }
    }
    return ret;
}

void BitcoinExchange::printBitcoinValue() {
    std::queue <dateValuePair> database = loadFile("data.csv");
    std::queue <dateValuePair> inputData = loadFile("input.txt");

    while (!database.empty()) {
        std::cout << database.front().first << " " << database.front().second << '\n';
        database.pop();
    }
    while(!inputData.empty()) {
        std::cout << inputData.front().first << " " << inputData.front().second << '\n';
        inputData.pop();
    }
}