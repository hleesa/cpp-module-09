
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <deque>
#include <string>
#include <utility>
#include <map>

typedef std::pair<std::string, std::string> dateValuePair;

class BitcoinExchange {

private:
    BitcoinExchange();

    BitcoinExchange(const BitcoinExchange &other);

    BitcoinExchange &operator=(const BitcoinExchange &other);

    ~BitcoinExchange();

    static std::deque<dateValuePair>
    readDatabase(const std::string filename, const std::string fileFormat, const char delim);

    static std::map<std::string, double, std::greater<std::string> >
    loadDatabase(const std::string filename, const std::string fileFormat, const char delim);

    static std::deque<dateValuePair>
    readInputFile(const std::string filename, const std::string fileFormat, const char delim);

public:
    static void printBitcoinValue(const std::string inputFile);

};


#endif //BITCOINEXCHANGE_HPP
