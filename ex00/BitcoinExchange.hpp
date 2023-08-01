
#ifndef CPP_HLEESA_BITCOINEXCHANGE_HPP
#define CPP_HLEESA_BITCOINEXCHANGE_HPP

#include <queue>
#include <string>
#include <utility>

typedef std::pair<std::string, double> dateValuePair;

class BitcoinExchange {

private:
    BitcoinExchange();

    BitcoinExchange(const BitcoinExchange& other);

    BitcoinExchange& operator=(const BitcoinExchange& other);

    ~BitcoinExchange();

public:

    static std::queue <dateValuePair> loadFile(const std::string filename);

    static void printBitcoinValue();


};


#endif //CPP_HLEESA_BITCOINEXCHANGE_HPP
