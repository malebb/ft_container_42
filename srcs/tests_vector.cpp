#include "main.hpp"

void	test_vector(void)
{
	std::cout << std::endl;
	std::cout << "[------------ Tests vector ------------]"
	<< std::endl;

	test_vector_iterator();
	test_vector_reverse_iterator();
	test_vector_init();
	test_vector_capacity();
	test_vector_element_access();
	test_vector_modifiers();
	test_vector_allocator();
	test_vector_relational_operators();
}
