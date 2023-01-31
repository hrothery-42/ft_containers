/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBTreeIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 08:34:14 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/16 10:00:53 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBTREEITERATOR_HPP
# define RBTREEITERATOR_HPP
# include <iostream>
# include "IteratorTraits.hpp"
# include "RedBlackTree.hpp"
namespace ft {
	
	template<class T>
	struct Node;

	template<class T>
	class RBTreeIterator
	{
		public:
		
		typedef typename ft::iterator_traits<T*>::value_type  		value_type;
		typedef typename ft::iterator_traits<T*>::difference_type  	difference_type;
		typedef typename ft::iterator_traits<T*>::pointer			pointer;
		typedef typename ft::iterator_traits<T*>::reference 		reference;
		typedef typename ft::bidirectional_iterator_tag				iterator_category;

		typedef ft::Node<value_type>						node_type;
		typedef node_type &									nodeRef;
		typedef node_type *									nodePtr;
		typedef RBTreeIterator<T>							self_type;
		
			nodePtr 					_node;
			nodePtr 					_minNode;
			nodePtr 					_maxNode;
		
			RBTreeIterator() : _node(NULL), _minNode(NULL), _maxNode(NULL)
			{ 
			};

			explicit RBTreeIterator(nodePtr node) : _node(node), _minNode(getSmallestNode()), _maxNode(getBiggestNode())
			{
			};

			RBTreeIterator(self_type const& src) : _node(src._node), _minNode(src._minNode), _maxNode(src._maxNode)
			{
			};
			
			template <class U>
			RBTreeIterator (const RBTreeIterator<U>& src) : _node(src._node), _minNode(src._minNode), _maxNode(src._maxNode)
			{
			};
			
			RBTreeIterator& operator=(self_type const& rhs)
			{
				_node = rhs._node;
				_minNode = rhs._minNode;
				_maxNode = rhs._maxNode;
				return *this;
			};

			
			~RBTreeIterator() 
			{
			};

		nodePtr	getCurrent()
		{
			return _node;
		};

		/*increment and decrement*/
		RBTreeIterator & operator++() { increment(); return *this; };
		RBTreeIterator operator++(int) { self_type tmp(*this); increment(); return tmp; };
		RBTreeIterator & operator--() { decrement(); return *this; };
		RBTreeIterator operator--(int) { self_type tmp(*this); decrement(); return tmp; };

		/*reference and dereference*/
		reference operator*() const { return _node->data; };
		pointer operator->() const { return &_node->data; };

		/*equality and inequality operators*/
		bool operator==(self_type const& rhs)
		{
			return this->_node == rhs._node;
		};

		bool operator!=(self_type const& rhs)
		{
			return this->_node != rhs._node;
		};

		private:

			nodePtr getSmallestNode()
			{
				nodePtr tmp(_node);
				while (tmp->parent)
					tmp = tmp->parent;
				while (tmp->left)
					tmp = tmp->left;
				return tmp;
			};

			nodePtr getBiggestNode()
			{
				nodePtr tmp(_node);
				while (tmp->parent)
					tmp = tmp->parent;
				while (tmp->right)
					tmp = tmp->right;
				return tmp;
			};

			nodePtr increment() 
			{
				if (_node == _maxNode)
				{
					_node = _node->end;
					return _node;
				}
				else if (_node == _maxNode->end)
				{
					std::cout <<"node is already one place past the biggest node\n";
					return _node;
				}
				else if (_node == _minNode->rend)
				{
					_node = _minNode;
				}
				else if (_node->right)
				{
					_node = _node->right;
					while (_node->left)
						_node = _node->left;
					return _node;
				}
				else
				{
					while (_node->isLeftSibling == false && _node->parent)
						_node = _node->parent;
					if (_node->isLeftSibling == true && _node->parent)
					{
						_node = _node->parent;
						return _node;
					}
				}
				return _node;
			};

