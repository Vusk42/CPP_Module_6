/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 17:03:14 by marudlof          #+#    #+#             */
/*   Updated: 2026/10/07 15:38:21 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCALARCONVERTER_HPP
# define SCALARCONVERTER_HPP

# include <string>

class ScalarConverter
{
	private:
		enum LiteralType
		{
			CHAR,
			INT,
			FLOAT,
			DOUBLE,
			INVALID
		};

		ScalarConverter(void);
		ScalarConverter(const ScalarConverter& other);
		ScalarConverter&	operator=(const ScalarConverter& other);
		~ScalarConverter(void);

		static bool	_isPseudoFloat(const std::string& literal);
		static bool	_isPseudoDouble(const std::string& literal);
		static bool	_isChar(const std::string& literal);
		static bool	_isInt(const std::string& literal);
		static bool	_isFloat(const std::string& literal);
		static bool	_isDouble(const std::string& literal);

		static bool	_isNan(double value);
		static bool	_isInf(double value);

		static LiteralType	_detectType(const std::string& literal);
		static double		_toDouble(const std::string& literal,
								LiteralType type);

		static void	_printReal(double value, bool asFloat);
		static void	_printChar(double value);
		static void	_printInt(double value);
		static void	_printFloat(double value);
		static void	_printDouble(double value);
		static void	_printImpossible(void);

	public:
		static void	convert(const std::string& literal);
};

#endif
