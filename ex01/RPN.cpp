
#include "RPN.hpp"
#include <stack>
#include <iostream>
#include <stdexcept>
#include <stdlib.h>

RPN::RPN() {
}

RPN::RPN(const RPN& other) {
    (void) other;
}

RPN& RPN::operator=(const RPN& other) {
    (void) other;
    return *this;
}

RPN::~RPN() {
}

bool isOperator(const char c) {
    std::string ops = "+-*/";
    return ops.find(c) != std::string::npos;
}

void applyOperator(std::stack<long>& acc, const char op) {
    if (acc.size() < 2)
        throw std::invalid_argument("lack of number");
    long rhs = acc.top(); acc.pop();
    long lhs = acc.top(); acc.pop();
    long result;
    switch (op) {
        case '+':
            result = lhs + rhs;
            break;
        case '-':
            result = lhs - rhs;
            break;
        case '*':
            result = lhs * rhs;
            break;
        case '/':
            result = lhs / rhs;
            break;
        default:
            throw std::invalid_argument("invalid operator");
            break;
    }
    acc.push(result);
}

long RPN::calculate(std::string expression) {
    std::stack<long> acc;
    for (size_t i = 0; i < expression.size(); ++i) {
        char c = expression[i];
        if (isdigit(c))
            acc.push(atol(&c));
        else if (isOperator(c))
            applyOperator(acc, c);
        else if (!isspace(c))
            throw std::invalid_argument(std::string(&c, 1));
    }
    if (acc.size() != 1)
        throw std::invalid_argument("lack of operators");
    return acc.top();
}

void RPN::printAnswer(const char* arg) {
    try {
        std::cout << calculate(std::string(arg)) << '\n';
    } catch (std::exception& e) {
        std::cout << "Error\n";
    }
    return;
}