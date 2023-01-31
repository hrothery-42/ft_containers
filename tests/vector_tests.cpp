/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_tests.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:16:11 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/13 11:24:30 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <algorithm>
#include <iterator>
#include "../Vector.hpp"
#include "../IteratorTraits.hpp"
#include "../RandomAccessIterator.hpp"
#include "../ReverseIterator.hpp"
#include "../TypeTraits.hpp"
#include "../Utility.hpp"
#include <iostream>

/*this test includes both std::vector and ft::vector for comparison*/

int main()
{
	std::vector<int> myVec(5, 1);
	std::cout <<"std operator[]: " <<std::endl;
	for (int i = 0; i < myVec.size(); i++)
		std::cout <<myVec[i] <<" ";
	std::cout <<std::endl;
	myVec[4] = 8;
	std::cout <<"myVec[4] = " <<myVec[4] <<std::endl;
	for (int i = 0; i < myVec.size(); i++)
		std::cout <<myVec[i] <<" ";
	std::cout <<std::endl;
	std::cout <<"front: " <<myVec.front() <<", back: " <<myVec.back() <<std::endl;
	std::cout <<"*data(): " <<*myVec.data() <<std::endl;
	*myVec.data() = 4;
	std::cout <<"reassigned first element: " <<*myVec.data() <<std::endl;
	
	std::cout <<std::endl;
	ft::vector<int> ftVec(5, 1);
	std::cout <<"test: ft operator[]: " <<std::endl;
	for (int i = 0; i < ftVec.size(); i++)
		std::cout <<ftVec[i] <<" ";
	std::cout <<std::endl;
	ftVec[4] = 8;
	std::cout <<"ftVec[4] = " <<ftVec[4] <<std::endl;
	for (int i = 0; i < ftVec.size(); i++)
		std::cout <<ftVec[i] <<" ";
	std::cout <<std::endl;
	std::cout <<"front: " <<ftVec.front() <<", back: " <<ftVec.back() <<std::endl;
	std::cout <<"*data(): " <<*ftVec.data() <<std::endl;
	*ftVec.data() = 4;
	std::cout <<"reassigned first element: " <<*ftVec.data() <<std::endl;

	std::cout <<std::endl <<"testing ft::empty: " <<std::boolalpha <<std::endl;
	ft::vector<char> ftVecChar;
	std::cout <<"old vector is empty: " <<ftVec.empty() <<", newly created vector is empty: " <<ftVecChar.empty()  <<std::endl;
	std::cout <<"ft::size(): size of old vector: " <<ftVec.size() <<", size of new vector: " <<ftVecChar.size() <<std::endl;
	std::cout <<"max_size() of old vector: " <<ftVec.max_size() <<", and max_size() of new vector: " <<ftVecChar.max_size() <<std::endl;
	std::vector<char> myVecChar;
	std::cout <<"comparing the max_size in stl: "  <<myVec.max_size() <<", " <<myVecChar.max_size() <<std::endl;
	
	std::cout <<std::endl <<"Testing ft::reserve: " <<std::endl;
	std::cout <<"size of vector: " <<ftVec.size() <<", capacity of vector: " <<ftVec.capacity() <<std::endl;
	ftVec.reserve(50);
	std::cout <<"increasing capacity to 50: " <<std::endl;
	std::cout <<"size of vector: " <<ftVec.size() <<", capacity of vector: " <<ftVec.capacity() <<std::endl;
	
	std::cout <<std::endl <<"Testing ft::insert: " <<std::endl;
	std::cout <<"vector elements: " <<std::endl;
	for (int i = 0; i < ftVec.size(); i++)
		std::cout <<ftVec.at(i) <<" ";
	std::cout <<std::endl;
	ftVec.insert(ftVec.begin(), 42);
	std::cout <<"inserting element 42 at the beginning of the vector:" <<std::endl;
	for (int i = 0; i < ftVec.size(); i++)
		std::cout <<ftVec.at(i) <<" ";
	std::cout <<std::endl;
	std::cout <<"inserting element 42 at the end of the vector: " <<std::endl;
	ftVec.insert(ftVec.end(), 42);
	for (int i = 0; i < ftVec.size(); i++)
		std::cout <<ftVec.at(i) <<" ";
	std::cout <<std::endl <<"size: " <<ftVec.size() <<", capacity: " <<ftVec.capacity() <<std::endl;
	std::cout <<"inserting element 42 in the middle of the vector: " <<std::endl;
	ftVec.insert(ftVec.begin() + 3, 42);
	for (int i = 0; i < ftVec.size(); i++)
		std::cout <<ftVec.at(i) <<" ";
	std::cout <<std::endl;
	std::cout <<"inserting 5 elements 4242 at the beginning of the vector: " <<std::endl;
	ftVec.insert(ftVec.begin(), 5, 4242);
	for (int i = 0; i < ftVec.size(); i++)
		std::cout <<ftVec.at(i) <<" ";
	std::cout <<std::endl <<"size: " <<ftVec.size() <<", capacity: " <<ftVec.capacity() <<std::endl;
	std::cout <<"inserting 2 elements 123 at the end of the vector: " <<std::endl;
	ftVec.insert(ftVec.end(), 2, 123);
	for (int i = 0; i < ftVec.size(); i++)
		std::cout <<ftVec.at(i) <<" ";
	std::cout <<std::endl <<"size: " <<ftVec.size() <<", capacity: " <<ftVec.capacity() <<std::endl;
	std::cout <<"inserting 3 elements 4 near the front of the vector: " <<std::endl;
	ftVec.insert(ftVec.begin() + 2, 3, 4);
	for (int i = 0; i < ftVec.size(); i++)
		std::cout <<ftVec.at(i) <<" ";
	std::cout <<std::endl <<"size: " <<ftVec.size() <<", capacity: " <<ftVec.capacity() <<std::endl;
	
	std::cout <<std::endl <<"testing ft::insert with range parameters, new elements to add: 6 7 8:" <<std::endl;
	ft::vector<int> TmpVec;
	TmpVec.push_back(6);
	TmpVec.push_back(7);
	TmpVec.push_back(8);
	ftVec.insert(ftVec.end(), TmpVec.begin(), TmpVec.end());
	for (int i = 0; i < ftVec.size(); i++)
		std::cout <<ftVec.at(i) <<" ";
	std::cout <<std::endl;
	
	std::cout <<std::endl <<"testing ft:erase: " <<std::endl;
	std::cout <<"erasing first element: " <<std::endl;
	ftVec.erase(ftVec.begin());
	for (int i = 0; i < ftVec.size(); i++)
		std::cout <<ftVec.at(i) <<" ";
	std::cout <<std::endl;
	std::cout <<"erasing last element: " <<std::endl;
	ftVec.erase(ftVec.end() - 1);
	for (int i = 0; i < ftVec.size(); i++)
		std::cout <<ftVec.at(i) <<" ";
	std::cout <<std::endl;
	std::cout <<"erasing second element: " <<std::endl;
	ftVec.erase(ftVec.begin() + 1);
	for (int i = 0; i < ftVec.size(); i++)
		std::cout <<ftVec.at(i) <<" ";
	std::cout <<std::endl;
	std::cout <<std::endl <<"erasing a range of elements from index 0 to 3 (not including element 3): " <<std::endl;
	ftVec.erase(ftVec.begin(), ftVec.begin() + 3);
	for (int i = 0; i < ftVec.size(); i++)
		std::cout <<ftVec.at(i) <<" ";
	std::cout <<std::endl;
	std::cout <<std::endl <<"erasing a range of 3 elements at the end: " <<std::endl;
	ftVec.erase(ftVec.end() - 3, ftVec.end());
	for (int i = 0; i < ftVec.size(); i++)
		std::cout <<ftVec.at(i) <<" ";
	std::cout <<std::endl;

	std::cout <<std::endl <<"ft::pop back: " <<std::endl;
	ftVec.pop_back();
	for (int i = 0; i < ftVec.size(); i++)
		std::cout <<ftVec.at(i) <<" ";
	std::cout <<std::endl;
	
	std::cout <<std::endl <<"ft::resize: current size is " <<ftVec.size() <<std::endl;
	std::cout <<"resized to 8 elements: " <<std::endl;
	ftVec.resize(8);
	for (int i = 0; i < ftVec.size(); i++)
		std::cout <<ftVec.at(i) <<" ";
	std::cout <<std::endl;
	std::cout <<"resized to 12 elements: " <<std::endl;
	ftVec.resize(12);
	for (int i = 0; i < ftVec.size(); i++)
		std::cout <<ftVec.at(i) <<" ";
	std::cout <<std::endl;
	
	std::cout <<std::endl <<"testing ft::clear(): " <<std::endl;
	std::cout <<"vector elements: " <<std::endl;
	for (int i = 0; i < ftVec.size(); i++)
		std::cout <<ftVec.at(i) <<" ";
	std::cout <<std::endl <<"size is: " <<ftVec.size() <<", capacity is " <<ftVec.capacity() <<std::endl;
	std::cout <<"vector elements after clearing the vector:" <<std::endl;
	ftVec.clear();
	for (int i = 0; i < ftVec.size(); i++)
		std::cout <<ftVec.at(i) <<" ";
	std::cout <<std::endl <<"size is: " <<ftVec.size() <<", capacity is " <<ftVec.capacity() <<std::endl;
	
	std::vector<int> Vec1;
	Vec1.push_back(5);
	Vec1.push_back(10);
	Vec1.push_back(15);
	Vec1.push_back(20);
	std::cout <<std::endl <<"std::Vec1: ";
	for (int i = 0; i < Vec1.size(); i++)
		std::cout <<Vec1.at(i) <<" ";
	std::vector<int> Vec2;
	Vec2.push_back(1);
	Vec2.push_back(2);
	Vec2.push_back(3);
	Vec2.push_back(4);
	std::cout <<"std::Vec2: ";
	for (int i = 0; i < Vec2.size(); i++)
		std::cout <<Vec2.at(i) <<" ";
	std::cout <<std::endl;
	Vec1.swap(Vec2);
	std::cout <<"Std::swap: " <<std::endl;
	std::cout <<"std::Vec1: ";
	for (int i = 0; i < Vec1.size(); i++)
		std::cout <<Vec1.at(i) <<" ";
	std::cout <<"std::Vec2: ";
	for (int i = 0; i < Vec2.size(); i++)
		std::cout <<Vec2.at(i) <<" ";
	std::cout <<std::endl;

	ft::vector<int> ftVec1;
	ftVec1.push_back(5);
	ftVec1.push_back(10);
	ftVec1.push_back(15);
	ftVec1.push_back(20);
	std::cout <<std::endl <<"ft::Vec1: ";
	for (int i = 0; i < ftVec1.size(); i++)
		std::cout <<ftVec1.at(i) <<" ";
	ft::vector<int> ftVec2;
	ftVec2.push_back(1);
	ftVec2.push_back(2);
	ftVec2.push_back(3);
	ftVec2.push_back(4);
	std::cout <<"ft::Vec2: ";
	for (int i = 0; i < ftVec2.size(); i++)
		std::cout <<ftVec2.at(i) <<" ";
	std::cout <<std::endl;
	ftVec1.swap(ftVec2);
	std::cout <<"ft::swap: " <<std::endl;
	std::cout <<"ft::Vec1: ";
	for (int i = 0; i < ftVec1.size(); i++)
		std::cout <<ftVec1.at(i) <<" ";
	std::cout <<"ft::Vec2: ";
	for (int i = 0; i < ftVec2.size(); i++)
		std::cout <<ftVec2.at(i) <<" ";
	std::cout <<std::endl;

	std::cout <<std::endl <<"comparison std::Vec1 == Vec2: " <<(Vec1 == Vec2) <<std::endl;
	std::cout <<"Vec1 != Vec2 =  " <<(Vec1 != Vec2) <<std::endl;
	std::cout <<"Vec1 < Vec2 = "  <<(Vec1 < Vec2) <<std::endl;
	std::cout <<"Vec1 > Vec2 = " <<(Vec1 > Vec2) <<std::endl;
	std::cout <<"Vec1 >= Vec2 = " <<(Vec1 >= Vec2) <<std::endl;
	std::cout <<"Vec1 <= Vec2 = " <<(Vec1 <= Vec2) <<std::endl <<std::endl;
	
	std::cout <<"ft::Vec1 == ft::Vec2: " <<(ftVec1 == ftVec2) <<std::endl;
	std::cout <<"ftVec1 != ftVec2 =  " <<(ftVec1 != ftVec2) <<std::endl;
	std::cout <<"ftVec1 < ftVec2 = "  <<(ftVec1 < ftVec2) <<std::endl;
	std::cout <<"ftVec1 > ftVec2 = " <<(ftVec1 > ftVec2) <<std::endl;
	std::cout <<"ftVec1 >= ftVec2 = " <<(ftVec1 >= ftVec2) <<std::endl;
	std::cout <<"ftVec1 <= ftVec2 = " <<(ftVec1 <= ftVec2) <<std::endl <<std::endl;

	Vec1 = Vec2;
	ftVec1 = ftVec2;
	std::cout <<std::endl <<"comparison std::Vec1 == Vec2: " <<(Vec1 == Vec2) <<std::endl;
	std::cout <<"Vec1 != Vec2 =  " <<(Vec1 != Vec2) <<std::endl;
	std::cout <<"Vec1 < Vec2 = "  <<(Vec1 < Vec2) <<std::endl;
	std::cout <<"Vec1 > Vec2 = " <<(Vec1 > Vec2) <<std::endl;
	std::cout <<"Vec1 >= Vec2 = " <<(Vec1 >= Vec2) <<std::endl;
	std::cout <<"Vec1 <= Vec2 = " <<(Vec1 <= Vec2) <<std::endl <<std::endl;
	
	std::cout <<"ft::Vec1 == ft::Vec2: " <<(ftVec1 == ftVec2) <<std::endl;
	std::cout <<"ftVec1 != ftVec2 =  " <<(ftVec1 != ftVec2) <<std::endl;
	std::cout <<"ftVec1 < ftVec2 = "  <<(ftVec1 < ftVec2) <<std::endl;
	std::cout <<"ftVec1 > ftVec2 = " <<(ftVec1 > ftVec2) <<std::endl;
	std::cout <<"ftVec1 >= ftVec2 = " <<(ftVec1 >= ftVec2) <<std::endl;
	std::cout <<"ftVec1 <= ftVec2 = " <<(ftVec1 <= ftVec2) <<std::endl <<std::endl;
	
	Vec1.clear();
	ftVec1.clear();
	std::cout <<std::endl <<"comparison std::Vec1 == Vec2: " <<(Vec1 == Vec2) <<std::endl;
	std::cout <<"Vec1 != Vec2 =  " <<(Vec1 != Vec2) <<std::endl;
	std::cout <<"Vec1 < Vec2 = "  <<(Vec1 < Vec2) <<std::endl;
	std::cout <<"Vec1 > Vec2 = " <<(Vec1 > Vec2) <<std::endl;
	std::cout <<"Vec1 >= Vec2 = " <<(Vec1 >= Vec2) <<std::endl;
	std::cout <<"Vec1 <= Vec2 = " <<(Vec1 <= Vec2) <<std::endl <<std::endl;

	std::cout <<"ft::Vec1 == ft::Vec2: " <<(ftVec1 == ftVec2) <<std::endl;
	std::cout <<"ftVec1 != ftVec2 =  " <<(ftVec1 != ftVec2) <<std::endl;
	std::cout <<"ftVec1 < ftVec2 = "  <<(ftVec1 < ftVec2) <<std::endl;
	std::cout <<"ftVec1 > ftVec2 = " <<(ftVec1 > ftVec2) <<std::endl;
	std::cout <<"ftVec1 >= ftVec2 = " <<(ftVec1 >= ftVec2) <<std::endl;
	std::cout <<"ftVec1 <= ftVec2 = " <<(ftVec1 <= ftVec2) <<std::endl <<std::endl;
	
	Vec2.clear();
	ftVec2.clear();
	std::cout <<std::endl <<"comparison std::Vec1 == Vec2: " <<(Vec1 == Vec2) <<std::endl;
	std::cout <<"Vec1 != Vec2 =  " <<(Vec1 != Vec2) <<std::endl;
	std::cout <<"Vec1 < Vec2 = "  <<(Vec1 < Vec2) <<std::endl;
	std::cout <<"Vec1 > Vec2 = " <<(Vec1 > Vec2) <<std::endl;
	std::cout <<"Vec1 >= Vec2 = " <<(Vec1 >= Vec2) <<std::endl;
	std::cout <<"Vec1 <= Vec2 = " <<(Vec1 <= Vec2) <<std::endl <<std::endl;

	std::cout <<"ft::Vec1 == ft::Vec2: " <<(ftVec1 == ftVec2) <<std::endl;
	std::cout <<"ftVec1 != ftVec2 =  " <<(ftVec1 != ftVec2) <<std::endl;
	std::cout <<"ftVec1 < ftVec2 = "  <<(ftVec1 < ftVec2) <<std::endl;
	std::cout <<"ftVec1 > ftVec2 = " <<(ftVec1 > ftVec2) <<std::endl;
	std::cout <<"ftVec1 >= ftVec2 = " <<(ftVec1 >= ftVec2) <<std::endl;
	std::cout <<"ftVec1 <= ftVec2 = " <<(ftVec1 <= ftVec2) <<std::endl <<std::endl;
	
	return 0;
}