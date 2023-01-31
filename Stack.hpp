/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:16:47 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/16 10:42:08 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
# include "Vector.hpp"
# include <iostream>

namespace ft {

	template<
		class T,
		class Container = ft::vector<T>
	> class stack {
	
	//the container used must provide the following functions: back(), push_back(), pop_back()
	//std::vector, std::deque, and std::list satisfy these requirements
	
	public:

		typedef Container								container_type;
		typedef typename Container::value_type			value_type;
		typedef typename Container::size_type			size_type;
		typedef typename Container::reference			reference;
		typedef typename Container::const_reference		const_reference;

	explicit stack( const Container& cont = Container() )
		: c(cont)
	{
		
	};

	stack(const stack& other)
		: c(other.c)
	{
		
	};

	~stack()
	{
		
	};

	stack& operator=(const stack& other)
	{
		if (this == & other)
			return *this;
		c = other.c;
		return *this;
	};

	reference	top()
	{
		return c.back();
	};

	const_reference	top() const
	{
		return c.back();
	};

	bool	empty()
	{
		return c.empty();
	};

	size_type	size() const
	{
		return c.size();
	};
	
	void	push( const value_type& value)
	{
		c.push_back(value);
	};

	void	pop()
	{
		c.pop_back();
	};

	//a friend function, despite not being a member of this class, allows this class to 
	//access private and protected members of the class, thus it can access "c" in lhs and rhs
	friend
	bool operator==(const stack<T, Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c == rhs.c);
	};

	friend
	bool operator<(const stack<T,Container>&lhs, const stack<T,Container>&rhs)
	{
	return (lhs.c < rhs.c);
	};

	protected:

		Container	c;

	};
	
	/*non member functions*/
	
	template< class T, class Container >
	bool	operator != (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
	{
		return !(lhs == rhs);
	};

	template< class T, class Container >
	bool	operator <= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
	{
		return !(rhs < lhs);
	};

	template< class T, class Container >
	bool	operator >= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
	{
		return !(lhs < rhs);
	};

	template< class T, class Container >
	bool	operator > (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
	{
		return (rhs < lhs);
	};
	
}

#endif