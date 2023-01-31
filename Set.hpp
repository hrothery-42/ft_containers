/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:48:50 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/16 14:20:17 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP
# include <memory>
# include <limits>
# include "ReverseIterator.hpp"
# include "TypeTraits.hpp"
# include "Algorithm.hpp"
# include "RedBlackTree.hpp"
# include "Utility.hpp"
# include <functional>

namespace ft {
	
	template <
		class Key,
		class Compare = std::less<Key>,
		class Allocator = std::allocator<Key>
	> class set 
	{
		public:
		
		typedef Key									key_type;
		typedef Key									value_type;
		typedef	std::size_t							size_type;
		typedef std::ptrdiff_t						difference_type;
		typedef Compare								key_compare;
		typedef Compare								value_compare;
		typedef Allocator							allocator_type;
		typedef value_type&							reference;
		typedef const value_type&					const_reference;
		typedef typename Allocator::pointer			pointer;
		typedef typename Allocator::const_pointer	const_pointer;
		typedef typename ft::RBTreeIterator<value_type>		iterator;
		typedef	typename ft::RBTreeIterator<value_type>	const_iterator;
		typedef	typename ft::ReverseIterator<iterator>		reverse_iterator;
		typedef	typename ft::ReverseIterator<const_iterator>	const_reverse_iterator;
		
		private:

		RedBlackTree<value_type, key_type, key_compare> 	_rbtree;
		allocator_type										_allocator;
		key_compare											_comp;

		public:

		set()
			: _allocator(Allocator()), _comp(Compare()), _rbtree()
		{
			
		};

		explicit set( const Compare& comp, const Allocator& alloc = Allocator() )
			: _allocator(alloc), _comp(comp), _rbtree()
		{
			
		};

		template< class InputIt >
		set (InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() )
			: _allocator(alloc), _comp(comp), _rbtree()
		{
			insert(first, last);
		};

		set( const set& other)
			: _allocator(other._allocator), _comp(other._comp), _rbtree()
		{
			insert(other.begin(), other.end());
		};

		allocator_type	get_allocator() const
		{
			return _allocator;
		};

		iterator	begin()
		{
			return _rbtree.begin();
		};

		const_iterator	begin() const
		{
			return _rbtree.begin();
		};

		iterator	end()
		{
			return _rbtree.end();
		};

		const_iterator	end() const
		{
			return _rbtree.end();
		};
		
		reverse_iterator rbegin()
		{
			return _rbtree.rbegin();
		};

		const_reverse_iterator rbegin() const
		{
			return _rbtree.rbegin();
		};

		reverse_iterator rend()
		{
			return _rbtree.rend();
		};
		
		const_reverse_iterator rend() const
		{
			return _rbtree.rend();
		};

		bool	empty() const
		{
			return (begin() == end());
		};

		size_type	size() const
		{
			return _rbtree.size();
		};

		size_type	max_size() const
		{
			return _rbtree.max_size();
		};

		void	clear()
		{
			_rbtree.clear();
		};

		ft::pair<iterator, bool>	insert( const value_type& value )
		{
			return _rbtree.insert(value);
		};

		iterator	insert( iterator pos, const value_type& value )
		{
			return _rbtree.insert(pos, value);
		};

		template< class InputIt >
		void	insert( InputIt first, InputIt last )
		{
			_rbtree.insert(first, last);
		};

		void	erase( iterator pos )
		{
			_rbtree.deleteNode(pos);
		};

		void	erase(iterator first, iterator last )
		{
			_rbtree.deleteNode(first, last);
		};

		size_type	erase( const Key& key )
		{
			return _rbtree.deleteNode(key);
		};

		void	swap(set& other)
		{
			_rbtree.swap(other._rbtree);
		};

		size_type	count( const Key& key )
		{
			return _rbtree.count(key);
		};

		iterator	find( const Key& key )
		{
			return _rbtree.find(key);
		};

		const_iterator	find( const Key& key ) const
		{
			return _rbtree.find(key);
		};

		iterator	lower_bound(key_type const& key) 
		{
			return _rbtree.lower_bound(key);
		};

		const_iterator	lower_bound(key_type const& key) const
		{
			return _rbtree.lower_bound(key);
		};

		iterator	upper_bound(key_type const& key)
		{
			return _rbtree.upper_bound(key);
		};

		const_iterator	upper_bound(key_type const& key) const
		{
			return _rbtree.upper_bound(key);
		};

		ft::pair<iterator, iterator> equal_range(const key_type & key)
		{
			return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
		};

		ft::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
		{
			return ft::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
		};

		key_compare	key_comp() const
		{
			return key_compare();
		};

		value_compare value_comp() const
		{
			return value_compare(key_comp());
		};

		void printTree()
		{
			_rbtree.printHorizontalTree(_rbtree.root);
		};

	};
}

#endif