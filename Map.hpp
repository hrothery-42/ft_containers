/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:30:48 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/16 12:26:00 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <memory> //std::allocator
# include <limits> //max_size
# include "ReverseIterator.hpp"
//# include "RandomAccessIterator.hpp"
# include "TypeTraits.hpp"
# include "Algorithm.hpp"
# include "RedBlackTree.hpp"
# include "RBTreeIterator.hpp"
# include "Utility.hpp"
# include <functional>

namespace ft{
	
	template<
		class Key, 
		class Val, 
		class Compare = std::less<Key>,
		class Allocator = std::allocator<ft::pair<const Key, Val> >
	> class map
	{
		public:

			typedef Key														key_type;
			typedef Val 													mapped_type;
			typedef ft::pair<const Key, Val>								value_type;
			typedef size_t													size_type;
			typedef ptrdiff_t												difference_type;
			typedef Compare													key_compare;
			typedef Allocator												allocator_type;
			typedef value_type&												reference;
			typedef const value_type&										const_reference;
			typedef typename Allocator::pointer								pointer;
			typedef typename Allocator::const_pointer						const_pointer;
			typedef typename ft::RBTreeIterator<value_type> 				iterator;
			typedef typename ft::RBTreeIterator<const value_type> 			const_iterator;
			typedef typename ft::ReverseIterator<iterator>					reverse_iterator;
			typedef typename ft::ReverseIterator<const_iterator> 			const_reverse_iterator;

		class value_compare : public std::binary_function<value_type, value_type, bool> 
		{
			//the member types are obtained via publicly inheriting std::binary function

			friend class map<Key, Val, Compare, Allocator>; //map can access members of value_compare

			public:

			bool	operator()( const value_type& lhs, const value_type & rhs ) const
			{
				return comp(lhs.first, rhs.first);
			};
			
			protected:
			
			Compare comp;

			value_compare( Compare c ) : comp(c)
			{
				//constructor constructs a new value_compare object
			};
			
		};

		private:
		
			typedef	RedBlackTree<value_type, key_type, key_compare>		tree_type;
		
			allocator_type	_allocator;
			tree_type		_rbtree;
			key_compare		_comp;
			
			

		public:

			/* map()
				: _allocator(Allocator()), _comp(Compare()), _rbtree()
			{
				
			}; */
			
			explicit map( const Compare& comp = key_compare(), const Allocator& alloc = Allocator() )
				: _allocator(alloc),_comp(comp), _rbtree()
			{
				
			};

			template<class InputIt>
			map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator() ) 
				: _allocator(alloc), _comp(comp), _rbtree()
			{
				insert(first, last);
			};

			map( map const& other) : _allocator(other._allocator), _comp(other._comp), _rbtree()
			{
				insert(other.begin(), other.end());
			};

			~map()
			{
				
			};

			map& operator=( map const& rhs)
			{
				if (this == &rhs)
					return *this;
				_allocator = rhs._allocator;
				_comp = rhs._comp;
				clear();
				insert(rhs.begin(), rhs.end());
				return *this;
			};

			allocator_type get_allocator( void ) const
			{
				return _allocator;
			};

			mapped_type&		at(key_type& key)
			{
				value_type* result = _rbtree.findKey(key);
				if (result)
					return (*result).second;
				throw std::out_of_range("map::at");
			};

			mapped_type const&	at(key_type const& key) const
			{
				value_type* result = _rbtree.findKey(key);
				if (result)
					return (*result).second;
				throw std::out_of_range("map::at");
			};

			mapped_type& operator[]( key_type const& key)
			{
				value_type* result = _rbtree.findKey(key);
				if (result)
					return (*result).second;
				else
				{
					_rbtree.insert(value_type(key, mapped_type()));
					result = _rbtree.findKey(key);
					return (*result).second;
				}
			};

			iterator		begin()
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

			void	clear()
			{
				_rbtree.clear();
			};

