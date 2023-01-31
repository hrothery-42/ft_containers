/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomAccessIterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 09:16:31 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/16 14:11:42 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOMACCESSITERATOR_HPP
# define RANDOMACCESSITERATOR_HPP
# include "IteratorTraits.hpp"
# include <iostream>
# include <cstddef> //ptrdiff_t
# include "ExtractKey.hpp"

namespace ft{
	
	template <typename T>
	class RandomAccessIterator
	{
		public:
		
		typedef typename ft::iterator_traits<T*>::value_type		value_type;
		typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
		typedef typename ft::iterator_traits<T*>::pointer			pointer;
		typedef typename ft::iterator_traits<T*>::reference			reference;
		typedef typename ft::random_access_iterator_tag				iterator_category;
		typedef T*													iterator_type;

		protected:

			pointer _i;

		public:

			RandomAccessIterator() : _i() {};
			
			RandomAccessIterator(pointer p) : _i(p) {};
			
			template <typename type_T>
			RandomAccessIterator(RandomAccessIterator< type_T> const& src) :
				_i(isConstant(src.base())) {};

			RandomAccessIterator & operator=(RandomAccessIterator<T> const& rhs)
			{
				_i = rhs.base();
				return *this;
			};

			~RandomAccessIterator() {};
			
			pointer base() const { return _i; };
			
			/**increment and decrement**/
			RandomAccessIterator & operator++() { ++_i; return *this; };
			RandomAccessIterator operator++(int) { RandomAccessIterator<value_type> tmp(*this); ++(*this); return tmp; };
			RandomAccessIterator& operator--() { --_i; return *this; };
			RandomAccessIterator operator--(int) { RandomAccessIterator<value_type> tmp(*this); --(*this); return tmp; }
			
			/**reference and dereference**/
			reference operator*() const { return *_i; };
			pointer operator->() const { return _i; };
			
			/**arithmetic operators**/
			RandomAccessIterator operator+(difference_type const& n) const {return (_i + n); }; 
			RandomAccessIterator operator-(difference_type const& n) const { return (_i - n); };
			RandomAccessIterator operator+=(difference_type const& n) { _i += n; return *this; };
			RandomAccessIterator operator-=(difference_type const& n) { _i -= n; return *this; };

			/**offset dereference operator**/
			reference operator[](difference_type n) const { return *(_i + n); };
	};

	/**equality and inequality comparison(allowing comparison between two different types**/
	template <typename IterLhs, typename IterRhs>
	bool operator==(RandomAccessIterator<IterLhs> const& lhs, RandomAccessIterator<IterRhs> const& rhs ) {
		return lhs.base() == rhs.base();
	};

	template <typename IterLhs, typename IterRhs>
	bool operator!=(RandomAccessIterator<IterLhs> const& lhs, RandomAccessIterator<IterRhs> const& rhs ) {
		return lhs.base() != rhs.base();
	};

	/*relational operators*/
	template <typename IterLhs, typename IterRhs>
	bool operator<( RandomAccessIterator<IterLhs> const & lhs, RandomAccessIterator<IterRhs> const & rhs ) {
		return lhs.base() < rhs.base();
	};

	template <typename IterLhs, typename IterRhs>
	bool operator>( RandomAccessIterator<IterLhs> const & lhs, RandomAccessIterator<IterRhs> const & rhs ) {
		return lhs.base() > rhs.base();
	};

	template <typename IterLhs, typename IterRhs>
	bool operator<=( RandomAccessIterator<IterLhs> const& lhs, RandomAccessIterator<IterRhs> const & rhs ) {
		return lhs.base() <= rhs.base();
	};

	template <typename IterLhs, typename IterRhs>
	bool operator>=( RandomAccessIterator<IterLhs> const& lhs, RandomAccessIterator<IterRhs> const& rhs ) {
		return lhs.base() >= rhs.base();
	};

	template <class Iter>
	typename RandomAccessIterator<Iter>::difference_type operator-(RandomAccessIterator<Iter> const& lhs, RandomAccessIterator<Iter> const& rhs) {
		return lhs.base() - rhs.base();
	};

	template <class Iter>
	RandomAccessIterator<Iter> operator+(typename RandomAccessIterator<Iter>::difference_type const n, RandomAccessIterator<Iter> const& rhs) {
		return (RandomAccessIterator<Iter>(rhs.base() + n));
	};

	

}

#endif