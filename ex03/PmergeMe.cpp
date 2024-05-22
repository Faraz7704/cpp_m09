#include	<sstream>
#include	<algorithm>
#include	<limits>
#include	<math.h>
#include	<iterator>
#include	"PmergeMe.hpp"

PmergeMe::PmergeMe(void) {};

PmergeMe::~PmergeMe(void) {};

PmergeMe::PmergeMe(const PmergeMe &pMergeMeREF)
{
	operator=(pMergeMeREF);
};

PmergeMe	&PmergeMe::operator=(const PmergeMe &pMergeMeREF)
{
	if (this != &pMergeMeREF)
	{
		_list = pMergeMeREF.getList();
		_vector = pMergeMeREF.getVector();
		_values = pMergeMeREF.getValues();
	}
	return (*this);
};

PmergeMe::PmergeMe(unsigned int nNumbers, const char **numbers) throw (std::exception)
{
	std::vector< std::pair< float, float > >::iterator	it;
	std::vector< std::pair< float, float > >::iterator	ite;
	std::pair< float, float >							oddPair;
	float												tmpFl;

	_values = makePairs(loadValues(nNumbers, numbers));
	ite = _values.end();
	if (isnan(_values.back().second))
		--ite;
	for (it = _values.begin(); it != ite; ++it)
	{
		if (it->first > it->second)
		{
			tmpFl = it->first;
			it->first = it->second;
			it->second = tmpFl;
		}
	}
};

const std::list< float >	&PmergeMe::getList(void) const
{
	return (_list);
};

const std::vector< float >	&PmergeMe::getVector(void) const
{
	return (_vector);
};

const std::vector< std::pair< float, float > >	&PmergeMe::getValues(void) const
{
	return (_values);
};

std::vector< float >	PmergeMe::loadValues(unsigned int nNumbers, const char **numbers)
{
	std::stringstream	ssNumbers;
	std::stringstream	ssNumber;
	std::string			numberStr;
	std::vector<float>	numbersArr;
	float				numberfloat;

	if (nNumbers > 0)
	{
		for (unsigned int i = 0; i < nNumbers && numbers[i] != NULL; ++i)
		{
			ssNumbers.clear();
			ssNumbers.str(numbers[i]);
			do {
				ssNumbers >> numberStr;
				ssNumber.clear();
				ssNumber.str(numberStr);
				ssNumber >> numberfloat;
				if (ssNumber.fail())
					throw (ErrorInputException(std::string("Error number at: ") + numberStr));
				numbersArr.push_back(numberfloat);
			} while (!ssNumbers.eof());
		};
	}
	return (numbersArr);
};

std::vector< std::pair< float, float > >	PmergeMe::makePairs(const std::vector<float> &values)
{
	float										first;
	float										second;
	std::vector< std::pair< float, float > >	valuePairs;

	std::vector< float >::const_iterator itc = values.begin();
	while (itc != values.end())
	{
		first = *itc;
		if (++itc != values.end())
		{
			second = *itc;
			valuePairs.push_back(std::pair< float, float >(first, second));
			++itc;
		}
		else
			valuePairs.push_back(std::pair< float, float >(first, std::numeric_limits< float >::quiet_NaN()));
	};
	return (valuePairs);
}

static int	sortBySecond(const std::pair< float, float > &a, const std::pair< float, float > &b)
{
	return (a.second < b.second);
};

static void	jsthalIncrement(long int &jsthalLast, long int &jsthalThis)
{
	long int	jsthalNext;

	jsthalNext = jsthalThis + 2 * jsthalLast;
	jsthalLast = jsthalThis;
	jsthalThis = jsthalNext;
}

static std::list< float >	listBinaryInsert(std::list< float > aChain, const std::list< float > bChain)
{
	long int								jsthalThis;
	long int								jsthalLast;
	std::list< float >::const_iterator		jsthalIt;
	std::list< float >::const_iterator		jsthalIte;

	jsthalThis = 1;
	jsthalLast = 0;
	jsthalIt = bChain.begin();
	jsthalIte = jsthalIt;
	std::advance(jsthalIte, -1);
	jsthalIncrement(jsthalLast, jsthalThis);
	for (std::size_t i = 0; i < bChain.size(); ++i)
	{
		aChain.insert(std::lower_bound(aChain.begin(), aChain.end(), *jsthalIt), *jsthalIt);
		--jsthalIt;
		if (jsthalIt == jsthalIte)
		{
			std::advance(jsthalIt, jsthalThis - jsthalLast);
			std::advance(jsthalIte, jsthalThis - jsthalLast);
			jsthalIncrement(jsthalLast, jsthalThis);
			std::advance(jsthalIt, ((jsthalThis - jsthalLast) > (std::distance(jsthalIt, bChain.end()) - 1)) ? (jsthalThis - jsthalLast) : (std::distance(jsthalIt, bChain.end()) - 1));
		}
	};
	return (aChain);
};

std::list< std::pair< float, float > >	listMerge(std::list< std::pair< float, float > > aPairs, std::list< std::pair< float, float > > bPairs)
{
	std::list< std::pair< float, float > >			cPairs;

	std::merge(aPairs.begin(), aPairs.end(), bPairs.begin(), bPairs.end(), std::back_inserter(cPairs), sortBySecond);
	return (cPairs);
}

