/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 08:45:54 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/16 10:11:57 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACKTREE_HPP
# define REDBLACKTREE_HPP
# include <iostream>
# include "ExtractKey.hpp"
# include "RBTreeIterator.hpp"
# include <cstdlib>
# include <cstddef> //NULL
# include "ReverseIterator.hpp"

# define RBT_RED "\033[31;1m"
# define RBT_BLACK "\033[0m"

namespace ft {

	# define BLACK 0
	# define RED 1

	template<class V>
	struct Node
	{
		
		V		data;
		Node *	parent;
		Node *	left;
		Node *	right;
		Node *  end;
		Node *  rend;
		bool	color;
		bool	isLeftSibling;

		Node(V val = V()) :
			data(val),
			parent(NULL),
			left(NULL),
			right(NULL),
			end(NULL),
			rend(NULL),
			color(BLACK),
			isLeftSibling(false) {
				std::cout <<"node: constructor called\n";
			};
		
		Node(const Node& src) :
			data(src.data),
			parent(src.parent),
			left(src.left),
			right(src.right),
			end(src.end),
			rend(src.end),
			color(src.color),
			isLeftSibling(src.isLeftSibling) {
				std::cout <<"node: copy constructor called\n";
			};
		
		~Node() {};

		private:
		Node& operator=(const Node& rhs); //can't be used because some data types are const
	};

	template <class T, class Key, class Compare, class Allocator = std::allocator<T> >
	class RedBlackTree
	{
		public:

		typedef T											value_type;
		typedef Key											key_type;
		typedef Compare										key_compare;
		typedef typename Allocator::template rebind<Node<T> >::other	allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference 	const_reference;
		typedef typename allocator_type::pointer 			pointer;
		typedef typename allocator_type::const_pointer 		const_pointer;
		typedef typename allocator_type::difference_type 	difference_type;
		typedef typename allocator_type::size_type			size_type;
		typedef Node<T>* 									nodePtr;
	

		typedef RBTreeIterator<value_type> iterator;
		typedef RBTreeIterator<const value_type> const_iterator;
		typedef ft::ReverseIterator<iterator> reverse_iterator;
		typedef ft::ReverseIterator<const_iterator> const_reverse_iterator;
		
		
		nodePtr 					root;
		key_compare 				compare;
		Allocator 					typeAlloc;
		allocator_type 				wholeNodeAlloc;
		nodePtr						endNode;
		nodePtr						rendNode;
		
		RedBlackTree(const key_compare& c = key_compare(), const allocator_type& a = allocator_type()) :
			root(NULL),
			compare(c),
			wholeNodeAlloc(a),
			typeAlloc(Allocator())
		{
			endNode = fillNodeWith(value_type());
			rendNode = fillNodeWith(value_type());
		};
		
		RedBlackTree(RedBlackTree const& src) :
			wholeNodeAlloc(src.wholeNodeAlloc),
			typeAlloc(src.typeAlloc),
			compare(src.compare)
		{
			//endNode = wholeNodeAlloc.allocate(1);
			//rendNode = wholeNodeAlloc.allocate(1);
			endNode = fillNodeWith(src.endNode->data);
			rendNode = fillNodeWith(src.rendNode->data);
			insert(src.begin(), src.end());
		};
	
		RedBlackTree& operator=(RedBlackTree const& rhs)
		{
			if (this != &rhs)
			{
				wholeNodeAlloc = rhs.wholeNodeAlloc;
				typeAlloc = rhs.typeAlloc;
				compare = rhs.compare;
				clear();
				insert(rhs.begin(), rhs.end());
			}
			return *this;
		};
		
		~RedBlackTree() {
			clear();
			deallocNode(endNode);
			deallocNode(rendNode);
		};

		//******************************
		//*********iterators************
		//******************************

		iterator	begin()
		{
			if (!root)
				return end();
			return iterator(findMin(root));
		};

		const_iterator	begin() const
		{
			if (!root)
				return end();
			return const_iterator(findMin(root));
		};
		
		iterator	end()
		{
			return iterator(endNode);
		};