			ft::pair<iterator, bool>	insert(value_type const& pair)
			{
				return _rbtree.insert(pair);
			};

			iterator	insert(iterator pos, value_type const& pair)
			{
				return _rbtree.insert(pos, pair);
			};

			template<class InputIt>
			void	insert(InputIt first, InputIt last)
			{
				_rbtree.insert(first, last);
			};

			void	erase(iterator pos)
			{
				_rbtree.deleteNode(pos);
			};

			void 	erase(iterator first, iterator last)
			{
				_rbtree.deleteNode(first, last);
			};

			size_type	erase(const key_type& key)
			{
				return _rbtree.deleteNode(key);
			};

			void	swap(map& other)
			{
				_rbtree.swap(other._rbtree);
			};

			size_type	count(key_type const & key) const
			{
				return _rbtree.count(key);
			};

			iterator	find(key_type const& key)
			{
				return _rbtree.find(key);
			};

			const_iterator	find(key_type const& key) const
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

			bool empty() const
			{
				return (begin() == end());
			};

			size_type	size() const
			{
				return _rbtree.size();
			};

			size_type	max_size() const
			{
				return std::min<size_type>(std::numeric_limits<difference_type>::max(), _rbtree.max_size());
				//return std::min<size_type>(std::numeric_limits<difference_type>::max(), _rbtree.max_size());
			};

			key_compare key_comp() const
			{
				return key_compare();
			};

			value_compare value_comp() const
			{
				//returns a function object that compares objects of type std::map::value_type(pair)
				//by using key_comp to compare the first components of the pair
				return value_compare(key_comp());
			};


			/*this one is not in the std::map, but as learners we need it to visualize what is going*/
			void printMap()
			{
				_rbtree.printHorizontalTree(_rbtree.root);
			};
	};

	/**Comparison operators*/
	/* template<class Key, class Val, class Comp, class Alloc>
	bool operator==(const ft::map<Key,Val,Comp,Alloc>& lhs, const ft::map<Key,Val,Comp,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal((lhs.begin()), lhs.end(), rhs.begin());
	}; */

	template<class Key, class Val, class Comp, class Alloc>
	bool operator==(const ft::map<Key,Val,Comp,Alloc>& lhs, const ft::map<Key,Val,Comp,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::pairs_are_equal(lhs.begin(), lhs.end(), rhs.begin());
	};
	
	template<class Key, class Val, class Comp, class Alloc>
	bool operator!=(const ft::map<Key,Val,Comp,Alloc>& lhs, const ft::map<Key,Val,Comp,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return true;
		return (!(pairs_are_equal(lhs.begin(), lhs.end(), rhs.begin())));
	};

	template<class Key, class Val, class Comp, class Alloc>
	bool operator<(const ft::map<Key,Val,Comp,Alloc>& lhs, const ft::map<Key,Val,Comp, Alloc>& rhs)
	{
		return ft::compare_pairs(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};
	
	template<class Key, class Val, class Comp, class Alloc>
	bool operator <=(const ft::map<Key,Val,Comp,Alloc>& lhs, const ft::map<Key,Val,Comp,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	};

	template<class Key, class Val, class Comp, class Alloc>
	bool operator>(const ft::map<Key,Val,Comp,Alloc>& lhs, const ft::map<Key,Val,Comp,Alloc>& rhs)
	{
		//if (lhs == rhs)
		//	return false;
		return (rhs < lhs);

	};

	template<class Key, class Val, class Comp, class Alloc>
	bool operator >=(const ft::map<Key,Val,Comp,Alloc>& lhs, const ft::map<Key,Val,Comp,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	};

	//specializes the std::swap algorithm
	namespace std{
		template< class Key, class T, class Compare, class Alloc>
		void	swap(ft::map<Key,T,Compare,Alloc>& lhs,
					ft::map<Key,T,Compare,Alloc>& rhs)
		{
			lhs.swap(rhs);
		} ;
	} //namespace std
}//namespace ft

#endif