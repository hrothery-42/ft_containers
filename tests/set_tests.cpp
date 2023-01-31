/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_tests.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 09:21:22 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/09 13:21:22 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Set.hpp"
#include <set>
#include <iostream>

int main()
{
	ft::set<int> s;
	std::set<int> f;
	std::cout <<std::boolalpha;
	std::cout <<"set is empty: " <<s.empty() <<std::endl;
	s.insert(5);
	s.insert(15);
	s.insert(25);
	s.insert(100);
	std::cout <<"size of set is " <<s.size() <<std::endl;
	s.insert(s.end(), 99);
	s.printTree();
	ft::set<int>::iterator its(s.find(5));
	s.erase(its);
	s.printTree();
	s.erase(100);
	s.printTree();
	s.erase(s.begin());
	s.erase(s.begin(), s.end());
	for (ft::set<int>::iterator it = s.begin(); it != s.end(); ++it)
		std::cout <<*it <<" ";
	std::cout <<std::endl;
	std::cout <<s.max_size() <<std::endl;
	std::cout <<f.max_size() <<std::endl;
	return 0;
}