#pragma once

#include <algorithm>

template<typename Container>
class PmergeMe {
	private:
		static const int INSERTION_THRESHOLD = 10;

		static void merge(Container& container, typename Container::iterator left, typename Container::iterator mid, typename Container::iterator right);

		static void insertionSort(Container& container, typename Container::iterator left, typename Container::iterator right);

		static void mergeInsertionSort(Container& container, typename Container::iterator left, typename Container::iterator right);

	public:
		static void sort(Container& container);
};

#include "PmergeMe.cpp"
