/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tests_std.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:06:33 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/13 15:35:56 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include <utility>
#include <iterator>
#include <iostream>
#include <time.h>

template<class Key, class Val>
void	printMap(std::map<Key, Val> Map)
{
	typedef typename std::map<Key,Val>::iterator mapiterator;
	for (mapiterator it = Map.begin(); it != Map.end(); ++it)
		std::cout <<(*it).first <<" ";
	std::cout <<std::endl;
}

int main(void)
{
	clock_t	tstart = clock();
	/*constructor*/
	std::map<int, char> ftMap;
	std::cout <<"inserting elements in the map:\n";
	ftMap.insert(std::pair<int,char>(3,'a'));
	ftMap.insert(std::pair<int, char>(6, 'b'));
	ftMap.insert(std::pair<int,char>(34,'g'));
	ftMap.insert(std::pair<int, char>(26, 'c'));
	ftMap.insert(ftMap.begin(), std::pair<int,char>(37,'s'));
	ftMap.insert(ftMap.end(), std::pair<int, char>(9, 'e'));
	std::cout <<"keys which already exist will not be added twice, map is printed below:\n";
	ftMap.insert(std::pair<int, char>(6,'d'));

	std::cout <<"\nTESTING COPY CONSTRUCTOR!!! \nprinting first map:\n";
	printMap(ftMap);
	std::cout <<"printing new map after copying:\n";
	std::map<int,char> ftMapOther(ftMap);
	printMap(ftMapOther);

	std::cout <<"TESTING THE RANGE CONSTRUCTOR: making a copy from a range (element 2-4) of the first map\n";
	std::cout <<"iterating through the first map:\n";
	for (std::map<int, char>::iterator it = ftMap.begin(); it != ftMap.end(); ++it)
		std::cout <<(*it).first <<" ";
	std::cout <<std::endl;
	std::map<int,char>::iterator it = ++++ftMap.begin();
	std::map<int,char>::iterator it2 = ++++++++ftMap.begin();
	std::map<int, char> RangeMap(it, it2);
	std::cout <<"printing the 2nd map:\n";
	printMap(RangeMap);
	std::cout <<"\nTESTING THE = OPERATOR:\n";
	RangeMap = ftMap;
	printMap(RangeMap);

	std::cout <<"\nTESTING ELEMENT ACCESS\n";
	std::cout <<"map.at(6) returns the mapped value: " <<RangeMap.at(6) <<std::endl;
	std::cout <<"map.at(out of range) throws an exception\n";
	//std::cout <<"ftMap.at(33) = " <<RangeMap.at(33) <<std::endl;
	std::cout <<"map[34] returns the mapped value: " <<RangeMap[34] <<std::endl;
	std::cout <<"map[out of range] inserts a new element\n";
	std::cout <<"Map[33] = " <<RangeMap[33] <<std::endl;
	printMap(RangeMap);

	std::cout <<"\nTESTING ITERATORS\n";
	std::cout <<"value of iterator to the beginning: " <<(*ftMap.begin()).first <<std::endl;
	std::cout <<"value of iterator to the end (past the final value): " <<(*ftMap.end()).first <<std::endl;
	std::cout <<"value of --map.end() " <<(*--ftMap.end()).first <<std::endl;
	std::cout <<"value of map.rbegin(): " <<(*ftMap.rbegin()).first <<std::endl;
	std::cout <<"value of map.rend(): " <<(*ftMap.rend()).first <<std::endl;
	std::cout <<"value of --map.rend(): "<<(*--ftMap.rend()).first <<std::endl;
	
	std::cout <<"\nTESTING ERASE, erasing smallest element:\n";
	RangeMap.erase(RangeMap.begin());
	printMap(RangeMap);
	std::cout <<"erasing biggest element\n";
	RangeMap.erase(--RangeMap.end());
	printMap(RangeMap);
	std::cout <<"erasing non existent key\n";
	RangeMap.erase(10);
	printMap(RangeMap);
	std::cout <<"erasing a range of iterators at once:\n";
	std::map<int, char>::iterator iter(++RangeMap.begin());
	std::map<int,char>::iterator iter2(++++++RangeMap.begin());
	std::cout <<"range of iterators to erase: from " <<(*iter).first <<" to (not including) " <<(*iter2).first <<std::endl;
	RangeMap.erase(iter, iter2);
	printMap(RangeMap);
	std::cout <<"erasing all elements: map is empty\n";
	RangeMap.erase(33);
	RangeMap.erase(34);
	RangeMap.erase(6);

	std::cout <<"\nTESTING SWAP:\n";
	std::cout <<"printing RangeMap: (map is empty)\n";
	printMap(RangeMap);
	std::cout <<"printing ftMap:\n ";
	printMap(ftMap);
	std::cout <<"swapping maps...\n";
	ftMap.swap(RangeMap);
	std::cout <<"printing RangeMap: \n";
	printMap(RangeMap);
	std::cout <<"printing ftMap: (is now empty)\n ";
	printMap(ftMap);

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
	printMap(ftMap);
	std::cout <<"printing RangeMap\n";
	printMap(RangeMap);
	std::cout <<"printing ftMapOther\n";
	printMap(ftMapOther);
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
	RangeMap.insert(std::pair<int,char>(2, 'b'));
	std::cout <<"(ftMapOther == RangeMap) " <<(ftMapOther == RangeMap) <<std::endl;
	std::cout <<"(ftMapOther <= RangeMap) " <<(ftMapOther <= RangeMap) <<std::endl;
	std::cout <<"(ftMapOther > RangeMap) "  <<(ftMapOther > RangeMap) <<std::endl;

	std::cout <<"\nTESTING RANGE CONSTRUCTOR\n";
	printMap(RangeMap);
	std::map<int, char> rangeConstructedMap(RangeMap.begin(), RangeMap.end());
	printMap(rangeConstructedMap);

	std::cout <<"\nTESTING OTHER DATA TYPES. map<char, char>\n";
	std::map<char, char> charMap;
	charMap.insert(std::pair<char,char>('a', 'a'));
	charMap.insert(std::pair<char,char>('b', 'a'));
	charMap.insert(std::pair<char,char>('c', 'a'));
	charMap.insert(std::pair<char,char>('d', 'a'));
	charMap.insert(std::pair<char,char>('e', 'a'));

	printMap(charMap);
	
	std::cout <<"\nMAX_SIZE\n";
	std::map<int, char> newMap;
	std::cout <<"std::map<float, char> max_size " <<newMap.max_size() <<std::endl;
	std::cout <<"Time taken: " <<(double)(clock() - tstart)/CLOCKS_PER_SEC <<std::endl;	return 0;
	std::cout <<"Time taken: " <<(double)(clock() - tstart)/CLOCKS_PER_SEC <<std::endl;
	return 0;
}