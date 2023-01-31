/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReverseIterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:06:18 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/16 11:17:17 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSEITERATOR 
# define REVERSEITERATOR
# include "RandomAccessIterator.hpp"
# include <cstddef>
# include "IteratorTraits.hpp"

namespace ft
{
	template <typename Iterator>
	class ReverseIterator
	{
		public:
		
		typedef Iterator 								iterator_type;
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer 				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::value_type			value_type;

		protected:
			iterator_type current;

		public:
		
		ReverseIterator() :current(iterator_type()) {};
		explicit ReverseIterator( iterator_type const rhs ) : current(rhs) {};
		ReverseIterator( ReverseIterator<iterator_type> const& src) : current(src.base()) {};
		ReverseIterator& operator=( ReverseIterator<iterator_type> const& rhs ) {
			if (this == &rhs)
				return *this;
			current = rhs.base();
			return *this;
		}
		~ReverseIterator() {};

		iterator_type	base() const 
		{ 
			return current;
		};

		/*increment and decrement operators*/
		ReverseIterator & operator++() { --current; return *this; };
		ReverseIterator operator++(int) { ReverseIterator<iterator_type> tmp(*this); --current; return tmp; }
		ReverseIterator & operator--() { ++current; return *this; };
		ReverseIterator operator--(int) { ReverseIterator<iterator_type> tmp(*this); ++current; return tmp; };
		
		/*arithmetic operators*/
		ReverseIterator operator+(difference_type  n) const { return ReverseIterator(current - n); };
		ReverseIterator operator-(difference_type  n) const { return ReverseIterator(current + n); };
		ReverseIterator operator+=(difference_type  n)  { current -= n; return (*this); };
		ReverseIterator operator-=(difference_type  n)  { current += n; return (*this); };
		
		/*reference and dereference*/
		reference	operator*() const {  iterator_type tmp = current; return *(--tmp); };
		pointer		operator->() const { return &operator*(); };

		/*offset dereference operator*/
		reference	operator[](difference_type n) const { return *(*this + n); };
	};

		/*****************************************/
		/***********NON-MEMBER FUNCTIONS**********/
		/*****************************************/

		
	template <typename IterLhs, typename IterRhs>
	bool operator==(ft::ReverseIterator<IterLhs> const& lhs, ft::ReverseIterator<IterRhs> const& rhs) {
		return lhs.base() == rhs.base();
	};
	
	template <typename IterLhs, typename IterRhs>
	bool operator!=(ft::ReverseIterator<IterLhs> const& lhs, ft::ReverseIterator<IterRhs> const& rhs) {
		return lhs.base() != rhs.base();
	};

	template <typename IterLhs, typename IterRhs>
	bool operator >(ft::ReverseIterator<IterLhs> const& lhs, ft::ReverseIterator<IterRhs> const& rhs) {
		return lhs.base() < rhs.base();
	};

	template <typename IterLhs, typename IterRhs>
	bool operator >=(ft::ReverseIterator<IterLhs> const& lhs, ft::ReverseIterator<IterRhs> const& rhs) {
		return lhs.base() <= rhs.base();
	};

	template <typename IterLhs, typename IterRhs>
	bool operator <(ft::ReverseIterator<IterLhs> const& lhs, ft::ReverseIterator<IterRhs> const& rhs) {
		return lhs.base() > rhs.base();
	};

	template <typename IterLhs, typename IterRhs>
	bool operator <=(ft::ReverseIterator<IterLhs> const& lhs, ft::ReverseIterator<IterRhs> const& rhs) {
		return lhs.base() >= rhs.base();
	};

	template <typename Iter>
	ReverseIterator<Iter> operator+(typename ft::ReverseIterator<Iter>::difference_type const n, ft::ReverseIterator<Iter> const& rhs) {
		return (ft::ReverseIterator<Iter>(rhs.base() - n));
	};

	template <typename IterLhs, typename IterRhs>
	typename ft::ReverseIterator<IterLhs>::difference_type operator-(ft::ReverseIterator<IterLhs> const& lhs, ft::ReverseIterator<IterRhs> const& rhs) {
		return (rhs.base() - lhs.base());
	};
}

#endif
