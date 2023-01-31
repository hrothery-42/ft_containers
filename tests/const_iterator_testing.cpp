/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_iterator_testing.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 12:09:26 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/16 14:12:01 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include "../Vector.hpp"
#include <iterator>
#include "../RandomAccessIterator.hpp"
#include <iostream>

int main(void)
{
	std::vector<int> myVec;
	myVec.push_back(0);
	myVec.push_back(1);
	myVec.push_back(2);
	myVec.push_back(3);
	std::vector<int>::const_iterator cit(myVec.begin());

	std::cout <<"cit: " <<*cit  <<std::endl;
	cit++;
	std::cout <<"cit++: " <<*cit <<std::endl;

	ft::vector<int> ft_myVec;

	ft_myVec.push_back(0);
	ft_myVec.push_back(1);
	ft_myVec.push_back(2);
	ft_myVec.push_back(3);
	std::cout <<"vector elements: ";
	for (int i = 0; i < ft_myVec.size(); i++)
		std::cout <<ft_myVec.at(i) <<" ";
	std::cout <<std::endl;
	ft::vector<int>::const_iterator ft_cit(ft_myVec.begin());

	std::cout <<"ft_cit: " <<*ft_cit <<std::endl;
	ft_cit++;
	std::cout <<"ft_cit++: " <<*ft_cit <<std::endl;
	ft_cit--;
	std::cout <<"--ft_cit: " <<*ft_cit <<std::endl;
	std::cout <<"ft_cit + 2: " <<*(ft_cit + 2) <<std::endl;
	std::cout <<"ft_cit[0] = " <<ft_cit[0] <<", ft_cit[1] = " <<ft_cit[1] <<std::endl;
	std::cout <<"f_cit += 3: " <<*(ft_cit += 3) <<std::endl;

	
	return 0;
}
