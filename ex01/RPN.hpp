
#ifndef RPN_HPP
#define RPN_HPP

#include <string>

class RPN {

private:
    RPN();

    RPN(const RPN& other);

    RPN& operator=(const RPN& other);

    ~RPN();

    static long calculate(std::string expression);

public:
    static void printAnswer(const char* arg);

};


#endif //RPN_HPP
