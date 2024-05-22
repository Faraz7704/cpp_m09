#include "PmergeMe.hpp"

template<typename Container>
void PmergeMe<Container>::merge(Container& container, typename Container::iterator left, typename Container::iterator mid, typename Container::iterator right) {
    int n1 = std::distance(left, mid) + 1;
    int n2 = std::distance(mid, right) + 1;

    Container L(left, mid + 1);
    Container R(mid + 1, right + 1);

    typename Container::iterator it1 = L.begin(), it2 = R.begin();
    typename Container::iterator it = left;

    while (it1 != L.end() && it2 != R.end()) {
        if (*it1 <= *it2) {
            *it = *it1;
            ++it1;
        } else {
            *it = *it2;
            ++it2;
        }
        ++it;
    }

    while (it1 != L.end()) {
        *it = *it1;
        ++it;
        ++it1;
    }

    while (it2 != R.end()) {
        *it = *it2;
        ++it;
        ++it2;
    }
}

template<typename Container>
void PmergeMe<Container>::insertionSort(Container& container, typename Container::iterator left, typename Container::iterator right) {
    for (typename Container::iterator i = left + 1; i != right + 1; ++i) {
        typename Container::value_type key = *i;
        typename Container::iterator j = i;
        while (j != left && *(j - 1) > key) {
            *j = *(j - 1);
            --j;
        }
        *j = key;
    }
}

template<typename Container>
void PmergeMe<Container>::mergeInsertionSort(Container& container, typename Container::iterator left, typename Container::iterator right) {
    if (std::distance(left, right) <= INSERTION_THRESHOLD) {
        insertionSort(container, left, right);
    } else {
        typename Container::iterator mid = left + std::distance(left, right) / 2;
        mergeInsertionSort(container, left, mid);
        mergeInsertionSort(container, mid + 1, right);
        merge(container, left, mid, right);
    }
}

template<typename Container>
void PmergeMe<Container>::sort(Container& container) {
    if (container.size() <= 1) return;
    mergeInsertionSort(container, container.begin(), container.end() - 1);
}