		const_iterator end() const
		{
			return const_iterator(endNode);
		};

		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		};

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(end());
		};

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		};

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		};

		//******************************
		//*********Capacity*************
		//******************************

		size_type	size() const
		{
			if (!root)
				return 0;
			size_type count = 0;
			
			for (const_iterator it = begin(); it != end(); ++it)
				count++;
			return count;
		};

		size_type	max_size() const
		{
			return allocator_type().max_size();
		};

		bool	empty() const
		{
			if (begin() == end())
				return true;
			return false;
		}

		//******************************
		//*********Modifiers************
		//******************************

		void	clear()
		{
			if (!root)
			{
				linkWithEndNode(root);
				return;
			}
			while (root)
			{
				clearNodes(root);
				root = NULL;
				linkWithEndNode(root);
			}
		};
		
		ft::pair<iterator, bool> insert(T input)
		{
			nodePtr tmp(root);
			key_type key(extractKey(input));
			if (!root)
			{
				root = fillNodeWith(input);
				root = linkWithEndNode(root);
				return ft::pair<iterator, bool>(iterator(root), true);
			}
			while (1)
			{
				if (key == extractKey(tmp->data))
				{
					return ft::pair<iterator, bool>(iterator(tmp), false);
				}
				else if (!compare(key, extractKey(tmp->data)) && tmp->right)
					tmp = tmp->right;
				else if (compare(key, extractKey(tmp->data)) && tmp->left)
					tmp = tmp->left;
				else if (!compare(key, extractKey(tmp->data)) && !tmp->right)
				{
					tmp->right = fillNodeWith(input);
					tmp->right->parent = tmp;
					tmp->right->color = RED;
					tmp = tmp->right;
					root = restoreTree(root, tmp);
					root = linkWithEndNode(root);
					return ft::pair<iterator, bool>(iterator(tmp), true);
				}
				else if (compare(key, extractKey(tmp->data)) && !tmp->left)
				{
					tmp->left = fillNodeWith(input);
					tmp->left->parent = tmp;
					tmp->left->color = RED;
					tmp->left->isLeftSibling = 1;
					tmp = tmp->left;
					root = restoreTree(root, tmp);
					root = linkWithEndNode(root);
					return ft::pair<iterator, bool>(iterator(tmp), true);
				}
			}
			return ft::pair<iterator, bool>(iterator(tmp), false);
		};

		iterator insert(iterator pos, T input)
		{
			key_type key(extractKey(input));
			if (!root)
			{
				root = fillNodeWith(input);
				root = linkWithEndNode(root);
				return iterator(root);
			}
			iterator current(pos);
			iterator prev(current);
			if (prev != begin())
				--prev;
			iterator next(current);
			if (current != end() && current != --(end()))
				++next;
			if (current.getCurrent() && key == extractKey(current.getCurrent()->data))
				return current;
			else if (prev.getCurrent() && key == extractKey(prev.getCurrent()->data))
				return prev;
			else if (next.getCurrent() && key == extractKey(next.getCurrent()->data))
				return next;
			else if (compare(key, extractKey(current.getCurrent()->data)) && !compare(key, extractKey(prev.getCurrent()->data)) && !(current.getCurrent())->left)
			{
				current.getCurrent()->left = fillNodeWith(input);
				current.getCurrent()->left->parent = current.getCurrent();
				current.getCurrent()->left->color = RED;
				current.getCurrent()->left->isLeftSibling = 1;
				current = iterator(current.getCurrent()->left);
				root = restoreTree(root, current.getCurrent());
				root = linkWithEndNode(root);
				return current;
			}
			else if (!compare(key, extractKey(current.getCurrent()->data)) && compare(key, extractKey(next.getCurrent()->data)) && !(current.getCurrent())->right)
			{
				current.getCurrent()->right = fillNodeWith(input);
				current.getCurrent()->right->parent = current.getCurrent();
				current.getCurrent()->right->color = RED;
				current = iterator(current.getCurrent()->right);
				root = restoreTree(root, current.getCurrent());
				root = linkWithEndNode(root);
				return current;
			}
			else
				return insert(input).first;
		};

		template< class InputIt >
		void	insert(InputIt first, InputIt last)
		{
			for (; first != last; ++first)
				insert(*first);
		};

		void	deleteNode(iterator pos)
		{
			if (pos == end())
				return;
			if (!pos.getCurrent())
				return;
			nodePtr tmp(pos.getCurrent());
			nodePtr x(NULL);
			bool originalColor(tmp->color);
			if (!tmp->left && !tmp->right && tmp == root)
			{
				root = NULL;
				deallocNode(tmp);
				root = linkWithEndNode(root);
				return;
			}
			else if (!tmp->left) {
				x = tmp->right;
				nodePtr tmpParent = tmp->parent;
				root = nodeTransplant(root, tmp, x);
				deallocNode(tmp);
				if (x && originalColor == BLACK)
					x->color = BLACK;
				else if (originalColor == BLACK)
					root = deleteFix(root, x, tmpParent);
			}
			else if (!tmp->right)
			{
				nodePtr x = tmp->left;
				root = nodeTransplant(root, tmp, x);
				nodePtr tmpParent = tmp->parent;
				deallocNode(tmp);
				if (x && originalColor == BLACK) 
					x->color = BLACK;
				else if (originalColor == BLACK)
					root = deleteFix(root, x, tmpParent);
			}
			else if (tmp->right)
			{
				nodePtr y = findMaxSubtree(tmp->left);
				nodePtr x = y->left;
				originalColor = y->color;
				nodePtr tmpParent = y->parent;
				
				rewriteData(tmp->data, y->data);
				
				root = nodeTransplant(root, y, x);
				deallocNode(y);
				if (x && originalColor == BLACK)
					x->color = BLACK;
				else if (originalColor == BLACK)
					root = deleteFix(root, x, tmpParent);
			}
			root = linkWithEndNode(root);
			return;
		};

		void	deleteNode(iterator first, iterator last)
		{
			iterator it(first);
			for (; it != last;)
			{
				iterator next(it);
				++next;
				deleteNode(it);
				it = next;
			}
		};

		size_type	deleteNode(const key_type& key)
		{
			if (!root)
				return 0;
			nodePtr tmp = root;
			nodePtr x(NULL);
			bool originalColor(BLACK);
			while (1)
			{
				if (key == extractKey(tmp->data))
				{
					originalColor = tmp->color;
					if (!tmp->left && !tmp->right && tmp == root)
					{
						deallocNode(tmp);
						root = NULL;
						linkWithEndNode(root);
						return 1;
					}
					else if (!tmp->left)
					{
						x = tmp->right;
						nodePtr tmpParent = tmp->parent;
						root = nodeTransplant(root, tmp, x);
						deallocNode(tmp);
						if (x && originalColor == BLACK)
							x->color = BLACK;
						else if (originalColor == BLACK)
							root = deleteFix(root, x, tmpParent);
					}
					else if (!tmp->right)
					{
						nodePtr x(tmp->left);
						nodePtr tmpParent(NULL);
						root = nodeTransplant(root, tmp, x);
						if (tmp->parent)
							tmpParent = tmp->parent;
						deallocNode(tmp);
						if (x && originalColor == BLACK) 
							x->color = BLACK;
						else if (originalColor == BLACK)
							root = deleteFix(root, x, tmpParent);
					}
					else if (tmp->right)
					{
						nodePtr y = findMaxSubtree(tmp->left);
						nodePtr x = y->left;
						originalColor = y->color;

						rewriteData(tmp->data, y->data);

						nodePtr tmpParent = y->parent;
						root = nodeTransplant(root, y, x);
						deallocNode(y);
						
						if (x && originalColor == BLACK)
							x->color = BLACK;
						else if (originalColor == BLACK)
							root = deleteFix(root, x, tmpParent);
					}
					root = linkWithEndNode(root);
					return 1;
				}
				else if (!compare(key, extractKey(tmp->data)) && tmp->right)
					tmp = tmp->right;
				else if (compare(key, extractKey(tmp->data)) && tmp->left)
					tmp = tmp->left;
				else if (!compare(key, extractKey(tmp->data)) && !tmp->right)
					return 0;
				else if (compare(key, extractKey(tmp->data)) && !tmp->left)
					return 0;
			}
			return 1;
		};

		void	swap(RedBlackTree& other)
		{
			std::swap(root, other.root);
			std::swap(compare, other.compare);
			std::swap(typeAlloc, other.typeAlloc);
			std::swap(endNode, other.endNode);
		};

		//************************************
		//********Lookup**********************
		//************************************

		size_type	count(key_type key) const
		{
			if (!root)
				return 0;
			nodePtr tmp(root);
			while (1)
			{
				if (extractKey(tmp->data) == key)
					return 1;
				else if (compare(key, extractKey(tmp->data)) && !tmp->left)
					return 0;
				else if (!compare(key, extractKey(tmp->data)) && !tmp->right)
					return 0;
				else if (compare(key, extractKey(tmp->data)) && tmp->left)
					tmp = tmp->left;
				else if (!compare(key, extractKey(tmp->data)) && tmp->right)
					tmp = tmp->right;
			}
			return 0;
		};

		iterator	find(key_type key)
		{
			if (!root)
				return end();
			nodePtr tmp(root);
			while (1)
			{
				if (key == extractKey(tmp->data))
					return iterator(tmp);
				else if (!compare(key, extractKey(tmp->data)) && tmp->right)
					tmp = tmp->right;
				else if (compare(key, extractKey(tmp->data)) && tmp->left)
					tmp = tmp->left;
				else if (!compare(key, extractKey(tmp->data)) && !tmp->right)
					return end();
				else if (compare(key, extractKey(tmp->data)) && !tmp->left)
					return end();
			}
			return end();
		};
		
		const_iterator	find(key_type key) const
		{
			if (!root)
				return end();
			nodePtr tmp(root);
			while (1)
			{
				if (key == extractKey(tmp->data))
					return iterator(tmp);
				else if (!compare(key, extractKey(tmp->data)) && tmp->right)
					tmp = tmp->right;
				else if (compare(key, extractKey(tmp->data)) && tmp->left)
					tmp = tmp->left;
				else if (!compare(key, extractKey(tmp->data)) && !tmp->right)
					return end();
				else if (compare(key, extractKey(tmp->data)) && !tmp->left)
					return end();
			}
			return end();
		};

		value_type* findKey(key_type key) const
		{
			if (!root)
				return NULL;
			nodePtr tmp = root;
			while (1)
			{
				if (extractKey(tmp->data) == key)
					return &(tmp->data);
				else if (!compare(key, extractKey(tmp->data)) && tmp->right)
					tmp = tmp->right;
				else if (compare(key, extractKey(tmp->data)) && tmp->left)
					tmp = tmp->left;
				else if (!compare(key, extractKey(tmp->data)) && !tmp->right)
					return NULL;
				else if (compare(key, extractKey(tmp->data)) && !tmp->left)
					return NULL;
			}
			return NULL;
		};

		iterator	lower_bound(key_type key)
		{
			if (!root)
				return end();
			nodePtr tmp(root);
			while (1)
			{
				if (key == extractKey(tmp->data))
					return iterator(tmp);
				else if (!compare(key, extractKey(tmp->data)) && tmp->right)
					tmp = tmp->right;
				else if (compare(key, extractKey(tmp->data)) && tmp->left)
					tmp = tmp->left;
				else if (!compare(key, extractKey(tmp->data)) && !tmp->right)
					return ++(iterator(tmp));
				else if (compare(key, extractKey(tmp->data)) && !tmp->left)
					return iterator(tmp);
				}
			return end();
		}

		const_iterator	lower_bound(key_type key) const
		{
			if (!root)
				return end();
			nodePtr tmp(root);
			while (1)
			{
				if (key == extractKey(tmp->data))
					return iterator(tmp);
				else if (!compare(key, extractKey(tmp->data)) && tmp->right)
					tmp = tmp->right;
				else if (compare(key, extractKey(tmp->data)) && tmp->left)
					tmp = tmp->left;
				else if (!compare(key, extractKey(tmp->data)) && !tmp->right)
					return ++(iterator(tmp));
				else if (compare(key, extractKey(tmp->data)) && !tmp->left)
					return iterator(tmp);
				}
			return end();
		};

		iterator	upper_bound(key_type key)
		{
			if (!root)
				return end();
			nodePtr tmp(root);
			while (1)
			{
				if (key == extractKey(tmp->data))
					return ++iterator(tmp);
				else if (!compare(key, extractKey(tmp->data)) && tmp->right)
					tmp = tmp->right;
				else if (compare(key, extractKey(tmp->data)) && tmp->left)
					tmp = tmp->left;
				else if (!compare(key, extractKey(tmp->data)) && !tmp->right)
					return ++(iterator(tmp));
				else if (compare(key, extractKey(tmp->data)) && !tmp->left)
					return iterator(tmp);
				}
			return end();
		};

		const_iterator	upper_bound(key_type key) const
		{
			if (!root)
				return end();
			nodePtr tmp(root);
			while (1)
			{
				if (key == extractKey(tmp->data))
					return ++iterator(tmp);
				else if (!compare(key, extractKey(tmp->data)) && tmp->right)
					tmp = tmp->right;
				else if (compare(key, extractKey(tmp->data)) && tmp->left)
					tmp = tmp->left;
				else if (!compare(key, extractKey(tmp->data)) && !tmp->right)
					return ++(iterator(tmp));
				else if (compare(key, extractKey(tmp->data)) && !tmp->left)
					return iterator(tmp);
				}
			return end();
		};

		void	printHorizontalTree(nodePtr root) const
		{
			if (root)
				printNode(root, 0);
		};

		private:

			void	clearNodes(nodePtr node)
			{
				if (!node)
					return;
				if (node->left)
					clearNodes(node->left);
				if (node->right)
					clearNodes(node->right);
				if (node->isLeftSibling && node->parent)
					node->parent->left = NULL;
				else if (node->parent)
					node->parent->right = NULL;
				deallocNode( node );
			};

			void	deallocNode( nodePtr node)
			{
				wholeNodeAlloc.deallocate(node, 1);
				node = NULL;
			};

			nodePtr deleteFix(nodePtr root, nodePtr x, nodePtr parent)
			{
				while ((!x || (x && x != root)) && (!x || (x && x->color == BLACK)))
				{
					if ((x && x->isLeftSibling) || (!x && !parent->left && parent->right))
					{
						nodePtr sibling = findSibling(x, parent);
						if (sibling && sibling->color == RED)
						{
							sibling->color = BLACK;
							sibling->parent->color = RED;
							root = rotateLeft(root, sibling, sibling->parent);
							sibling = findSibling(x, parent);
						}
						if (sibling && ((!sibling->left || (sibling->left && sibling->left->color == BLACK)) && (!sibling->right || (sibling->right && sibling->right->color == BLACK))))
						{
							sibling->color = RED;
							if (x)
							{
								x = x->parent;
								parent = x->parent;
							}
							else
							{
								x = parent;
								parent = x->parent;
							}
						}
						else
						{
							if (sibling && (!sibling->right || (sibling->right && sibling->right->color == BLACK)))
							{
								if (sibling->left)
									sibling->left->color = BLACK;
								sibling->color = RED;
								root = rotateRight(root, sibling->left, sibling);
								sibling = findSibling(x, parent);
							}
							
							sibling->color = sibling->parent->color;
							sibling->parent->color = BLACK;
							if (sibling->right)
								sibling->right->color = BLACK;
							
							root = rotateLeft(root, sibling, sibling->parent);
							x = root;
						}
					}
					else //x is right sibling
					{
						nodePtr sibling = findSibling(x, parent);
						if (sibling && sibling->color == RED)
						{
							sibling->color = BLACK;
							sibling->parent->color = RED;
							root = rotateRight(root, sibling, sibling->parent);
							sibling = findSibling(x, parent);
						}
						if ((!sibling->right || (sibling->right && sibling->right->color == BLACK)) && (!sibling->left || (sibling->left && sibling->left->color == BLACK)))
						{
							sibling->color = RED;
							if (x) {
								x = x->parent;
								parent = x->parent;
							}
							else {
								x = parent;
								parent = x->parent;
							}
						}
						else
						{
							if (!sibling->left || (sibling->left && sibling->left->color == BLACK))
							{
								if (sibling->right)
									sibling->right->color = BLACK;
								sibling->color = RED;
								root = rotateLeft(root, sibling->right, sibling);
								sibling = findSibling(x, parent);
							}
							if (sibling && parent)
								sibling->color = parent->color;
							if (parent)
								parent->color = BLACK;
							if (sibling->left)
								sibling->left->color = BLACK;
							root = rotateRight(root, sibling, parent);
							x = root;
						}
					}
				}
				if (x)
					x->color = BLACK;
				return root;
			};

			nodePtr findMax(nodePtr node) const
			{
				nodePtr tmp(node);
				while (tmp->parent)
					tmp = tmp->parent;
				while (tmp->right)
					tmp = tmp->right;
				return tmp;
			};

			nodePtr findMaxSubtree(nodePtr subtreeNode) const
			{
				nodePtr tmp(subtreeNode);
				while (tmp->right)
					tmp = tmp->right;
				return tmp;
			};

			nodePtr findMin(nodePtr node) const
			{
				nodePtr tmp(node);
				while (tmp->parent)
					tmp = tmp->parent;
				while (tmp->left)
					tmp = tmp->left;
				return tmp;
			};

			nodePtr findSibling(nodePtr child, nodePtr parent)
			{
				if (!parent)
					return NULL;
				nodePtr sibling(NULL);
				if ((!child && !parent->left && parent->right) || (child && child->isLeftSibling))
					sibling = parent->right;
				else
					sibling = parent->left;
				return sibling;
			};

			nodePtr findUncle(nodePtr tmp)
			{
				if (!tmp->parent)
					return NULL;
				if (tmp->parent->parent && tmp->parent->isLeftSibling == false)
				{
					return tmp->parent->parent->left;
				}
				else if (tmp->parent->parent && tmp->parent->isLeftSibling == true)
				{
					return tmp->parent->parent->right;
				}
				else {
					return NULL;
				}
			};

			nodePtr fillNodeWith(const T& input)
			{
				nodePtr newNode = wholeNodeAlloc.allocate(1);
				typeAlloc.construct(&(newNode->data), input);
				newNode->left = NULL,
				newNode->right = NULL;
				newNode->end = NULL;
				newNode->rend = NULL;
				newNode->parent = NULL;
				newNode->color = BLACK;
				newNode->isLeftSibling = 0;
				return newNode;
			};

			nodePtr	linkWithEndNode(nodePtr root)
			{
				if (!root)
				{
					endNode->parent = NULL;
					rendNode->parent = NULL;
				}
				else
				{
					nodePtr tmp = findMax(root);
					tmp->end = endNode;
					endNode->parent = tmp;
					nodePtr minTmp = findMin(root);
					minTmp->rend = rendNode;
					rendNode->parent = minTmp;
				}
				return root;
			};

			nodePtr	nodeTransplant(nodePtr root, nodePtr toDelete, nodePtr x)
			{
				if (toDelete->parent)
				{
					nodePtr parent = toDelete->parent;
					if (toDelete->isLeftSibling)
					{
						parent->left = x;
						if (x)
						{
							x->isLeftSibling = true;
							x->parent = parent;
						}
						return root;
					}
					else if (!toDelete->isLeftSibling)
					{
						parent->right = x;
						if (x)
						{
							x->isLeftSibling = false;
							x->parent = parent;
						}
						return root;
					}
				}
				else
				{
					root = x;
					if (x)
						x->parent = NULL;
					return root;
				}
				return root;
			};

			void	printNode(nodePtr node, int count) const
			{
				for (int i = 0; i < count; ++i)
					std::cout <<"    ";
				if (node)
				{
					if (!node->parent)
						std::cout <<" ";
					else if (node->isLeftSibling == false)
						std::cout <<"--";
					else if (node->isLeftSibling == true)
						std::cout <<"|_";
					if (node->color == RED)
						std::cout <<RBT_RED;
					std::cout <<"(" <<extractKey(node->data) <<")\n";
					std::cout <<RBT_BLACK;
					if (node->right)
						printNode(node->right, count + 1);
					else
					{
						for (int i = 0; i < count + 1; ++i)
							std::cout <<"    ";
						std::cout <<"--()\n";
					}
					if (node->left)
						printNode(node->left, count + 1);
					else
					{
						for (int i = 0; i < count + 1; ++i)
							std::cout <<"    ";
						std::cout <<"|_()\n";
					}
				}
			};

			nodePtr restoreTree(nodePtr root, nodePtr tmp)
			{
				nodePtr uncle = findUncle(tmp);
				if (uncle && uncle->color == RED && tmp->parent && tmp->parent->color == RED) {
					uncle->color = BLACK;
					tmp->parent->color = BLACK;
					tmp->parent->parent->color = RED;
					root = restoreTree(root, tmp->parent->parent);
				}
				else if ((!uncle || (uncle && uncle->color == BLACK)) && tmp->parent && tmp->parent->color == RED) {
					if (tmp->isLeftSibling && tmp->parent->isLeftSibling) {
						root = rotateRight(root, tmp->parent, tmp->parent->parent);
						swapColors(tmp->parent, tmp->parent->right);
					}
					else if (!tmp->isLeftSibling && !tmp->parent->isLeftSibling) {
						root = rotateLeft(root, tmp->parent, tmp->parent->parent);
						swapColors(tmp->parent, tmp->parent->left);
					}
					else if (!tmp->parent->isLeftSibling && tmp->isLeftSibling) {
						root = rotateRight(root, tmp, tmp->parent);
					}
					else if (tmp->parent->isLeftSibling && !tmp->isLeftSibling) {
						root = rotateLeft(root, tmp, tmp->parent);
					}
				}
				if (root->color == RED)
					root->color = BLACK;
				if (tmp->left && tmp->left->color == RED && tmp->color == RED)
					root = restoreTree(root, tmp->left);
				if (tmp->right && tmp->right->color == RED && tmp->color == RED)
					root = restoreTree(root, tmp->right);
				return root;
			};

			nodePtr	rotateLeft(nodePtr root, nodePtr parent, nodePtr grandparent)
			{
				nodePtr tmp = parent->left;
				if (!grandparent->parent)
				{
					root = parent;
					parent->parent = NULL;
				}
				else
				{
					parent->parent = grandparent->parent;
					if (grandparent->isLeftSibling == true)
					{
						grandparent->parent->left = parent;
						parent->isLeftSibling = true;
					}
					else if (grandparent->isLeftSibling == false)
					{
						grandparent->parent->right = parent;
						parent->isLeftSibling = false;
					}
				}
				parent->left = grandparent;
				grandparent->parent = parent;
				grandparent->isLeftSibling = true;
				grandparent->right = tmp;
				if (tmp)
				{
					tmp->isLeftSibling = false;
					tmp->parent = grandparent;
				}
				return root;
			};

			nodePtr	rotateRight(nodePtr root, nodePtr parent, nodePtr grandparent)
			{
				nodePtr tmp = parent->right;
				if (!grandparent->parent)
				{
					root = parent;
					parent->parent = NULL;
				}
				else
				{
					parent->parent = grandparent->parent;
					if (grandparent->isLeftSibling == true)
					{
						grandparent->parent->left = parent;
						parent->isLeftSibling = true;
					}
					else if (grandparent->isLeftSibling == false)
					{
						grandparent->parent->right = parent;
						parent->isLeftSibling = false;
					}
				}
				parent->right = grandparent;
				grandparent->parent = parent;
				grandparent->isLeftSibling = false;
				grandparent->left = tmp;
				if (tmp)
				{
					tmp->isLeftSibling = true;
					tmp->parent = grandparent;
				}
				return root;
			};

			void	swapColors(nodePtr node1, nodePtr node2)
			{
				if (node2)
				{
					if (node2->color == RED)
						node2->color = BLACK;
					else
						node2->color = RED;
				}
				if (node1)
				{
					if (node1->color == RED)
						node1->color = BLACK;
					else
						node1->color = RED;
				}
			};

	};
	
}

#endif