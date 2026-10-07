/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 18:01:22 by marudlof          #+#    #+#             */
/*   Updated: 2026/10/07 15:40:06 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Data.hpp"
#include "Serializer.hpp"
#include <iostream>

static void	ft_print_data(const std::string& label, const Data* data)
{
	std::cout << label << std::endl
		<< "adress:		" << data << std::endl
		<< "id:		" << data->id << std::endl
		<< "name:		" << data->name << std::endl
		<< "balance:	" << data->balance << std::endl
		<< std::endl;
}

int	main(void)
{
	Data		data;
	uintptr_t	raw;
	Data*		restored;

	data.id = 42;
	data.name = "Mathis RUDLOFF";
	data.balance = 421.124;

	raw = Serializer::serialize(&data);
	restored = Serializer::deserialize(raw);

	std::cout << "=== Serialization ===" << std::endl;
	ft_print_data("original", &data);
	std::cout << "serialized: " << raw << std::endl;
	ft_print_data("restored", restored);

	std::cout << std::endl << "=== Comparison ===" << std::endl;
	std::cout << std::boolalpha;
	std::cout << "restored == &data: " << (restored == &data) << std::endl;
	std::cout << "same content: "
		<< (restored->id == data.id
			&& restored->name == data.name
			&& restored->balance == data.balance)
		<< std::endl;

	std::cout << std::endl << "=== Writing through the restored pointer ===" << std::endl;
	restored->id = 1;
	restored->name = "42 Angouleme";
	ft_print_data("original", &data);

	std::cout << std::endl << "=== A pointer coming from the heap ===" << std::endl;
	Data*	heap = new Data();

	heap->id = 7;
	heap->name = "Darius Kaymak";
	heap->balance = -999;
	std::cout << "deserialize(serialize(heap)) == heap: "
		<< (Serializer::deserialize(Serializer::serialize(heap)) == heap)
		<< std::endl;
	ft_print_data("heap", Serializer::deserialize(Serializer::serialize(heap)));
	delete heap;

	return (0);
}
