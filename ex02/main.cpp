/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 19:18:14 by marudlof          #+#    #+#             */
/*   Updated: 2026/10/07 15:54:32 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "A.hpp"
#include "B.hpp"
#include "Base.hpp"
#include "C.hpp"
#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>

Base*	generate(void)
{
	switch (std::rand() % 3)
	{
		case 0:
			return (new A());
		case 1:
			return (new B());
		default:
			return (new C());
	}
}

void	identify(Base* p)
{
	if (p == NULL)
	{
		std::cout << "the pointer is NULL" << std::endl;
		return ;
	}
	if (dynamic_cast<A*>(p) != NULL)
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p) != NULL)
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p) != NULL)
		std::cout << "C" << std::endl;
	else
		std::cout << "unknown type" << std::endl;
}

void	identify(Base& p)
{
	try
	{
		A&	a = dynamic_cast<A&>(p);

		(void)a;
		std::cout << "A" << std::endl;
		return ;
	}
	catch (std::exception&)
	{
	}
	try
	{
		B&	b = dynamic_cast<B&>(p);

		(void)b;
		std::cout << "B" << std::endl;
		return ;
	}
	catch (std::exception&)
	{
	}
	try
	{
		C&	c = dynamic_cast<C&>(p);

		(void)c;
		std::cout << "C" << std::endl;
		return ;
	}
	catch (std::exception&)
	{
	}
	std::cout << "unknown type" << std::endl;
}

int	main(void)
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	std::cout << "=== Eight random objects ===" << std::endl;
	for (int idx = 0; idx < 8; idx++)
	{
		Base*	object = generate();

		std::cout << "object " << idx << " -> pointer: ";
		identify(object);
		std::cout << "            reference: ";
		identify(*object);
		delete object;
	}

	std::cout << std::endl << "=== Known types ===" << std::endl;
	A	a;
	B	b;
	C	c;

	std::cout << "an A: ";
	identify(&a);
	std::cout << "a B: ";
	identify(b);
	std::cout << "a C: ";
	identify(&c);

	std::cout << std::endl << "=== A null pointer ===" << std::endl;
	identify(static_cast<Base*>(NULL));

	return (0);
}
