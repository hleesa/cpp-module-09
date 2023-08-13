
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <deque>
#include <string>
#include <utility>


typedef std::pair <std::string, std::string> dateValuePair;

class BitcoinExchange {

private:
    BitcoinExchange();

    BitcoinExchange(const BitcoinExchange& other);

    BitcoinExchange& operator=(const BitcoinExchange& other);

    ~BitcoinExchange();

public:
    static std::deque <dateValuePair> loadDatabase(const std::string filename, const std::string fileFormat, const char delim);

    static std::deque <dateValuePair> loadInputFile(const std::string filename, const std::string fileFormat, const char delim);

    static void printBitcoinValue(const std::string inputFile);

};


#endif //BITCOINEXCHANGE_HPP
