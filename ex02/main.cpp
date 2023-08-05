
#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <stdexcept>
#include <sstream>

std::deque<int> toDeque(int argc, char* argv[]) {
    if (argc == 1)
        throw std::invalid_argument("Error");
    std::deque<int> ret(argc - 1);
    int value;
    for (int i = 1; i < argc; ++i) {
        std::stringstream ss(argv[i]);
        if (!(ss >> value) || value < 1)
            throw std::invalid_argument("Error");
        ret[i - 1] = value;
    }
    return ret;
}

template<typename T>
void printContainer(const std::string condition, T& container) {
    std::cout << condition;
    typename T::const_iterator it;
    for (it = container.begin(); it != container.end(); ++it)
        std::cout << *it << " ";
    std::cout << '\n';
}

void printTime(const size_t size, const std::string containerName, const long time) {
    std::cout << "Time to process a range of " << size << " elements with std::" + containerName + ": " << time
              << "us\n";
}

int main(int argc, char* argv[]) {
    try {
        std::deque<int> deque = toDeque(argc, argv);
        std::list<int> list(deque.begin(), deque.end());
        printContainer("Before: ", deque);
        long t1 = PmergeMe::mergeInsertSort(deque, 0, deque.size() - 1);
        long t2 = PmergeMe::mergeInsertSort(list, 0, list.size() - 1);
        printContainer("After:  ", list);
        printTime(deque.size(), "deque   ", t1);
        printTime(list.size(), "list    ", t2);
    } catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }
    return 0;
}