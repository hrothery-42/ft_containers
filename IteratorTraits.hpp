/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IteratorTraits.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:05:01 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/14 11:43:43 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORTRAITS_HPP 
# define ITERATORTRAITS_HPP
# include <cstddef>

namespace ft {
	/***Iterator categories***/
	struct	input_iterator_tag {};
	struct	output_iterator_tag {};
	struct	forward_iterator_tag {};
	struct	bidirectional_iterator_tag {};
	struct	random_access_iterator_tag {};
	
	template <class Iter>
	struct iterator_traits {
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::iterator_category	iterator_category;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference 			reference;
	};

	/***partial specialization for pointer types***/
	template <class T>
	struct iterator_traits<T*>
	{
		typedef T 								value_type;
		typedef ptrdiff_t						difference_type;
		typedef ft::random_access_iterator_tag	iterator_category;
		typedef T*								pointer;
		typedef T&								reference;
	};

	/***partial specialization for const pointer types***/
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef T 								value_type;
		typedef ptrdiff_t						difference_type;
		typedef ft::random_access_iterator_tag	iterator_category;
		typedef const T*						pointer;
		typedef const T&						reference;
	};

}

#endif