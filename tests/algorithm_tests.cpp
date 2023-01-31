/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm_tests.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:17:26 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/13 11:10:27 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <algorithm>
#include <iostream>
#include "../Algorithm.hpp"
#include "../Utility.hpp"
#include "../Map.hpp"
#include <vector>
#include <map>

using namespace std;

/*converts chars to lower case which affects their lexicographical value*/
bool comp(char s1, char s2) {return tolower(s1)<tolower(s2);};

bool is_equal_squared(int val1, int val2) {
	bool result = val1 == (val2 * val2);
	return (result); };

int main(void)
{
	vector<char> myVec;
	myVec.push_back('D');
	myVec.push_back('B');
	myVec.push_back('C');
	myVec.push_back('D');
	vector<char> myVec2;
	myVec2.push_back('a');
	myVec2.push_back('b');
	myVec2.push_back('c');
	myVec2.push_back('d');
	std::cout <<lexicographical_compare(myVec.begin(), myVec.end(), myVec2.begin(), myVec2.end(), comp) <<std::endl;
	std::cout <<ft::lexicographical_compare(myVec.begin(), myVec.end(), myVec2.begin(), myVec2.end(), comp) <<std::endl;

	vector<int> myVecInt;
	vector<int> myVecInt2;
	myVecInt.push_back(1);
	myVecInt.push_back(4);
	myVecInt.push_back(9);
	myVecInt2.push_back(1);
	myVecInt2.push_back(2);
	myVecInt2.push_back(3);
	std::cout <<std::endl <<"std::equal: " <<std::endl;
	std::cout <<"myVecInt is equal to myVecInt2 = " <<std::equal(myVecInt.begin(), myVecInt.end(), myVecInt2.begin()) <<std::endl;
	std::cout <<"myVecInt == myVecInt2 squared = " <<std::equal(myVecInt.begin(), myVecInt.end(), myVecInt2.begin(), is_equal_squared) <<std::endl;
	std::cout <<"testing ft::equal: " <<std::endl;
	std::cout <<"myVecInt is equal to myVecInt2 = " <<ft::equal(myVecInt.begin(), myVecInt.end(), myVecInt2.begin()) <<std::endl;
	std::cout <<"myVecInt == myVecInt2 squared = " <<ft::equal(myVecInt.begin(), myVecInt.end(), myVecInt2.begin(), is_equal_squared) <<std::endl;
	
	return 0;
}