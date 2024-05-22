#include	<iostream>
#include	<ctime>
#include	"PmergeMe.hpp"

int	main(int argc, const char **argv)
{
	if (argc > 1)
	{
		try {
			PmergeMe	test(argc - 1, &argv[1]);
			clock_t		timer;

			timer = clock();
			test.sortUsingVector();
			timer = clock() - timer;
			for (std::vector< float >::const_iterator itc = test.getVector().begin(); itc != test.getVector().end(); ++itc)
			{
				std::cout << *itc
					<< " ";
			};
			std::cout << std::endl;
			std::cout << "Time spent using vector for "
				<< test.getVector().size()
				<< " items, were: "
				<< (float)timer / CLOCKS_PER_SEC
				<< std::endl;

			timer = clock();
			test.sortUsingList();
			timer = clock() - timer;
			for (std::list< float >::const_iterator itc = test.getList().begin(); itc != test.getList().end(); ++itc)
			{
				std::cout << *itc
					<< " ";
			};
			std::cout << std::endl;
			std::cout << "Time spent using vector for "
				<< test.getList().size()
				<< " items, were: "
				<< (float)timer / CLOCKS_PER_SEC
				<< std::endl;
		}
		catch (std::exception &e)
		{
			std::cerr << e.what()
				<< std::endl;
		}
	}
	else
		std::cout << "Usage: PmergeMe [int, int, ...]"
			<< std::endl;
	return (0);
}