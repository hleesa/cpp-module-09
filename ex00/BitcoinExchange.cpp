
#include "BitcoinExchange.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

BitcoinExchange::BitcoinExchange() {
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
    (void) other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    (void) other;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {
}

std::queue <dateValuePair> BitcoinExchange::loadFile(const std::string filename, const char delim) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw std::invalid_argument("Failed to open file '" + filename + "'");
    }
    std::queue <dateValuePair> ret;
    std::string line;
    if (std::getline(file, line)) {
        int numOfDelim = 0;
        for (size_t i = 0; i < line.length(); ++i) {
            if (line[i] == delim)
                ++numOfDelim;
        }
        if (numOfDelim != 1) {
            file.close();
            throw std::invalid_argument("Invalid data form '" + filename + "'");
        }
        while (std::getline(file, line)) {
            size_t delimPos = line.find(delim);
            dateValuePair dateValue = std::make_pair(std::string(), std::string());
            if (delimPos == std::string::npos)
                dateValue.first = line;
            else {
                dateValue.first = line.substr(0, delimPos);
                dateValue.second = line.substr(delimPos + 1);
            }
            ret.push(dateValue);
        }
    }
    file.close();
    return ret;
}

bool isValidDate(const std::string date) {
    std::stringstream ss(date);
    int year, month, day;
    char delim1, delim2;
    if (!(ss >> year) || !(ss >> delim1) || !(ss >> month) || !(ss >> delim2) || !(ss >> day))
        return false;
    else if (year < 0 || month < 0 || month > 12 || delim2 < 0 || delim1 != '-' || delim2 != '-')
        return false;
    int maxDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        maxDays[2] = 29;
    if (day > maxDays[month])
        return false;
    return true;
}

void fillDatabase(std::map<std::string, double>& database) {
    std::queue <dateValuePair> dataset;
    try {
        dataset = BitcoinExchange::loadFile("data.csv", ',');
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
    while (!dataset.empty()) {
        try {
            dateValuePair curData = dataset.front();
            dataset.pop();
            std::stringstream ss(curData.second);
            double exchangeRate;
            if (!(ss >> exchangeRate))
                throw std::invalid_argument("invalid number => " + curData.second);
            database.insert(std::pair<std::string, double>(curData.first, exchangeRate));
        } catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }
    return;
}

void BitcoinExchange::printBitcoinValue(const std::string inputFile) {
    std::map<std::string, double> database;
    fillDatabase(database);
    std::queue <dateValuePair> inputData;
    try {
        inputData = loadFile(inputFile, '|');
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
    }
    while (!inputData.empty()) {
        try {
            dateValuePair curData = inputData.front();
            inputData.pop();
            if (isValidDate(curData.first)) {
                std::stringstream ss(curData.second);
                double value;
                if (ss >> value) {
                    if (value < 0.0)
                        throw std::invalid_argument("not a positive number.");
                    else if (value > 1000.0)
                        throw std::invalid_argument("too large a number.");
                    else {
                        std::map<std::string, double>::iterator it = database.lower_bound(curData.first);
                        if (it->first != curData.first) {
                            if (it == database.begin())
                                throw std::invalid_argument("bad input => " + curData.first);
                            else
                                --it;
                        }
                        std::cout << curData.first << "=> " << value << " = " << value * it->second << '\n';
                    }
                }
                else
                    throw std::invalid_argument("bad input => " + curData.first + curData.second);
            }
            else
                throw std::invalid_argument("bad input => " + curData.first);
        } catch (std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }
    return;
}
