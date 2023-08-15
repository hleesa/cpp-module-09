
#include "BitcoinExchange.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

BitcoinExchange::BitcoinExchange() {
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {
    (void) other;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
    (void) other;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {
}

std::deque<dateValuePair>
BitcoinExchange::readDatabase(const std::string filename, const std::string fileFormat, const char delim) {
    std::deque<dateValuePair> dataset;
    std::ifstream file(filename.c_str());
    if (!file.is_open())
        throw std::invalid_argument("Failed to open file '" + filename + "'");
    std::string line;
    if (std::getline(file, line)) {
        if (line != fileFormat) {
            file.close();
            throw std::invalid_argument("Invalid data type '" + filename + "'");
        }
    }
    while (std::getline(file, line)) {
        size_t delimPos = line.find(delim);
        dateValuePair dateValue = std::make_pair(std::string(), std::string());
        if (delimPos == std::string::npos) {
            file.close();
            throw std::invalid_argument("Invalid data type '" + filename + "'");
        } else {
            dateValue.first = line.substr(0, delimPos);
            dateValue.second = line.substr(delimPos + 1);
        }
        dataset.push_back(dateValue);
    }
    file.close();
    return dataset;
}

bool isValidDate(const std::string date) {
    std::stringstream ss(date);
    int year, month, day;
    char delim1, delim2, dum;
    if (!(ss >> year) || !(ss >> delim1) || !(ss >> month) || !(ss >> delim2) || !(ss >> day) || (ss >> dum))
        return false;
    else if (year < 0 || month < 0 || month > 12 || day < 0 || delim1 != '-' || delim2 != '-')
        return false;
    int maxDays[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        maxDays[2] = 29;
    if (day > maxDays[month])
        return false;
    return true;
}

std::map<std::string, double, std::greater<std::string> >
BitcoinExchange::loadDatabase(const std::string filename, const std::string fileFormat, const char delim) {
    std::map<std::string, double, std::greater<std::string> > database;
    std::deque<dateValuePair> dataset = readDatabase(filename, fileFormat, delim);
    std::deque<dateValuePair>::iterator it;
    for (it = dataset.begin(); it != dataset.end(); ++it) {
        if (!isValidDate(it->first))
            throw std::invalid_argument("Invalid data type in the database: " + it->first);
        std::stringstream ss(it->second);
        double exchangeRate;
        char dum;
        if (!(ss >> exchangeRate) || (ss >> dum))
            throw std::invalid_argument("Invalid data type in the database: " + it->second);
        database.insert(std::pair<std::string, double>(it->first, exchangeRate));
    }
    return database;
}

std::deque<dateValuePair>
BitcoinExchange::readInputFile(const std::string filename, const std::string fileFormat, const char delim) {
    std::deque<dateValuePair> dataset;
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        throw std::invalid_argument("Failed to open file '" + filename + "'");
    }
    std::string line;
    if (std::getline(file, line)) {
        if (line != fileFormat) {
            file.close();
            throw std::invalid_argument("Invalid data type '" + filename + "'");
        }
    }
    while (std::getline(file, line)) {
        size_t delimPos = line.find(delim);
        dateValuePair dateValue = std::make_pair(std::string(), std::string());
        if (delimPos == std::string::npos) {
            dateValue.first = line;
        } else {
            dateValue.first = line.substr(0, delimPos);
            dateValue.second = line.substr(delimPos + 1);
        }
        dataset.push_back(dateValue);
    }
    file.close();
    return dataset;
}

double getBitcoinValue(const std::string exchangeRate) {
    std::stringstream ss(exchangeRate);
    double value;
    char dum;
    if (!(ss >> value))
        throw std::invalid_argument("bad input => " + exchangeRate);
    else if (ss >> dum)
        throw std::invalid_argument("bad input => " + std::string(&dum, 1));
    else if (value < 0.0)
        throw std::invalid_argument("not a positive number.");
    else if (value > 1000.0)
        throw std::invalid_argument("too large a number.");
    return value;
}

void BitcoinExchange::printBitcoinValue(const std::string inputFile) {
    std::map<std::string, double, std::greater<std::string> > database = loadDatabase("data.csv", "date,exchange_rate",',');
    std::deque<dateValuePair> inputDataSet = readInputFile(inputFile, "date | value", '|');
    std::deque<dateValuePair>::iterator inputIt;
    for (inputIt = inputDataSet.begin(); inputIt != inputDataSet.end(); ++inputIt) {
        try {
            if (!isValidDate(inputIt->first))
                throw std::invalid_argument("bad input => " + inputIt->first);
            double value = getBitcoinValue(inputIt->second);
            std::map<std::string, double>::iterator foundDatabaseIt = database.lower_bound(inputIt->first);
            if (foundDatabaseIt == database.end())
                throw std::invalid_argument("bad input => " + inputIt->first);
            else
                std::cout << inputIt->first << "=> " << value << " = " << value * foundDatabaseIt->second << '\n';
        } catch (std::exception &e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }
    return;
}
