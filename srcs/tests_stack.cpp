#include "main.hpp"

void	test_stack(void)
{
	std::cout << std::endl;
	std::cout << "[------------ Tests stack ------------]"
	<< std::endl;

	test_stack_init();
	test_stack_member_functions();
	test_stack_relational_operators();
}
