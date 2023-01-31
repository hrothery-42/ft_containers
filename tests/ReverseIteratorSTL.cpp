/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReverseIteratorSTL.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:15:26 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/13 15:19:12 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReverseIterator_tests.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:10:46 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/13 15:14:29 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iterator>
#include <iostream>
#include <cstddef>
#include <time.h>

int main(void)
{
	clock_t		tstart = clock();
	std::vector<int> myVec;
	for (size_t i = 0; i < 10; i++)
		myVec.push_back(i);
	std::cout <<"Vector elements are: " <<std::endl;
	for (size_t i = 0; i < myVec.size(); i++)
		std::cout <<myVec.at(i) <<" ";
	std::cout <<std::endl;
	std::vector<int>::iterator it = myVec.begin();
	std::vector<int>::reverse_iterator it_rev;
	std::cout <<"Dereference *it_rev = myVec.rbegin() = " <<*(it_rev = myVec.rbegin()) <<std::endl;

	std::cout <<"Dereference *it_rev = myVec.rend() = " <<*(it_rev = myVec.rend()) <<std::endl;
	if (*(it = myVec.begin()) == *(it_rev = myVec.rend()))
		std::cout <<"iterator.begin() = reverse_iterator.rend()" <<std::endl;
	std::cout <<"The vector elements in reverse order are: ";
	it_rev = myVec.rbegin();
	for (size_t i = 0; i < myVec.size(); i++)
		std::cout <<it_rev[i] <<" ";
	std::cout <<std::endl;
	
	it_rev = myVec.rend();
	std::cout <<"pre-decrement(from rend()): ";
	std::cout <<*--it_rev <<" " <<*--it_rev <<" " <<*--it_rev <<std::endl;
	std::cout <<"post-decrement: " <<*(it_rev--) <<" " <<*it_rev <<std::endl;
	std::cout <<"-= operator: it_rev -= 2 = " <<*(it_rev -= 2) <<std::endl;
	std::cout <<"+= operator: it_rev += 1 = " <<*(it_rev += 1) <<std::endl;
	std::cout <<"pre-increment ++it_rev: " <<*++it_rev <<" and post-increment it_rev++: " <<*(it_rev++) <<" " <<*it_rev <<std::endl;
	std::cout <<"- operator: it_rev - 3 = " <<*(it_rev - 3) <<", *it_rev(has not changed) = " <<*it_rev <<std::endl;
	std::cout <<"+ operator: it_rev + 1 = " <<*(it_rev + 1) <<", *it_rev(has not changed) = " <<*it_rev <<std::endl;
	std::cout <<"testing offset dereference operator: " <<std::endl;
	it_rev = myVec.rbegin();
	std::cout <<"it_rev[0] = " <<it_rev[0] <<", it_rev[1] = " <<it_rev[1] <<", it_rev[4] = " <<it_rev[4] <<std::endl;
	std::vector<int>::reverse_iterator it_rev2 = it_rev + 3;
	std::vector<int>::reverse_iterator it_rev3 = it_rev2 - 2;
	std::cout <<"it_rev: " <<*it_rev <<", it_rev2 = it_rev + 3: " <<*it_rev2 <<std::endl;
	std::cout <<"it_rev2: " <<*it_rev2 <<", it_rev3 = it_rev2 - 2: " <<*it_rev3 <<std::endl;
	
	std::cout <<"****************************************" <<std::endl;
	std::cout <<"*****testing non member functions*******" <<std::endl;
	std::cout <<"****************************************" <<std::endl;
	std::cout <<"it_rev: " <<*it_rev <<", it_rev2: " <<*it_rev2 <<", it_rev3: " <<*it_rev3 <<std::endl;
	std::cout <<"comparison between 2 instances:" <<std::endl;
	if (it_rev == it_rev2)
		std::cout <<"it_rev == it_rev2" <<std::endl;
	else
		std::cout <<"!(it_rev == it_rev2)" <<std::endl;
	if (it_rev != it_rev2)
		std::cout <<"it_rev != it_rev2" <<std::endl;
	else
		std::cout <<"!(it_rev != it_rev2)" <<std::endl;
	if (it_rev > it_rev2)
		std::cout <<"it_rev > it_rev2" <<std::endl;
	else
		std::cout <<"!(it_rev > it_rev2)" <<std::endl;
	if (it_rev < it_rev2)
		std::cout <<"it_rev < it_rev2" <<std::endl;
	else
		std::cout <<"!(it_rev < it_rev2)" <<std::endl;
	if (it_rev2 <= it_rev3)
		std::cout <<"it_rev2 <= it_rev3" <<std::endl;
	else
		std::cout <<"!(it_rev2 <= it_rev3)" <<std::endl;
	if (it_rev3 <= it_rev2)
		std::cout <<"it_rev3 <= it_rev2" <<std::endl;
	else
		std::cout <<"!(it_rev3 <= it_rev2)" <<std::endl;
	std::cout <<"Testing + and - non member functions: " <<std::endl;
	std::cout <<"it_rev3 + 4 = " <<*(it_rev3 + 4) <<std::endl;
	std::cout <<"it_rev3 - it_rev2 = " <<it_rev3 - it_rev2 <<std::endl;
	std::cout <<"Time taken: " <<(double)(clock() - tstart)/CLOCKS_PER_SEC <<std::endl;
	return 0;
}