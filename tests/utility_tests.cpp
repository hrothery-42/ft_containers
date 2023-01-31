/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_tests.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 10:15:27 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/13 11:07:14 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utility>
#include <iostream>
#include "../Utility.hpp"

int main(void) 
{
	std::cout <<std::boolalpha;
	std::pair<char, int> secretCode;
	std::pair<char, int> newElement('B', 5000);
	std::pair<char, int> copyConstructedElement(newElement);
	
	std::cout <<"before initializing the pair values: " <<secretCode.first <<", " <<secretCode.second <<std::endl;
	std::cout <<"std::pair:" <<std::endl;
	secretCode.first = 'A';
	secretCode.second = 145;
	std::cout <<"secretCode elements: " <<secretCode.first <<", " <<secretCode.second <<std::endl;
	std::cout <<"newElement: " <<newElement.first <<", " <<newElement.second <<std::endl;
	std::cout <<"copyConstructedElement: " <<copyConstructedElement.first <<", " <<copyConstructedElement.second <<std::endl;
	std::cout <<"equal operator: new values secretCode = newElement: ";
	secretCode = newElement;
	std::cout <<secretCode.first <<", " <<secretCode.second <<std::endl;
	std::pair<char, int> anotherPair = std::make_pair('C', 4);
	std::cout <<"std::make_pair: another Pair: " <<anotherPair.first <<", " <<anotherPair.second <<std::endl;
	

	
	ft::pair<char, int> ft_secretCode;
	ft::pair<char, int> ft_newElement('B', 5000);
	ft::pair<char, int> ft_copyConstructedElement(ft_newElement);
	std::cout <<std::endl <<"Testing ft::pair: " <<std::endl;

	std::cout <<"before initializing the pair values: " <<ft_secretCode.first <<", " <<ft_secretCode.second <<std::endl;
	ft_secretCode.first = 'A';
	ft_secretCode.second = 145;
	std::cout <<"secretCode elements: " <<ft_secretCode.first <<", " <<ft_secretCode.second <<std::endl;
	std::cout <<"newElement: " <<ft_newElement.first <<", " <<ft_newElement.second <<std::endl;
	std::cout <<"copyConstructedElement: " <<ft_copyConstructedElement.first <<", " <<ft_copyConstructedElement.second <<std::endl;
	std::cout <<"equal operator: new values secretCode = newElement: ";
	ft_secretCode = ft_newElement;
	std::cout <<ft_secretCode.first <<", " <<ft_secretCode.second <<std::endl;
	ft::pair<char, int> ft_anotherPair = ft::make_pair('C', 4);
	std::cout <<"ft::make_pair: another Pair: " <<ft_anotherPair.first <<", " <<ft_anotherPair.second <<std::endl;
	
	return 0;
}