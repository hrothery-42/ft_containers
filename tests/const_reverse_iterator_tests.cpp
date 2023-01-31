/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const_reverse_iterator_tests.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:03:08 by hrothery          #+#    #+#             */
/*   Updated: 2022/11/14 11:17:38 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include <iterator>
#include "../Vector.hpp"
#include "../RandomAccessIterator.hpp"
#include "../ReverseIterator.hpp"

int main(void)
{
	std::vector<int> myVec;
	myVec.push_back(0);
	myVec.push_back(1);
	myVec.push_back(2);
	myVec.push_back(3);
	myVec.push_back(4);
	std::cout <<"Vector elements : " <<std::endl;
	for(int i = 0; i < myVec.size(); i++)
		std::cout <<myVec.at(i) <<" ";
	std::cout <<std::endl;
	std::vector<int>::const_iterator constIt = myVec.begin();
	std::vector<int>::const_reverse_iterator constRevIt(constIt);
	std::cout <<"const_reverse_iterator: " <<*constRevIt <<std::endl;
	std::cout <<"post-decrement " <<*constRevIt-- <<" " <<*constRevIt-- <<" " <<*constRevIt-- <<std::endl;
	std::cout <<"pre-decrement: " <<*--constRevIt <<std::endl;
	std::cout <<"arithmetic operators: " <<*(constRevIt - 1) <<" " <<*(constRevIt + 1) <<std::endl;
	std::cout <<"iterator[0]: " <<constRevIt[0] <<", iterator[1]: " <<constRevIt[1] <<std::endl;
	
	std::cout <<std::endl <<"testing ft:const_reverse_iterator: " <<std::endl;
	ft::vector<int> ftVec;
	ftVec.push_back(0);
	ftVec.push_back(1);
	ftVec.push_back(2);
	ftVec.push_back(3);
	ftVec.push_back(4);
	std::cout <<"ft::vector elements: " <<std::endl;
	for(int i = 0; i < ftVec.size(); i++)
		std::cout <<ftVec.at(i) <<" ";
	std::cout <<std::endl;
	ft::vector<int>::const_iterator ftConstIt = ftVec.begin();
	ft::vector<int>::const_reverse_iterator ftConstRev(ftConstIt);
	std::cout <<"ft::const_reverse_iterator: " <<*ftConstRev <<std::endl;
	std::cout <<"post-decrement " <<*ftConstRev-- <<" " <<*ftConstRev-- <<" " <<*ftConstRev-- <<std::endl;
	std::cout <<"pre-decrement: " <<*--ftConstRev <<std::endl;
	std::cout <<"arithmetic operators: " <<*(ftConstRev - 1) <<" " <<*(ftConstRev + 1) <<std::endl;
	std::cout <<"ft::iterator[0]: " <<ftConstRev[0] <<", ft::iterator[1]: " <<ftConstRev[1] <<std::endl;
	
	return 0;
}