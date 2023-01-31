/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_tests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:34:05 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/16 14:21:16 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stack>
#include <vector>
#include "../Stack.hpp"
#include "../Vector.hpp"

int main(void)
{
	ft::stack<int> s;
	//ft::stack<int, std::vector<int> > s;
	std::stack<int, std::vector<int> > ss;
	std::cout <<ss.empty() <<" " <<s.empty() <<std::endl;
	std::cout <<ss.size() <<" " <<s.size() <<std::endl;
	s.push(5);
	ss.push(5);
	std::cout <<s.top() <<" " <<ss.top() <<std::endl;
	std::cout <<ss.empty() <<" " <<s.empty() <<std::endl;
	std::cout <<ss.size() <<" " <<s.size() <<std::endl;
	s.push(8);
	ss.push(8);
	std::cout <<s.top() <<" " <<ss.top() <<std::endl;
	std::cout <<ss.empty() <<" " <<s.empty() <<std::endl;
	std::cout <<ss.size() <<" " <<s.size() <<std::endl;
	s.pop();
	ss.pop();
	std::cout <<ss.empty() <<" " <<s.empty() <<std::endl;
	std::cout <<ss.size() <<" " <<s.size() <<std::endl;
	return 0;
	
}