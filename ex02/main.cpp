
#include "PmergeMe.hpp"
#include <iostream>
#include <list>
#include <stdexcept>
#include <sstream>
#include <vector>

template<typename Container>
Container argvToContainer(int argc, char* argv[]) {
    Container ret;
    int value;
    char dum;
    for (int i = 0; i + 1 < argc; ++i) {
        std::stringstream ss(argv[i + 1]);
        if (!(ss >> value) || (value < 1) || (ss >> dum))
            throw std::invalid_argument("Error");
        ret.push_back(value);
    }
    return ret;
}

template<typename Container>
void printContainer(const std::string condition, Container& container) {
    std::cout << condition;
    typename Container::const_iterator it;
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
        if (argc == 1)
            throw std::invalid_argument("Enter positive integer sequence.");
        std::vector<int> vector = argvToContainer<std::vector <int> >(argc, argv);
        std::list<int> list(vector.begin(), vector.end());
        printContainer("Before: ", vector);
        long t1 = PmergeMe::mergeInsertSort(vector, 0, vector.size() - 1);
        long t2 = PmergeMe::mergeInsertSort(list, 0, list.size() - 1);
        printContainer("After:  ", list);
        printTime(vector.size(), "vector ", t1);
        printTime(list.size(), "list   ", t2);
    } catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }
    return 0;
}