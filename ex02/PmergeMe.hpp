
#ifndef CPP_HLEESA_PMERGEME_HPP
#define CPP_HLEESA_PMERGEME_HPP


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

        T leftContainer(leftSize);
        T rightContainer(rightSize);
        for (int i = 0; i < leftSize; ++i) {
            leftContainer[i] = container[left + i];
        }
        for (int i = 0; i < rightSize; ++i) {
            rightContainer[i] = container[mid + 1 + i];
        }

        int i = 0, j = 0, k = left;
        while (i < leftSize && j < rightSize) {
            if (leftContainer[i] <= rightContainer[j]) {
                container[k] = leftContainer[i];
                ++i;
            }
            else {
                container[k] = rightContainer[j];
                ++j;
            }
            ++k;
        }
        while (i < leftSize) {
            container[k++] = leftContainer[i++];
        }
        while (j < rightSize) {
            container[k++] = rightContainer[j++];
        }
    }

public:

    template<typename T>
    static void mergeInsertSort(T& container, int left, int right) {
        if (left < right) {
            int mid = (left + right) / 2;
            mergeInsertSort(container, left, mid);
            mergeInsertSort(container, mid + 1, right);
            merge(container, left, mid, right);
        }
    }


};


#endif //CPP_HLEESA_PMERGEME_HPP
