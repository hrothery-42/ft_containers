/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_testing.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:28:20 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/13 11:43:32 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <time.h>
#include <vector>
#include "../Vector.hpp"
#include <iterator>
#include "../RandomAccessIterator.hpp"

typedef struct s_data {
	int x;
}	t_data;

int main()
{
	clock_t	tstart = clock();
	//access and assign value with *
	ft::vector<int> myVec;
	myVec.push_back(0);
	myVec.push_back(1);
	myVec.push_back(2);
	myVec.push_back(3);
	ft::vector<int>::iterator it;
	it = myVec.begin();
	std::cout <<"Vector elements are: ";
	for (int i = 0; i < myVec.size(); i++)
		std::cout <<myVec.at(i) <<" ";
	std::cout <<std::endl;
	std::cout <<"it = " <<*it <<std::endl;
	std::cout <<"Pre-increment operator ++it: " <<*(++it) <<std::endl;
	std::cout <<"Post-increment operator it++: " <<*(it++) <<" " <<*it <<std::endl;
	std::cout <<"Pre-decrement operator --it: " <<*(--it) <<std::endl;
	std::cout <<"Post-decrement operator it--: " <<*(it--) <<" " <<*it <<std::endl;
	
	ft::vector<int>::iterator it2 = it + 3;
	std::cout <<std::endl <<"Testing equality operator ==" <<std::endl;
	std::cout <<"it = " <<*it <<",  it2 = " <<*it2 <<std::endl;
	std::cout <<"it == it2 is ";
	if (it2 == it)
		std::cout <<"true" <<std::endl;
	else 
		std::cout <<"false" <<std::endl;
	it2 = it;
	std::cout <<"it = " <<*it <<",  it2 = " <<*it2 <<std::endl;
	std::cout <<"it == it2 is ";
	if (it2 == it)
		std::cout <<"true" <<std::endl;
	else 
		std::cout <<"false" <<std::endl;

	std::cout <<std::endl <<"Testing inequality operator !=" <<std::endl;
	it2 = myVec.end() - 1;
	std::cout <<"it = " <<*it <<",  it2 = " <<*it2 <<std::endl;
	std::cout <<"it != it2 is ";
	if (it2 != it)
		std::cout <<"true" <<std::endl;
	else 
		std::cout <<"false" <<std::endl;
	it2 = it;
	std::cout <<"it = " <<*it <<",  it2 = " <<*it2 <<std::endl;
	std::cout <<"it != it2 is ";
	if (it2 != it)
		std::cout <<"true" <<std::endl;
	else 
		std::cout <<"false" <<std::endl;
	
	std::cout <<std::endl <<"reassigning values using dereference *: " <<std::endl;
	it = myVec.begin();
	*it = 10; *++it= 9; *++it = 8; *++it = 7;
	std::cout <<"Values reassigned, printing vector: " <<std::endl;
	for (int i = 0; i < myVec.size(); i++)
		std::cout <<myVec.at(i) <<" ";
	std::cout <<std::endl <<std::endl;

	std::cout <<"testing operator -> using vector<t_data>: " <<std::endl;
	t_data DataSt;
	DataSt.x = 1;
	ft::vector<t_data> DataVec;
	DataVec.push_back(DataSt);
	ft::vector<t_data>::iterator DataIt;
	DataIt = DataVec.begin();
	std::cout <<"DataIt->x: " <<DataIt->x <<std::endl;

	std::cout <<std::endl <<"Testing relational operators:" <<std::endl;
	it = myVec.begin();
	it2 = it + 1;
	ft::vector<int>::iterator it3(it);
	std::cout <<"it = vec.begin(); it2 = it + 1; it3 = it" <<std::endl;
	if (it < it2)
		std::cout <<"it < it2" <<std::endl;
	else
		std::cout <<"!(it < it2)" <<std::endl;
	if (it > it2)
		std::cout <<"it > it2)" <<std::endl;
	else 
		std::cout <<"!(it > it2)" <<std::endl;
	if (it <= it3)
		std::cout <<"it <= it3" <<std::endl;
	else
		std::cout <<"!(it <= it3" <<std::endl;

	std::cout <<std::endl <<"testing offset dereference operator: " <<std::endl;
	it = myVec.begin();
	std::cout <<"Vector elements are: ";
	for (int i = 0; i < myVec.size(); i++)
		std::cout <<myVec.at(i) <<" ";
	std::cout <<std::endl;
	std::cout <<"it[0] = " <<it[0] <<", it[1] = " <<it[1] <<", it[2] = " <<it[2] <<std::endl;
	
	std::cout <<std::endl <<"testing arithmetic operators (see vector elements above): " <<std::endl;
	it = myVec.begin();
	std::cout <<"value of iterator is " <<*it <<std::endl;
	std::cout <<"value of iterator + 2 is " <<*(it + 2) <<std::endl;
	it = myVec.end() - 1;
	std::cout <<"new value of iterator is " <<*it <<std::endl;
	std::cout <<"value of iterator - 1 is " <<*(it - 1) <<std::endl;
	it = myVec.begin();
	std::cout <<"value of iterator is " <<*it <<std::endl;
	it += 3;
	std::cout <<"iterator += 3 = " <<*it <<std::endl;
	std::cout <<"value of iterator is now " <<*it <<std::endl;
	it -=2;
	std::cout <<"iterator -= 2 = " <<*it <<std::endl;
	
	std::cout <<"testing difference operator between 2 iterators" <<std::endl;
	it = myVec.begin();
	it2 = it + 1;
	std::cout <<"it - it2 = " <<it - it2 <<std::endl;
	std::cout <<"Time taken: " <<(double)(clock() - tstart)/CLOCKS_PER_SEC <<std::endl;
	return 0;
}