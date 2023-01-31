/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:06:33 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/13 15:32:57 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../Map.hpp"
#include <time.h>

int main(void)
{
	clock_t	tstart = clock();
	/*constructor*/
	ft::map<int, char> ftMap;
	std::cout <<"inserting elements in the map:\n";
	ftMap.insert(ft::pair<int,char>(3,'a'));
	ftMap.insert(ft::pair<int, char>(6, 'b'));
	ftMap.insert(ft::pair<int,char>(34,'g'));
	ftMap.insert(ft::pair<int, char>(26, 'c'));
	ftMap.insert(ftMap.begin(), ft::pair<int,char>(37,'s'));
	ftMap.insert(ftMap.end(), ft::pair<int, char>(9, 'e'));
	std::cout <<"keys which already exist will not be added twice, map is printed below:\n";
	ftMap.insert(ft::pair<int, char>(6,'d'));

	std::cout <<"\nTESTING COPY CONSTRUCTOR!!! \nprinting first map:\n";
	ftMap.printMap();
	std::cout <<"printing new map after copying:\n";
	ft::map<int,char> ftMapOther(ftMap);
	ftMapOther.printMap();

	std::cout <<"TESTING THE RANGE CONSTRUCTOR: making a copy from a range (element 2-4) of the first map\n";
	std::cout <<"iterating through the first map:\n";
	for (ft::map<int, char>::iterator it = ftMap.begin(); it != ftMap.end(); ++it)
		std::cout <<(*it).first <<" ";
	std::cout <<std::endl;
	ft::map<int,char>::iterator it = ++++ftMap.begin();
	ft::map<int,char>::iterator it2 = ++++++++ftMap.begin();
	ft::map<int, char> RangeMap(it, it2);
	std::cout <<"printing the 2nd map:\n";
	RangeMap.printMap();
	std::cout <<"\nTESTING THE = OPERATOR:\n";
	RangeMap = ftMap;
	RangeMap.printMap();

	std::cout <<"\nTESTING ELEMENT ACCESS\n";
	std::cout <<"map.at(6) returns the mapped value: " <<RangeMap.at(6) <<std::endl;
	std::cout <<"map.at(out of range) throws an exception\n";
	//std::cout <<"ftMap.at(33) = " <<RangeMap.at(33) <<std::endl;
	std::cout <<"map[34] returns the mapped value: " <<RangeMap[34] <<std::endl;
	std::cout <<"map[out of range] inserts a new element\n";
	std::cout <<"Map[33] = " <<RangeMap[33] <<std::endl;
	RangeMap.printMap();

	std::cout <<"\nTESTING ITERATORS\n";
	std::cout <<"value of iterator to the beginning: " <<(*ftMap.begin()).first <<std::endl;
	std::cout <<"value of iterator to the end (past the final value): " <<(*ftMap.end()).first <<std::endl;
	std::cout <<"value of --map.end() " <<(*--ftMap.end()).first <<std::endl;
	std::cout <<"value of map.rbegin(): " <<(*ftMap.rbegin()).first <<std::endl;
	std::cout <<"value of map.rend(): " <<(*ftMap.rend()).first <<std::endl;
	std::cout <<"value of --map.rend(): "<<(*--ftMap.rend()).first <<std::endl;

	std::cout <<"\nTESTING ERASE, erasing smallest element:\n";
	RangeMap.erase(RangeMap.begin());
	RangeMap.printMap();
	std::cout <<"erasing biggest element\n";
	RangeMap.erase(--RangeMap.end());
	RangeMap.printMap();
	std::cout <<"erasing non existent key\n";
	RangeMap.erase(10);
	RangeMap.printMap();
	std::cout <<"erasing a range of iterators at once:\n";
	ft::map<int, char>::iterator iter(++RangeMap.begin());
	ft::map<int,char>::iterator iter2(++++++RangeMap.begin());
	std::cout <<"range of iterators to erase: from " <<(*iter).first <<" to (not including) " <<(*iter2).first <<std::endl;
	RangeMap.erase(iter, iter2);
	RangeMap.printMap();
	std::cout <<"erasing all elements: map is empty\n";
	RangeMap.erase(33);
	RangeMap.erase(34);
	RangeMap.erase(6);
	RangeMap.printMap();
	
	std::cout <<"\nTESTING SWAP:\n";
	std::cout <<"printing RangeMap: (map is empty)\n";
	RangeMap.printMap();
	std::cout <<"printing ftMap:\n ";
	ftMap.printMap();
	std::cout <<"swapping maps...\n";
	ftMap.swap(RangeMap);
	std::cout <<"printing RangeMap: \n";
	RangeMap.printMap();
	std::cout <<"printing ftMap: (is now empty)\n ";
	ftMap.printMap();

	std::cout <<"\nTESTING COUNT\n";
	std::cout <<"count returns the number of elements matching the key\n";
	std::cout <<"count(10) " <<RangeMap.count(10) <<", count(26) " <<RangeMap.count(26) <<std::endl;
	
	std::cout <<"\nTESTING FIND, EQUAL RANGE\n";
	std::cout <<"find returns an iterator to the element with the given key, on failure returns end()\n";
	std::cout <<"find 26: " <<(*RangeMap.find(26)).first <<", find 10: " <<(*RangeMap.find(10)).first <<std::endl;
	std::cout <<"equal range takes a key and returns a pair of iterators: first one to the first element that is not less\n";
	std::cout <<"than the given key, second one that is the first one greater than the given key\n";
	std::cout <<"upper_bound(26) " <<(*RangeMap.upper_bound(26)).first <<std::endl;
	std::cout <<"upper_bound(25) " <<(*RangeMap.upper_bound(25)).first <<std::endl;
	std::cout <<"upper_bound(27) " <<(*RangeMap.upper_bound(27)).first <<std::endl;
	std::cout <<"upper_bound(40) " <<(*RangeMap.upper_bound(40)).first <<std::endl;
	std::cout <<"lower_bound(26) " <<(*RangeMap.lower_bound(26)).first <<std::endl;
	std::cout <<"lower_bound(25) " <<(*RangeMap.lower_bound(25)).first <<std::endl;
	std::cout <<"lower_bound(27) " <<(*RangeMap.lower_bound(27)).first <<std::endl;
	std::cout <<"lower_bound(40) " <<(*RangeMap.lower_bound(40)).first <<std::endl;
	std::cout <<"equal_range(10) : first iterator(lower_bound) " <<(*(RangeMap.equal_range(10)).first).first <<", second iterator(upper_bound) " <<(*(RangeMap.equal_range(10)).second).first <<std::endl;
	std::cout <<"equal_range(6) : first iterator(lower_bound) " <<(*(RangeMap.equal_range(6)).first).first <<", second iterator(upper_bound) " <<(*(RangeMap.equal_range(6)).second).first <<std::endl;

	std::cout <<"\nTESTING NON MEMBER COMPARISON FUNCTIONS\n";
	std::cout <<std::boolalpha;
	std::cout <<"printing ftMap\n";
	ftMap.printMap();
	std::cout <<"printing RangeMap\n";
	RangeMap.printMap();
	std::cout <<"printing ftMapOther\n";
	ftMapOther.printMap();
	std::cout <<"(ftMap == RangeMap) " <<(ftMap == RangeMap) <<std::endl;
	std::cout <<"(ftMap != RangeMap) " <<(ftMap != RangeMap) <<std::endl;
	std::cout <<"(ftMap >= ftMapOther) " <<(ftMap >= ftMapOther) <<std::endl;
	std::cout <<"(ftMap < ftMapOther) " <<(ftMap < ftMapOther) <<std::endl;
	std::cout <<"(ftMapOther == RangeMap) " <<(ftMapOther == RangeMap) <<std::endl;
	std::cout <<"(ftMapOther <= RangeMap) " <<(ftMapOther <= RangeMap) <<std::endl;
	std::cout <<"(ftMapOther > RangeMap) "  <<(ftMapOther > RangeMap) <<std::endl;
	std::cout <<"deleting an element in RangeMap and retesting\n";
	RangeMap.erase(RangeMap.begin());
	std::cout <<"(ftMapOther == RangeMap) " <<(ftMapOther == RangeMap) <<std::endl;
	std::cout <<"(ftMapOther <= RangeMap) " <<(ftMapOther <= RangeMap) <<std::endl;
	std::cout <<"(ftMapOther > RangeMap) "  <<(ftMapOther > RangeMap) <<std::endl;
	std::cout <<"inserting a new element in RangeMap different than before\n";
	RangeMap.insert(ft::pair<int,char>(2, 'b'));
	std::cout <<"(ftMapOther == RangeMap) " <<(ftMapOther == RangeMap) <<std::endl;
	std::cout <<"(ftMapOther <= RangeMap) " <<(ftMapOther <= RangeMap) <<std::endl;
	std::cout <<"(ftMapOther > RangeMap) "  <<(ftMapOther > RangeMap) <<std::endl;

	std::cout <<"\nTESTING RANGE CONSTRUCTOR\n";
	RangeMap.printMap();
	ft::map<int, char> rangeConstructedMap(RangeMap.begin(), RangeMap.end());
	rangeConstructedMap.printMap();

	std::cout <<"\nTESTING OTHER DATA TYPES. map<char, char>\n";
	ft::map<char, char> charMap;
	charMap.insert(ft::pair<char,char>('a', 'a'));
	charMap.insert(ft::pair<char,char>('b', 'a'));
	charMap.insert(ft::pair<char,char>('c', 'a'));
	charMap.insert(ft::pair<char,char>('d', 'a'));
	charMap.insert(ft::pair<char,char>('e', 'a'));

	charMap.printMap();

	std::cout <<"\nMAX_SIZE\n";
	ft::map<int, char> newMap;
	std::cout <<"ft::map<float, char> max_size " <<newMap.max_size() <<std::endl;
	std::cout <<"Time taken: " <<(double)(clock() - tstart)/CLOCKS_PER_SEC <<std::endl;
	return 0;
}