#include "main.hpp"

static void		test_increment_decrement(void)
{
	ft::map<int, std::string>::iterator		it;
	ft::map<int, std::string>					nbrs;

	nbrs[1] = "one";
	nbrs[2] = "two";
	nbrs[3] = "three";
	nbrs[4] = "four";

	std::cout << std::endl;
	std::cout << ">> Test increment and decrement" << std::endl;
	std::cout << std::endl;

	display_map("nbrs", nbrs);
	it = nbrs.begin();
	std::cout << "it = " << "{" << it->first << " => " << it->second << "}"
		<< std::endl << std::endl;

	std::cout << "it++" << std::endl;
	it++;
	std::cout << "it = " << "{" << it->first << " => " << it->second << "}"
		<< std::endl << std::endl;

	std::cout << "it--" << std::endl;
	it--;
	std::cout << "it = " << "{" << it->first << " => " << it->second << "}"
		<< std::endl << std::endl;

	std::cout << "(++it)->first = " << (++it)->first << std::endl << std::endl;
	std::cout << "(--it)->first = " << (--it)->first << std::endl << std::endl;

	std::cout << "(it++)->first = " << (it++)->first << std::endl << std::endl;
	std::cout << "it = " << "{" << it->first << " => " << it->second << "}"
		<< std::endl << std::endl;

	std::cout << "(it--)->first = " << (it--)->first << std::endl;
	std::cout << "it = " << "{" << it->first << " => " << it->second << "}"
		<< std::endl << std::endl;
	std::cout << std::endl;
}


static void		test_comparison(void)
{
	ft::map<int, std::string>::iterator		it;
	ft::map<int, std::string>::iterator		it2;
	ft::map<int, std::string>					nbrs;

	nbrs[1] = "one";
	nbrs[2] = "two";
	nbrs[3] = "three";
	nbrs[4] = "four";

	std::cout << std::endl;
	std::cout << ">> Test comparison" << std::endl;
	std::cout << std::endl;
	
	display_map("nbrs", nbrs);

	it = nbrs.begin();
	it2 = it;
	it2++;

	std::cout << "it = " << "{" << it->first << " => " << it->second << "}"
		<< std::endl << std::endl;
	std::cout << "it2 = " << "{" << it2->first << " => " << it2->second << "}"
		<< std::endl << std::endl;

	std::cout << "it == it2 : ";
	check_comparison(it == it2);

	std::cout << "it != it2 : ";
	check_comparison(it != it2);
	std::cout << std::endl;
}

static void		test_member_access(void)
{
	ft::map<int, std::string>::iterator		it;
	ft::map<int, std::string>					nbrs;

	nbrs[1] = "one";
	nbrs[2] = "two";
	nbrs[3] = "three";
	nbrs[4] = "four";

	std::cout << std::endl;
	std::cout << ">> Test member access" << std::endl;
	std::cout << std::endl;
	
	display_map("nbrs", nbrs);

	it = nbrs.begin();

	std::cout << "it->first = " << it->first << std::endl;
	std::cout << "it->second = " << it->second << std::endl << std::endl;
	std::cout << "(*it).first = " << (*it).first << std::endl;
	std::cout << "(*it).second = " << (*it).second << std::endl << std::endl;
}

static void		test_const_iterator(void)
{
	std::cout << std::endl;
	std::cout << ">> Test const" << std::endl;
	std::cout << std::endl;

	ft::map<int, std::string>::const_iterator		const_it;
	ft::map<int, std::string>						nbrs;

	nbrs[1] = "one";
	nbrs[2] = "two";
	nbrs[3] = "three";
	nbrs[4] = "four";

	display_map("nbrs", nbrs);
	const_it = nbrs.begin();
	std::cout << "it = " << "{" << const_it->first << " => " << const_it->second << "}"
		<< std::endl << std::endl;
	std::cout << "const_it->second = \"first\" => impossible" << std::endl;
	//const_it->second = "first"; // impossible
	std::cout << "it = " << "{" << const_it->first << " => " << const_it->second << "}"
		<< std::endl << std::endl;
	std::cout << std::endl;
}

void	test_map_iterator(void)
{
	std::cout << std::endl;
	std::cout << "<------------ Test map iterator ------------>"
	<< std::endl;
	std::cout << std::endl;

	std::cout << "********************************************" << std::endl;
	test_increment_decrement();
	std::cout << "********************************************" << std::endl;
	test_comparison();
	std::cout << "********************************************" << std::endl;
	test_member_access();
	std::cout << "********************************************" << std::endl;
	test_const_iterator();
	std::cout << "********************************************" << std::endl;
}
