/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typetraits_test.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:12:17 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/13 15:24:53 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <type_traits>
#include "../TypeTraits.hpp"
/*does not compile with the c++98 flag because of std::enable_if tests*/
int main()
{
	std::cout <<"std::enable_if: " <<std::endl;

	std::cout <<"testing ft::enable_if: " <<std::endl;
	
	std::cout <<std::boolalpha;
	std::cout <<"std::is_integral: " <<std::endl;
	std::cout <<"char: " <<std::is_integral<char>::value <<std::endl;
	std::cout <<"unsigned int: " <<std::is_integral<unsigned int>::value <<std::endl;
	std::cout <<"const int: " <<std::is_integral<const int>::value <<std::endl;
	std::cout <<"const volatile long: " <<std::is_integral<const volatile long>::value <<std::endl;
	std::cout <<"float: " <<std::is_integral<float>::value <<std::endl;

	std::cout <<std::endl <<"testing ft::is_integral: " <<std::endl;
	std::cout <<"char: " <<ft::is_integral<char>::value <<std::endl;
	std::cout <<"unsigned int: " <<ft::is_integral<unsigned int>::value <<std::endl;
	std::cout <<"const int: " <<ft::is_integral<const int>::value <<std::endl;
	std::cout <<"const volatile long: " <<ft::is_integral<const volatile long>::value <<std::endl;
	std::cout <<"float: " <<ft::is_integral<float>::value <<std::endl;
	return 0;
}