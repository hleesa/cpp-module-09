
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <queue>
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
    static std::queue <dateValuePair> loadFile(const std::string filename, const char delim);

    static void printBitcoinValue(const std::string inputFile);

};


#endif //BITCOINEXCHANGE_HPP
