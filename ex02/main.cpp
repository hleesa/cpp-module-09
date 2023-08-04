
#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <list>


int main() {
    int ar[] = {38, 27, 43, 3, 9, 82, 10};
    std::vector<int> arr(ar, ar + 7);
    std::list<int> brr(ar, ar + 7);
    int n = arr.size();

    std::cout << "Original Array: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    PmergeMe::mergeInsertSort(arr, 0, arr.size() - 1);
    PmergeMe::mergeInsertSort(brr, 0, brr.size() - 1);

    std::cout << "Sorted Array: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    std::list<int>::iterator it;
    for (it = brr.begin(); it != brr.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    return 0;
}