#ifndef		P_MERGE_ME_HPP
# define	P_MERGE_ME_HPP

# include	<vector>
# include	<list>
# include	<utility>
# include	<string>
# include	<exception>

class	PmergeMe {
	private:
		std::list< float >							_list;
		std::vector< float >						_vector;
		std::vector< std::pair< float, float > >	_values;
	protected:
	public:
		PmergeMe(void);
		~PmergeMe(void);
		PmergeMe(const PmergeMe &pMergeMeREF);
		PmergeMe	&operator=(const PmergeMe &pMergeMeREF);
		PmergeMe(unsigned int nNumbers, const char **numbers) throw (std::exception);

		const std::list< float >		&getList(void) const;
		const std::vector< float >		&getVector(void) const;
		const std::vector< std::pair< float, float > >	&getValues(void) const;

		static std::vector< float >	loadValues(unsigned int nNumbers, const char **numbers);
		static std::vector< std::pair< float, float > >	makePairs(const std::vector< float > &values);
		std::list< float >		sortUsingList(void);
		std::vector< float >	sortUsingVector(void);

		class	ErrorInputException;
};

class	PmergeMe::ErrorInputException: public std::exception {
	private:
		std::string	_errorMsg;
	protected:
	public:
		ErrorInputException(const std::string &errorMsg) throw ()
		{
			_errorMsg = errorMsg;
		};
		virtual ~ErrorInputException(void) throw () {};
		const char	*what(void) const throw ()
		{
			return (_errorMsg.c_str());
		}
};

#endif