static std::list< std::pair< float, float > >	listMergeSort(std::list< std::pair< float, float > > listPairs)
{
	std::list< std::pair< float, float > >				aPairs;
	std::list< std::pair< float, float > >				bPairs;
	std::list< std::pair< float, float > >::iterator	midPoint;

	if (listPairs.size() <= 1)
		return (listPairs);
	midPoint = listPairs.begin();
	std::advance(midPoint, listPairs.size() / 2);
	aPairs.insert(aPairs.begin(), listPairs.begin(), midPoint);
	aPairs = listMergeSort(aPairs);
	bPairs.insert(bPairs.begin(), midPoint, listPairs.end());
	bPairs = listMergeSort(bPairs);
	return (listMerge(aPairs, bPairs));
};

std::list< float >	PmergeMe::sortUsingList(void)
{
	std::list< std::pair< float, float > >					listPairs;
	std::list< std::pair< float, float > >::const_iterator	itc;
	std::list< float >										aChain;
	std::list< float >										bChain;

	if (_values.empty())
		return (_list);
	listPairs.insert(listPairs.begin(), _values.begin(), _values.end());
	if (isnan(listPairs.back().second))
	{
		bChain.push_back(listPairs.back().first);
		listPairs.pop_back();
	}
	if (!listPairs.empty())
	{
		listPairs = listMergeSort(listPairs);
		itc = listPairs.begin();
		aChain.push_back(itc->first);
		aChain.push_back(itc->second);
		while (++itc != listPairs.end())
		{
			aChain.push_back(itc->second);
			bChain.push_back(itc->first);
		}
	}
	_list = listBinaryInsert(aChain, bChain);
	return (_list);
};


static std::vector< float >	vectorBinaryInsert(std::vector< float > aChain, const std::vector< float > bChain)
{
	long int								jsthalThis;
	long int								jsthalLast;
	std::vector< float >::const_iterator	jsthalIt;
	std::vector< float >::const_iterator	jsthalIte;

	jsthalThis = 1;
	jsthalLast = 0;
	jsthalIt = bChain.begin();
	jsthalIte = jsthalIt - 1;
	jsthalIncrement(jsthalLast, jsthalThis);
	for (std::size_t i = 0; i < bChain.size(); ++i)
	{
		aChain.insert(std::lower_bound(aChain.begin(), aChain.end(), *jsthalIt), *jsthalIt);
		--jsthalIt;
		if (jsthalIt <= jsthalIte)
		{
			jsthalIt += jsthalThis - jsthalLast;
			jsthalIte += jsthalThis - jsthalLast;
			jsthalIncrement(jsthalLast, jsthalThis);
			jsthalIt += jsthalThis - jsthalLast;
			jsthalIt = (jsthalIt >= bChain.end()) ? bChain.end() - 1 : jsthalIt;
		}
	};
	return (aChain);
};

std::vector< std::pair< float, float > >	vectorMerge(std::vector< std::pair< float, float > > aPairs, std::vector< std::pair< float, float > > bPairs)
{
	std::vector< std::pair< float, float > >			cPairs;

	std::merge(aPairs.begin(), aPairs.end(), bPairs.begin(), bPairs.end(), std::back_inserter(cPairs), sortBySecond);
	return (cPairs);
}

static std::vector< std::pair< float, float > >	vectorMergeSort(std::vector< std::pair< float, float > > vectorPairs)
{
	std::vector< std::pair< float, float > >			aPairs;
	std::vector< std::pair< float, float > >			bPairs;
	std::vector< std::pair< float, float > >::iterator	midPoint;

	if (vectorPairs.size() <= 1)
		return (vectorPairs);
	midPoint = vectorPairs.begin() + vectorPairs.size() / 2;
	aPairs.insert(aPairs.begin(), vectorPairs.begin(), midPoint);
	aPairs = vectorMergeSort(aPairs);
	bPairs.insert(bPairs.begin(), midPoint, vectorPairs.end());
	bPairs = vectorMergeSort(bPairs);
	return (vectorMerge(aPairs, bPairs));
};

std::vector< float >	PmergeMe::sortUsingVector(void)
{
	std::vector< std::pair< float, float > >					vectorPairs;
	std::vector< std::pair< float, float > >::const_iterator	itc;
	std::vector< float >										aChain;
	std::vector< float >										bChain;

	if (_values.empty())
		return (_vector);
	vectorPairs = _values;
	if (isnan(vectorPairs.back().second))
	{
		bChain.push_back(vectorPairs.back().first);
		vectorPairs.pop_back();
	}
	if (!vectorPairs.empty())
	{
		vectorPairs = vectorMergeSort(vectorPairs);
		itc = vectorPairs.begin();
		aChain.push_back(itc->first);
		aChain.push_back(itc->second);
		while (++itc != vectorPairs.end())
		{
			aChain.push_back(itc->second);
			bChain.push_back(itc->first);
		}
	}
	_vector = vectorBinaryInsert(aChain, bChain);
	return (_vector);
};
