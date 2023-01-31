/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utility.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 09:29:18 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/16 12:13:28 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITY_HPP
# define UTILITY_HPP
# include "Algorithm.hpp"
# include "TypeTraits.hpp"
namespace ft{

	template< class T1, class T2>
	struct pair {
		typedef T1 first_type;
		typedef	T2 second_type;
		
		first_type	first;
		second_type	second;

		pair() : first(T1()), second(T2()) {};
		pair(first_type const & argFirst, second_type const & argSecond) : first(argFirst), second(argSecond) {};
		pair( pair const& src ) : first(src.first), second(src.second) {};
		~pair() {};

		template <class U, class V>
		pair(const pair<U, V>& other) : first(other.first), second(other.second) {};
		
		pair& operator=( pair const& rhs ) {
			if (this == &rhs)
				return *this;
			first = rhs.first;
			second = rhs.second;
			return *this;
		};
	};

	template<class T1, class T2>
	pair<T1, T2> make_pair(T1 argFirst, T2 argSecond ) {
		pair<T1, T2> newpair(argFirst, argSecond);
		return newpair;
	};

	template<class T1, class T2>
	bool operator==(T1 lhs, T2 rhs) 
	{ 
		return (lhs.first == rhs.first) && (lhs.second == rhs.second);
	};

	template<class T1, class T2>
	bool operator!=(T1 lhs, T2 rhs)
	{
		return !(lhs == rhs);
	};

	template<class T1, class T2>
	bool operator<=(T1 lhs, T2 rhs)
	{
		return ((lhs.first <= rhs.first) && (lhs.second <= rhs.second));
	};

	template<class T1, class T2>
	bool operator>=(T1 lhs, T2 rhs)
	{
		return ((lhs.first >= rhs.first) && (lhs.second >= rhs.second));
	};

	template<class T1, class T2>
	bool operator<(T1 lhs, T2 rhs)
	{
		return ((lhs.first < rhs.first) && (lhs.second < rhs.second));
	};

	template<class T1, class T2>
	bool operator>(T1 lhs, T2 rhs)
	{
		return ((lhs.first > rhs.first) && (lhs.second > rhs.second));
	};
	
}
#endif