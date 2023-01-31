/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:11:44 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/19 14:53:11 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>
# include <memory> //std::allocator
# include <limits> //max_size
# include "ReverseIterator.hpp"
# include "RandomAccessIterator.hpp"
# include "TypeTraits.hpp"
# include "Algorithm.hpp"

namespace ft {

	template<typename T, typename Allocator = std::allocator<T> >
	class vector 
	{
		public:
			/*** Member types ***/
			typedef T 													value_type;
			typedef Allocator 											allocator_type;
			typedef std::size_t 										size_type;
			typedef std::ptrdiff_t 										difference_type;
			typedef value_type& 										reference;
			typedef const value_type& 									const_reference;
			typedef typename Allocator::pointer 						pointer;
			typedef typename Allocator::const_pointer 					const_pointer;
			typedef typename ft::RandomAccessIterator<value_type>		iterator;
			typedef typename ft::RandomAccessIterator<const value_type>	const_iterator;
			typedef typename ft::ReverseIterator<iterator> 				reverse_iterator;
			typedef typename ft::ReverseIterator<const_iterator> 		const_reverse_iterator;
		
		protected:
			allocator_type 	_allocator;
			pointer 		_start;
			pointer 		_finish;
			pointer 		_end_of_storage;
		
		public:

			/*** Member functions ***/

			vector( void ) : _start(0), _finish(0), _end_of_storage(0),
				_allocator(allocator_type())
			{
			};

			explicit vector(const allocator_type& allocator)
				: _start(0), _finish(0), _end_of_storage(0), 
				_allocator(allocator)
			{
			};

			explicit vector(size_type n, const T& value = T(), const allocator_type& allocator = allocator_type()) 
				:_start(_allocator.allocate(n)), _finish(_start + n),
				_end_of_storage(_start + n), _allocator(allocator)
			{
				for (int i = 0; i < n; i++)
					_allocator.construct(_start + i, value);
			};

			vector(vector<T> const& src) 
			{
				_allocator = src._allocator;
				_start = _allocator.allocate(src.size());
				_finish = _start + src.size();
				_end_of_storage = _start + src.capacity();
				*this = src;
			};

			template <class InputIt>
			vector(InputIt first, InputIt last, const allocator_type& allocator = allocator_type(),
			typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL) 
			{
				_allocator = allocator;
				_start = _allocator.allocate(last - first);
				_finish = _start + (last - first);
				_end_of_storage = _finish;
				for (int i = 0; i < (last - first); i++)
					_allocator.construct(_start + i, *(first + i));
			};

			~vector( void ) {
				clear();
				_allocator.deallocate(_start, capacity());
			};
			
			vector<T> & operator = ( vector<T> const & rhs)
			{
				if (this == &rhs)
					return *this;
				clear();
				_allocator.deallocate(_start, capacity());
				_allocator = rhs._allocator;
				_start = _allocator.allocate(rhs.capacity());
				_finish = _start + (rhs.size());
				_end_of_storage = _start + (rhs.capacity());
				for (int i = 0; i < size(); i++)
					_allocator.construct(_start + i, *(rhs._start + i));
				return *this;
			};
			
			void	assign( size_type n, const value_type& value ) 
			{
				if (n == 0)
					return ;
				if (n > capacity())
				{
					_allocator.deallocate(_start, capacity());
					_start = _allocator.allocate(n);
					_end_of_storage = _start + n;
				}
				for (int i = 0; i < n; ++i)
					_allocator.construct(_start + i, value);
				_finish = _start + n;
			};

			template <class InputIt>
			void	assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type* = NULL)
			{
				difference_type	count = last - first;
				if (count > capacity())
				{
					_allocator.deallocate(_start, capacity());
					_start = _allocator.allocate(count);
					_end_of_storage = _start + count;
				}
				for (int i = 0; i < count; ++i)
					_allocator.construct(_start + i, *(first + i));
				_finish = _start + count;
			};
			
			allocator_type get_allocator( void ) const { return _allocator; };
		
