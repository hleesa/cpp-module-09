
#include "RPN.hpp"
#include <stack>
#include <iostream>
#include <stdexcept>

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

bool isOp(const char c) {
    std::string ops = "+-*/";
    return ops.find(c) != std::string::npos;
}

void applyOp(std::stack<long>& acc, const char op) {
    if (acc.size() < 2)
        throw std::invalid_argument("lack of number");
    long rhs = acc.top();
    acc.pop();
    long lhs = acc.top();
    acc.pop();
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
    }
    acc.push(result);
}

long RPN::calculate(std::string expression) {
    std::stack<long> acc;
    for (size_t i = 0; i < expression.size(); ++i) {
        char c = expression[i];
        if (isdigit(c))
            acc.push(static_cast<long>(c - '0'));
        else if (isOp(c))
            applyOp(acc, c);
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