
#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <iostream>
#include <deque>
#include <sys/time.h>
#include <stdexcept>

class PmergeMe {

private:
    PmergeMe();

    PmergeMe(const PmergeMe& other);

    PmergeMe& operator=(const PmergeMe& other);

    ~PmergeMe();

    template<typename Container>
    static void merge(Container& container, int left, int mid, int right) {
        int leftSize = mid - left + 1;
        int rightSize = right - mid;

        typename Container::iterator leftContainerBegin = container.begin();
        std::advance(leftContainerBegin, left);
        typename Container::iterator leftContainerEnd = leftContainerBegin;
        std::advance(leftContainerEnd, leftSize);

        typename Container::iterator rightContainerBegin = container.begin();
        std::advance(rightContainerBegin, mid + 1);
        typename Container::iterator rightContainerEnd = rightContainerBegin;
        std::advance(rightContainerEnd, rightSize);

        Container leftContainer(leftContainerBegin, leftContainerEnd);
        Container rightContainer(rightContainerBegin, rightContainerEnd);

        typename Container::iterator lIt;
        typename Container::iterator rIt;
        for (rIt = rightContainer.begin(); rIt != rightContainer.end(); ++rIt) {
            lIt = std::lower_bound(leftContainer.begin(), leftContainer.end(), *rIt);
            leftContainer.insert(lIt, *rIt);
        }
        typename Container::iterator it = container.begin();
        std::advance(it, left);
        for (lIt = leftContainer.begin(); lIt != leftContainer.end(); ++it, ++lIt) {
            *it = *lIt;
        }
    }

public:
    template<typename Container>
    static long mergeInsertSort(Container& container, int left, int right) {
        struct timeval startTime, endTime;
        gettimeofday(&startTime, NULL);
        if (left < 0 || right >= static_cast<int>(container.size()))
            throw std::invalid_argument("Error");
        else if (left < right) {
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