			/*** Iterators ***/
			iterator				begin() { return iterator(_start); };
			const_iterator			begin() const { return const_iterator(_start); };
			iterator				end() { return iterator(_finish); };
			const_iterator	 		end() const { return const_iterator(_finish); };
			reverse_iterator 		rbegin() { return reverse_iterator(end()); };
			const_reverse_iterator 	rbegin() const { return const_reverse_iterator(end()); };
			reverse_iterator 		rend() { return reverse_iterator(begin()); };
			const_reverse_iterator 	rend() const { return const_reverse_iterator(begin()); };

			/*** Element access ***/
		
			reference	at(size_type pos)
			{
				if (!(pos < size()))
					throw std::out_of_range("ft::vector::_M_range_check: __n >= this->size()");
				return *(_start + pos);
			};

			const_reference	at(size_type pos) const
			{
				if (!(pos < size()))
					throw std::out_of_range("ft::vector::_M_range_check: __n >= this->size()");
				return *(_start + pos);
			};
			
			reference		operator[](size_type pos) { return *(_start + pos); };
			const_reference	operator[](size_type pos) const { return *(_start + pos); };
			reference		front() { return *_start; };
			const_reference	front() const { return *_start; };
			reference		back() { return *(_finish - 1); };
			const_reference	back() const { return *(_finish - 1); };
			pointer			data() { return _start; };
			const_pointer	data() const { return _start; };
			
			/*** Capacity ***/
			bool		empty() { return begin() == end(); };
			size_type	size() const { return size_type(_finish - _start); };
			size_type	max_size() const { return allocator_type().max_size(); };
			
			void		reserve(size_type n)
			{
				if (n > max_size())
					throw std::length_error("vector::reserve");
				if (n > capacity())
				{
					pointer	new_start(_allocator.allocate(n));
					size_type tmp(size());
					for (int i = 0; i < size(); i++)
						_allocator.construct(new_start + i, *(_start + i));
					clear();
					_allocator.deallocate(_start, capacity());
					_start = new_start;
					_finish = _start + tmp;
					_end_of_storage = _start + n;
				}
			};
			
			size_type capacity() const { return size_type(_end_of_storage - _start); }; //returns no. of elements that can be held in currently allocated space
		
			/***Modifiers ***/
			void clear()
			{
				for (int i = 0; i < size(); i++)
					_allocator.destroy(_start + i);
				_finish = _start;
			};
		
			iterator	insert(const_iterator pos, const value_type& val)
			{
				if (pos < begin() | pos > end())
					throw std::logic_error("vector::insert");
				difference_type pos_diff(pos - const_iterator(begin()));
				size_type new_size(size() + 1);
				if (capacity() < new_size && capacity() * 2 <= max_size())
					reserve(capacity() * 2);
				else if (capacity() < new_size)
					reserve(new_size);
				for (int i = 0; i < (size() - pos_diff); ++i)
					_allocator.construct(_start + size() - i, *(_start + size() - 1 - i));
				_allocator.construct((_start + pos_diff), val);
				_finish += 1;
				return (_start + pos_diff);
			};

			iterator	insert(const_iterator pos, size_type count, const value_type& val)
			{
				if (pos < begin() | pos > end())
					throw std::logic_error("vector::insert");
				if (count < 0 || count + size() > max_size())
					throw std::length_error("vector::insert");
				difference_type pos_diff(0);
				if (size() != 0)
					pos_diff = pos - (const_iterator)begin();
				if (count == 0)
					return (_start + pos_diff);
				size_type new_size(size() + count);
				if (capacity() < new_size && capacity() * 2 <= max_size() && capacity() * 2 > new_size)
					reserve(capacity() * 2);
				else if (capacity() < new_size)
					reserve(new_size);
				for (int i = 0; i < (size() - pos_diff); ++i)
					_allocator.construct((_start + new_size - 1 - i), *(_start + size() - 1 - i));
				for (int i = 0; i < count; i++)
					_allocator.construct((_start + pos_diff + i), val);
				_finish = _start + new_size;
				return (_start + pos_diff);
			};
		