			nodePtr decrement()
			{
				if (_node == _maxNode->end)
				{
					_node = _maxNode;
					return _node;
				}
				else if (_node == _minNode)
				{
					_node = _minNode->rend;
				}
				else if (_node == _minNode->rend)
				{
					std::cout <<"node is already min\n";
					return _node;
				}
				else if (_node->left)
				{
					_node = _node->left;
					while (_node->right)
						_node = _node->right;
					return _node;
				}
				else
				{
					while (_node->isLeftSibling == true && _node->parent)
						_node = _node->parent;
					if (_node->isLeftSibling == false && _node->parent)
					{
						_node = _node->parent;
						return _node;
					}
				}
				return _node;
			};
			
	};

/*
	template<class T>
	class RBTreeConstIterator
	{
		public:
		
		
		typedef typename ft::iterator_traits<T*>::value_type 	value_type;
		typedef typename ft::iterator_traits<T*>::difference_type  	difference_type;
		typedef typename ft::iterator_traits<const T*>::pointer		pointer;
		typedef typename ft::iterator_traits<const T*>::reference 	reference;
		typedef typename ft::bidirectional_iterator_tag				iterator_category;
		
		typedef RBTreeIterator<value_type>							iterator;
		typedef ft::Node<value_type>								node_type;
		typedef node_type &											nodeRef;
		typedef node_type *											nodePtr;
		typedef RBTreeConstIterator<T>								self_type;
		

		protected:
			nodePtr 					_node;
			nodePtr 					_minNode;
			nodePtr 					_maxNode;
		
		public:
			RBTreeConstIterator() : _node(NULL), _minNode(NULL), _maxNode(NULL) {};
			explicit RBTreeConstIterator(nodePtr node) : _node(node), _minNode(getSmallestNode()), _maxNode(getBiggestNode()) {};
			RBTreeConstIterator(self_type const& src) : _node(src._node), _minNode(src._minNode), _maxNode(src._maxNode) {};

			RBTreeConstIterator& operator=(self_type const& rhs)
			{
				_node = rhs._node;
				_minNode = rhs._minNode;
				_maxNode = rhs._maxNode;
				return *this;
			};
			~RBTreeConstIterator() {};

		nodePtr		getCurrent()
		{
			return _node;
		};
	
		RBTreeConstIterator & operator++() { increment(); return *this; };
		RBTreeConstIterator operator++(int) { self_type tmp(_node); increment(); return tmp; };
		RBTreeConstIterator & operator--() { decrement(); return *this; };
		RBTreeConstIterator operator--(int) { self_type tmp(_node); decrement(); return tmp; };


		reference operator*() const { return _node->data; };
		pointer operator->() const { return &_node->data; };


		private:


			nodePtr getSmallestNode()
			{
				nodePtr tmp(_node);
				while (tmp->parent)
					tmp = tmp->parent;
				while (tmp->left)
					tmp = tmp->left;
				return tmp;
			};

			nodePtr getBiggestNode()
			{
				nodePtr tmp(_node);
				while (tmp->parent)
					tmp = tmp->parent;
				while (tmp->right)
					tmp = tmp->right;
				return tmp;
			};

			nodePtr increment() 
			{
				_minNode = getSmallestNode();
				_maxNode = getBiggestNode();
				if (_node == _maxNode)
				{
					_node = _node->end;
					return _node;
				}
				else if (_node == _maxNode->end)
				{
					std::cout <<"node is already one place past the biggest node\n";
					return _node;
				}
				
				if (_node->right)
				{
					_node = _node->right;
					while (_node->left)
						_node = _node->left;
					return _node;
				}
				else
				{
					while (_node->isLeftSibling == false && _node->parent)
						_node = _node->parent;
					if (_node->isLeftSibling == true && _node->parent)
					{
						_node = _node->parent;
						return _node;
					}
				}
				return _node;
			};

			nodePtr decrement()
			{
				_minNode = getSmallestNode();
				_maxNode = getBiggestNode();
				if (_node == _maxNode->end)
				{
					_node = _maxNode;
					return _node;
				}
				else if (_node == _minNode)
				{
					std::cout <<"node is already min\n";
					return _node;
				}
				if (_node->left)
				{
					_node = _node->left;
					while (_node->right)
						_node = _node->right;
					return _node;
				}
				else
				{
					while (_node->isLeftSibling == true && _node->parent)
						_node = _node->parent;
					if (_node->isLeftSibling == false && _node->parent)
					{
						_node = _node->parent;
						return _node;
					}
				}
				return _node;
			};
			
	};
*/
	template<class V>
	bool	operator==(RBTreeIterator<V>& lhs, RBTreeIterator<V>& rhs)
	{
		return lhs.getCurrent() == rhs.getCurrent();
	};

	template<class V>
	bool	operator!=(RBTreeIterator<V>& lhs, RBTreeIterator<V>& rhs)
	{
		return lhs.getCurrent() != rhs.getCurrent();
	};
/*
	template<class V>
	bool	operator==(RBTreeIterator<V>& lhs, RBTreeConstIterator<V>& rhs)
	{
		return lhs.getCurrent() == rhs.getCurrent();
	};

	template<class V>
	bool	operator!=(RBTreeIterator<V>& lhs, RBTreeConstIterator<V>& rhs)
	{
		return lhs.getCurrent() != rhs.getCurrent();
	};

	template<class V>
	bool	operator==(RBTreeConstIterator<V>& lhs, RBTreeIterator<V>& rhs)
	{
		return lhs.getCurrent() == rhs.getCurrent();
	};

	template<class V>
	bool	operator!=(RBTreeConstIterator<V>& lhs, RBTreeIterator<V>& rhs)
	{
		return lhs.getCurrent() != rhs.getCurrent();
	};

	template<class V>
	bool	operator==(RBTreeConstIterator<V>& lhs, RBTreeConstIterator<V>& rhs)
	{
		return lhs.getCurrent() == rhs.getCurrent();
	};

	template<class V>
	bool	operator!=(RBTreeConstIterator<V>& lhs, RBTreeConstIterator<V>& rhs)
	{
		return lhs.getCurrent() != rhs.getCurrent();
	};
*/

}


#endif