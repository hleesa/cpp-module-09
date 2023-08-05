
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <iostream>
#include <deque>
#include <sys/time.h>

class PmergeMe {

private:

    PmergeMe();

    PmergeMe(const PmergeMe& other);

    PmergeMe& operator=(const PmergeMe& other);

    ~PmergeMe();

    template<typename T>
    static void merge(T& container, int left, int mid, int right) {
        int leftSize = mid - left + 1;
        int rightSize = right - mid;

        typename T::iterator leftContainerBegin = container.begin();
        std::advance(leftContainerBegin, left);
        typename T::iterator leftContainerEnd = leftContainerBegin;
        std::advance(leftContainerEnd, leftSize);

        typename T::iterator rightContainerBegin = container.begin();
        std::advance(rightContainerBegin, mid + 1);
        typename T::iterator rightContainerEnd = rightContainerBegin;
        std::advance(rightContainerEnd, rightSize);

        T leftContainer(leftContainerBegin, leftContainerEnd);
        T rightContainer(rightContainerBegin, rightContainerEnd);

        typename T::iterator lIt;
        typename T::iterator rIt;
        for (rIt = rightContainer.begin(); rIt != rightContainer.end(); ++rIt) {
            lIt = std::lower_bound(leftContainer.begin(), leftContainer.end(), *rIt);
            leftContainer.insert(lIt, *rIt);
        }
        typename T::iterator it = container.begin();
        std::advance(it, left);
        for (lIt = leftContainer.begin(); lIt != leftContainer.end(); ++it, ++lIt) {
            *it = *lIt;
        }
    }

public:
    template<typename T>
    static long mergeInsertSort(T& container, int left, int right) {
        struct timeval startTime, endTime;
        gettimeofday(&startTime, NULL);
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeInsertSort(container, left, mid);
            mergeInsertSort(container, mid + 1, right);
            merge(container, left, mid, right);
        }
        gettimeofday(&endTime, NULL);
        return (endTime.tv_sec - startTime.tv_sec) * 1000000 + (endTime.tv_usec - startTime.tv_usec);
    }
};

#endif //PMERGEME_HPP
