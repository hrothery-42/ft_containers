/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocator_test.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:22:25 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/16 12:34:02 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include <iostream>
#include "../Map.hpp"
#include <utility>
#include <string>

int main()
{
	ft::map<int, int, std::less<int>, std::allocator<ft::pair<const int, int> > > mp;
	for (int i = 0, j = 10; i < 10; ++i, ++j) {
        mp.insert(ft::make_pair(i, j));
    }
	mp.printMap();
}
