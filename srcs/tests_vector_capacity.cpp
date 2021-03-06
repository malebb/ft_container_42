#include "main.hpp"

static void		test_size(void)
{
	std::cout << std::endl;
	std::cout << ">> Test size function" << std::endl;
	std::cout << std::endl;

	LIB::vector<int>				nbrs;
	LIB::vector<char>			letters;

	nbrs.push_back(11);
	nbrs.push_back(12);
	nbrs.push_back(13);
	nbrs.push_back(14);

	display_vector("nbrs = ", nbrs);
	display_vector("letters", letters);

	std::cout << "nbrs.size() = " << nbrs.size() << std::endl;
	std::cout << "letters.size() = " << letters.size() << std::endl;

	std::cout << std::endl;
}

static void		test_max_size(void)
{
	std::cout << std::endl;
	std::cout << ">> Test max size function" << std::endl;
	std::cout << std::endl;

	LIB::vector<bool>				boolean;
	LIB::vector<std::string>			strs(3, "string");

	boolean.push_back(true);
	boolean.push_back(false);
	boolean.push_back(true);

	display_vector("boolean", boolean);
	display_vector("strs", strs);

	std::cout << "nbrs.max_size() = " << boolean.max_size() << std::endl;
	std::cout << "strs.max_size() = " << strs.max_size() << std::endl;

	std::cout << std::endl;
}

static void		test_resize(void)
{
	LIB::vector<int>		hundreds(3, 100);

	std::cout << std::endl;
	std::cout << ">> Test resize function" << std::endl;
	std::cout << std::endl;

	display_vector("hundreds", hundreds);

	hundreds.resize(6, 200);
	std::cout << std::endl;
	std::cout << "hundreds.resize(6, 200)" << std::endl;
	std::cout << std::endl;

	display_vector("hundreds", hundreds);


	hundreds.resize(4);
	std::cout << std::endl;
	std::cout << "hundreds.resize(4)" << std::endl;
	std::cout << std::endl;

	display_vector("hundreds", hundreds);
}

static void		test_reserve(void)
{
	std::cout << std::endl;
	std::cout << ">> Test reserve function" << std::endl;
	std::cout << std::endl;

	LIB::vector<int>				nbrs;

	std::cout << "nbrs.capacity() = " << nbrs.capacity() << std::endl;
	std::cout << "nbrs.reserve(2)" << std::endl;
	nbrs.reserve(2);
	
	std::cout << "nbrs.capacity() = " << nbrs.capacity() << std::endl;
	std::cout << "nbrs.reserve(10)" << std::endl;
	nbrs.reserve(10);
	
	std::cout << "nbrs.capacity() = " << nbrs.capacity() << std::endl;
	std::cout << "nbrs.reserve(nbrs.max_size() + 1) ==> exception" << std::endl;
	try
	{
		nbrs.reserve(nbrs.max_size() + 1);
	}
	catch(std::exception const & e)
	{
		std::cout << e.what() << std::endl;
	}
	std::cout << std::endl;
}

static void		test_capacity(void)
{
	std::cout << std::endl;
	std::cout << ">> Test capacity function" << std::endl;
	std::cout << std::endl;

	LIB::vector<std::string>		plants;

	display_vector("plants", plants);

	std::cout << "plants.capacity() = " << plants.capacity() << std::endl;
	std::cout << std::endl;

	std::cout << "plants.push_back(\"tree\")" << std::endl;
	plants.push_back("tree");
	display_vector("plants", plants);

	std::cout << "plants.capacity() = " << plants.capacity() << std::endl;
	std::cout << std::endl;

	std::cout << "plants.push_back(\"tulip\")" << std::endl;
	std::cout << "plants.push_back(\"daisy\")" << std::endl;
	plants.push_back("tulip");
	plants.push_back("daisy");
	display_vector("plants", plants);

	std::cout << "plants.capacity() = " << plants.capacity() << std::endl;
	std::cout << std::endl;
}

static void		test_empty(void)
{
	LIB::vector<int>				empty_vector;
	LIB::vector<int>			filled_vector(4, 1);


	std::cout << std::endl;
	std::cout << ">> Test empty function" << std::endl;
	std::cout << std::endl;

	display_vector("empty_vector", empty_vector);
	display_vector("filled_vector", filled_vector);

	std::cout << "empty_vector.empty() = "<< empty_vector.empty() << std::endl;
	std::cout << "filled_vector.empty() = "<< filled_vector.empty() << std::endl;

	std::cout << std::endl;
}

void	test_vector_capacity(void)
{
	std::cout << std::endl;
	std::cout << "<------------ Test capacity ------------>"
	<< std::endl;
	std::cout << std::endl;

	std::cout << "********************************************" << std::endl;
	test_size();
	std::cout << "********************************************" << std::endl;
	test_max_size();
	std::cout << "********************************************" << std::endl;
	test_resize();
	std::cout << "********************************************" << std::endl;
	test_reserve();
	std::cout << "********************************************" << std::endl;
	test_capacity();
	std::cout << "********************************************" << std::endl;
	test_empty();
	std::cout << "********************************************" << std::endl;
}
