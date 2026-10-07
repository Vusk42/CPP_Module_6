/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marudlof <marudlof@42.angouleme.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/09 17:09:11 by marudlof          #+#    #+#             */
/*   Updated: 2026/10/07 15:38:34 by marudlof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>

bool	ScalarConverter::_isPseudoFloat(const std::string& literal)
{
	return (literal == "nanf" || literal == "inff" || literal == "+inff" || literal == "-inff");
}

bool	ScalarConverter::_isPseudoDouble(const std::string& literal)
{
	return (literal == "nan" || literal == "inf" || literal == "+inf" || literal == "-inf");
}

bool	ScalarConverter::_isChar(const std::string& literal)
{
	if (literal.size() == 3 && literal[0] == '\'' && literal[2] == '\'')
		return (true);
	if (literal.size() == 1 && !std::isdigit(static_cast<unsigned char>(literal[0])))
		return (true);
	return (false);
}

bool	ScalarConverter::_isInt(const std::string& literal)
{
	size_t	idx = 0;

	if (literal.empty())
		return (false);
	if (literal[0] == '+' || literal[0] == '-')
		idx = 1;
	if (idx == literal.size())
		return (false);
	while (idx < literal.size())
	{
		if (!std::isdigit(static_cast<unsigned char>(literal[idx])))
			return (false);
		idx++;
	}
	return (true);
}

bool	ScalarConverter::_isDouble(const std::string& literal)
{
	size_t	idx = 0;
	size_t	digits = 0;
	size_t	dots = 0;

	if (literal.empty())
		return (false);
	if (literal[0] == '+' || literal[0] == '-')
		idx = 1;
	while (idx < literal.size())
	{
		if (literal[idx] == '.')
			dots++;
		else if (std::isdigit(static_cast<unsigned char>(literal[idx])))
			digits++;
		else
			return (false);
		idx++;
	}
	return (digits > 0 && dots == 1);
}

bool	ScalarConverter::_isFloat(const std::string& literal)
{
	std::string	body;

	if (literal.size() < 2 || literal[literal.size() - 1] != 'f')
		return (false);
	body = literal.substr(0, literal.size() - 1);
	return (ScalarConverter::_isDouble(body) || ScalarConverter::_isInt(body));
}

bool	ScalarConverter::_isNan(double value)
{
	return (value != value);
}

bool	ScalarConverter::_isInf(double value)
{
	const double	infinity = std::numeric_limits<double>::infinity();

	return (value == infinity || value == -infinity);
}

ScalarConverter::LiteralType ScalarConverter::_detectType(const std::string& literal)
{
	if (literal.empty())
		return (ScalarConverter::INVALID);
	if (ScalarConverter::_isPseudoFloat(literal))
		return (ScalarConverter::FLOAT);
	if (ScalarConverter::_isPseudoDouble(literal))
		return (ScalarConverter::DOUBLE);
	if (ScalarConverter::_isChar(literal))
		return (ScalarConverter::CHAR);
	if (ScalarConverter::_isInt(literal))
		return (ScalarConverter::INT);
	if (ScalarConverter::_isFloat(literal))
		return (ScalarConverter::FLOAT);
	if (ScalarConverter::_isDouble(literal))
		return (ScalarConverter::DOUBLE);
	return (ScalarConverter::INVALID);
}

double	ScalarConverter::_toDouble(const std::string& literal, LiteralType type)
{
	if (ScalarConverter::_isPseudoFloat(literal)
		|| ScalarConverter::_isPseudoDouble(literal))
	{
		if (literal[0] == 'n')
			return (std::numeric_limits<double>::quiet_NaN());
		if (literal[0] == '-')
			return (-std::numeric_limits<double>::infinity());
		return (std::numeric_limits<double>::infinity());
	}
	if (type == ScalarConverter::CHAR)
	{
		if (literal.size() == 1)
			return (static_cast<double>(literal[0]));
		return (static_cast<double>(literal[1]));
	}
	return (std::strtod(literal.c_str(), NULL));
}

void	ScalarConverter::_printReal(double value, bool asFloat)
{
	const char*	suffix = "";

	if (asFloat)
		suffix = "f";
	if (ScalarConverter::_isNan(value))
		std::cout << "nan" << suffix;
	else if (ScalarConverter::_isInf(value))
	{
		if (value < 0)
			std::cout << "-inf" << suffix;
		else
			std::cout << "+inf" << suffix;
	}
	else if (value == std::floor(value) && std::fabs(value) < 1e16)
	{
		std::cout << std::fixed << std::setprecision(1) << value << suffix;
		std::cout.unsetf(std::ios::floatfield);
		std::cout << std::setprecision(6);
	}
	else
		std::cout << value << suffix;
	std::cout << std::endl;
}

void	ScalarConverter::_printChar(double value)
{
	char	converted;

	std::cout << "char: ";
	if (ScalarConverter::_isNan(value) || ScalarConverter::_isInf(value)
		|| value < static_cast<double>(std::numeric_limits<char>::min())
		|| value > static_cast<double>(std::numeric_limits<char>::max()))
	{
		std::cout << "impossible" << std::endl;
		return ;
	}
	converted = static_cast<char>(value);
	if (!std::isprint(static_cast<unsigned char>(converted)))
		std::cout << "Non displayable" << std::endl;
	else
		std::cout << "'" << converted << "'" << std::endl;
}

void	ScalarConverter::_printInt(double value)
{
	std::cout << "int: ";
	if (ScalarConverter::_isNan(value) || ScalarConverter::_isInf(value)
		|| value < static_cast<double>(std::numeric_limits<int>::min())
		|| value > static_cast<double>(std::numeric_limits<int>::max()))
		std::cout << "impossible" << std::endl;
	else
		std::cout << static_cast<int>(value) << std::endl;
}

void	ScalarConverter::_printFloat(double value)
{
	const float	converted = static_cast<float>(value);

	std::cout << "float: ";
	if (!ScalarConverter::_isNan(value) && !ScalarConverter::_isInf(value)
		&& ScalarConverter::_isInf(static_cast<double>(converted)))
		std::cout << "impossible" << std::endl;
	else
		ScalarConverter::_printReal(static_cast<double>(converted), true);
}

void	ScalarConverter::_printDouble(double value)
{
	std::cout << "double: ";
	ScalarConverter::_printReal(value, false);
}

void	ScalarConverter::_printImpossible(void)
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: impossible" << std::endl;
	std::cout << "double: impossible" << std::endl;
}

void	ScalarConverter::convert(const std::string& literal)
{
	LiteralType	type;
	double		value;

	type = ScalarConverter::_detectType(literal);
	if (type == ScalarConverter::INVALID)
	{
		std::cout << "\"" << literal << "\" is not a known literal:" << std::endl;
		ScalarConverter::_printImpossible();
		return ;
	}
	value = ScalarConverter::_toDouble(literal, type);
	ScalarConverter::_printChar(value);
	ScalarConverter::_printInt(value);
	ScalarConverter::_printFloat(value);
	ScalarConverter::_printDouble(value);
}