			template <class InputIt>
			iterator insert(const_iterator pos, InputIt first, InputIt last,
			typename ft::enable_if<!is_integral<InputIt>::value, InputIt>::type* = NULL)
			{
				if (pos < begin() || pos > end())
					throw std::logic_error("vector::insert");
				size_type count(last - first);
				if (count < 0 || count + size() > max_size())
					throw std::length_error("vector::insert");
				size_type new_size(size() + count);
				size_type pos_diff(0);
				if (size() != 0)
					pos_diff = pos - (const_iterator)begin();
				if (count == 0)
					return (_start + pos_diff);	
				if (capacity() < new_size && capacity() * 2 <= max_size() && capacity() * 2 > new_size)
					reserve(capacity() * 2);
				else if (capacity() < new_size)
					reserve(new_size);			
				for (int i = 0; i < (size() - pos_diff); ++i)
				{
					_allocator.construct((_start + new_size - 1 - i), *(_start + size() - 1 - i));
					_allocator.destroy(_start + size() - 1 - i);
				}
				for (int i = 0; i < count; i++)
				{
					_allocator.construct((_start + pos_diff + i), *(first + i));
				}
				_finish = _start + new_size;
				return (_start + pos_diff);
			};
		
		iterator	erase(iterator pos)
		{
			difference_type pos_diff(pos - (iterator)begin());
			for (int i = 0; pos_diff + i + 1 < size(); i++)
				_allocator.construct(_start + pos_diff + i, *(_start + pos_diff + i + 1));
			_allocator.destroy(_start + size() - 1);
			_finish -= 1;
			return iterator(_start + pos_diff);
		};
		
		iterator	erase(iterator first, iterator last)
		{
			difference_type pos_diff(first - (iterator)begin());
			difference_type count(last - first);
			for (int i = 0; i < count; i++)
				erase(_start + pos_diff);
			return (_start + pos_diff);
		};
		
		void	push_back(const value_type& val)
		{
			if (size() >= capacity())
			{
				if (capacity() && capacity() * 2 < max_size())
					reserve(capacity() * 2);
				else
					reserve(capacity() + 1);
			}
			_allocator.construct(_start + size(), val);
			_finish += 1;
		};
		
		void	pop_back()
		{
			_allocator.destroy(_start + size() - 1);
			_finish -= 1;
		};
		
		void	resize(size_type n, value_type val = value_type())
		{
			size_type	vec_size = size();
			if (n > max_size())
					throw std::length_error("vector::resize");
			else if (n < vec_size)
			{
				for (int i = vec_size - 1; i >= n; --i)
					_allocator.destroy(_start + i);
			}
			else if (n > vec_size)
			{
				if (n > capacity())
				{
					if (capacity() * 2 < max_size() && capacity() * 2 >= n)
						reserve(capacity() * 2);
					else
						reserve(n);
				}
				for (int i = vec_size; i < n; ++i)
					_allocator.construct(_start + i, val);
			}
			_finish = _start + n;
		};
		
		void swap(vector &x)
		{
			
			std::swap(_start, x._start);
			std::swap(_allocator, x._allocator);
			std::swap(_finish, x._finish);
			std::swap(_end_of_storage, x._end_of_storage);
		};

		protected:
			
	};

	/*non member functions*/
	template <class T, class Alloc >
	bool	operator==(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (int i = 0; i < lhs.size(); ++i)
		{
			if (lhs[i] != rhs[i])
				return false;
		}
		return true;
	};

	template <class T, class Alloc >
	bool	operator!=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{
		return !(lhs == rhs);
	};

	template <class T, class Alloc >
	bool	operator<(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	};

	template <class T, class Alloc >
	bool	operator>(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{
		return rhs < lhs;
	};

	template <class T, class Alloc >
	bool	operator<=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{
		return !(lhs > rhs);
	};

	template <class T, class Alloc >
	bool	operator>=(const ft::vector<T, Alloc>& lhs, const ft::vector<T, Alloc>& rhs)
	{
		return !(lhs < rhs);
	};

	//specializes the std::swap algorithm
	namespace std{
		template< class T, class Alloc>
		void	swap(ft::vector<T,Alloc>& lhs,
					ft::vector<T,Alloc>& rhs)
		{
			lhs.swap(rhs);
		} ;
	} //namespace std

}

#endif