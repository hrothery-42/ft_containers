/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TypeTraits.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 09:58:10 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/19 14:51:35 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPETRAITS_HPP
# define TYPETRAITS_HPP
# include <stdint.h>
namespace ft{
	
	/**********************************************
	*************enable_if ************************
	***********************************************/
	
	template <bool, class T = void >
	struct enable_if {};

	template <typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};


	/**************************************
	****************is_integral:************
	***************************************/
	/*is used to check whether the given variable is integral*/
	template <typename T, T val>
	struct integral_constant 
	{
		static const T value = val;
		typedef T value_type;
		typedef integral_constant<T, val> type;
		operator T() { return value; }
	};

	typedef integral_constant<bool, true>  true_type;
	typedef integral_constant<bool, false> false_type;

	template <typename T> struct is_integral : public false_type {};

	template <> struct is_integral<bool> : public true_type {};
	template <> struct is_integral<char> : public true_type {};
	template <> struct is_integral<unsigned char> : public true_type {};
	template <> struct is_integral<signed char> : public true_type {};
	template <> struct is_integral<char16_t> : public true_type {};
	template <> struct is_integral<char32_t> : public true_type {};
	template <> struct is_integral<wchar_t> : public true_type {};
	template <> struct is_integral<short> : public true_type {};
	template <> struct is_integral<unsigned short> : public true_type {};
	template <> struct is_integral<long> : public true_type {};
	template <> struct is_integral<unsigned long> : public true_type {};
	template <> struct is_integral<long long> : public true_type {};
	template <> struct is_integral<unsigned long long> : public true_type {};
	template <> struct is_integral<int> : public true_type {};
	template <> struct is_integral<unsigned int> : public true_type {};
	template <typename T> struct is_integral<const T> : is_integral<T> {};
	template <typename T> struct is_integral<volatile T> : is_integral<T> {};
	template <typename T> struct is_integral<const volatile T> : is_integral<T> {};
}

#endif