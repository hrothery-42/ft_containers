/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_test.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 11:28:12 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/14 11:54:09 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Utility.hpp"
#include <utility>
#include <iostream>

int main()
{
	std::cout <<ft::is_integral<float>() <<" " << std::is_integral<float>() <<std::endl;
	std::cout <<ft::is_integral<int>() <<" " <<std::is_integral<int>()<<std::endl ;
	std::cout <<ft::is_integral<bool>() <<" " << std::is_integral<bool>() <<std::endl;
	std::cout <<ft::is_integral<char>() <<" " << std::is_integral<char>() <<std::endl;
	std::cout <<ft::is_integral<signed char>() <<" " << std::is_integral<signed char>() <<std::endl;
	std::cout <<ft::is_integral<unsigned char>() <<" " << std::is_integral<unsigned char>() <<std::endl;
	std::cout <<ft::is_integral<wchar_t>() <<" " << std::is_integral<wchar_t>() <<std::endl;
	std::cout <<ft::is_integral<char16_t>() <<" " << std::is_integral<char16_t>() <<std::endl;
	std::cout <<ft::is_integral<short>() <<" " << std::is_integral<short>() <<std::endl;
	std::cout <<ft::is_integral<unsigned short>() <<" " << std::is_integral<unsigned short>() <<std::endl;
	std::cout <<ft::is_integral<unsigned int>() <<" " << std::is_integral<unsigned int>() <<std::endl;
	std::cout <<ft::is_integral<long>() <<" " << std::is_integral<long>() <<std::endl;
	std::cout <<ft::is_integral<unsigned long>() <<" " << std::is_integral<unsigned long>() <<std::endl;
	std::cout <<ft::is_integral<long long>() <<" " << std::is_integral<long long>() <<std::endl;
	std::cout <<ft::is_integral<unsigned long long>() <<" " << std::is_integral<unsigned long long>() <<std::endl;
}