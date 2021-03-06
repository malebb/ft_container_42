#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <iostream>
#include <stdlib.h>

#include "functional.hpp"
#include "utility.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "compare.hpp"

namespace ft
{
	template <class T>
	class avl
	{
		public :

			avl() : right(NULL), left(NULL), parent(NULL), end(false) {}
			avl(T* value) : value(value), right(NULL), left(NULL),
				parent(NULL), height(1), end(false)
			{
			}

			avl(const avl& src)
			{
				*this = src;
			}

			avl&		operator=(const avl& rhs)
			{
				this->value = rhs.value;
				this->right = rhs.right;
				this->left = rhs.left;
				this->parent = rhs.parent;
				this->height = rhs.height;
				this->end = rhs.end;
				return (*this);
			}

			T			*value;
			avl			*right;
			avl			*left;
			avl			*parent;
			int			height;
			bool		end;
	};

	struct bidirectional_iterator_tag {};

	template <class Key, class T, class Compare>
	class map_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
	{


		public :

			typedef Key												key_type;
			typedef T												mapped_type;
			typedef Compare											key_compare;
			typedef std::ptrdiff_t									difference_type;
			typedef ft::pair<const key_type, mapped_type>			value_type;
			typedef ft::pair<const key_type, mapped_type>&			reference;
			typedef ft::pair<const key_type, mapped_type>*			pointer;
			typedef avl<value_type>		tree_type;

			// Constructors / destructor

			map_iterator() : node(NULL) {}

			map_iterator(const map_iterator& src)
			{
				*this = src;
			}

			map_iterator&		operator=(const map_iterator& rhs)
			{
				this->node = rhs.node;

				return (*this);
			}

			map_iterator(tree_type *node) : node(node)
			{
			}

			virtual ~map_iterator() {}

			// comparison operators

			template <class T2>
			bool			operator==(const T2& rhs) const
			{
				return (this->node == rhs.node);
			}

			template <class T2>
			bool			operator!=(const T2& rhs) const
			{
				return (!(*this == rhs));
			}

			// member access operators

			value_type			*operator->() const
			{
				return (this->node->value);
			}

			value_type			&operator*() const
			{
				return (*(this->node->value));
			}

			// Increment / decrement operators

			map_iterator&		operator++()
			{
				const Key		origin_value = this->node->value->first;

				if (this->node->end)
					this->operator--();
				else
				{
					while ((this->_compare(this->node->value->first, origin_value) ||
								
							 (!this->_compare(this->node->value->first, origin_value)
								&& !this->_compare(origin_value, this->node->value->first)))
							&& !this->node->end)
					{
						if (this->node->right && 
							(this->_compare(origin_value, this->node->right->value->first)
							 || this->node->right->end))
							this->node = this->node->right;
						else
							this->node = this->node->parent;
					}
					while (this->node->left && 
						this->_compare(origin_value, this->node->left->value->first))
					{
						this->node = this->node->left;
					}
				}
				return (*this);
			}

			map_iterator		operator++(int)
			{
				map_iterator		tmp(*this);

				this->operator++();
				return (tmp);
			}

			map_iterator&		operator--()
			{
				tree_type		origin_node(*(this->node));

				if (this->node->end)
					this->node = this->node->parent;
				else if (!this->_compare(get_first_value()->first, origin_node.value->first)
						&& !this->_compare(origin_node.value->first, get_first_value()->first))
					this->node = get_last();
				else
				{
					while (!this->_compare(this->node->value->first, origin_node.value->first))
					{
						if (this->node->left &&
								this->_compare(this->node->left->value->first,
								origin_node.value->first))
							this->node = this->node->left;
						else
							this->node = this->node->parent;
					}
					while (this->node->right &&
						this->_compare(this->node->right->value->first, origin_node.value->first))
					{
						this->node = this->node->right;
					}
				}
				return (*this);
			}

			map_iterator		operator--(int)
			{
				map_iterator		tmp(*this);

				this->operator--();
				return (tmp);
			}


			tree_type			*node;
			key_compare			_compare;

		private :

			value_type		*get_first_value()
			{
				tree_type		*origin_node;

				origin_node = this->node;
				while (origin_node->parent)
				{
					origin_node = origin_node->parent;
				}
				while (origin_node->left != NULL)
				{
					origin_node = origin_node->left;
				}
				return (origin_node->value);
			}

			tree_type		*get_last()
			{
				tree_type		*origin_node;

				origin_node = this->node;
				while (origin_node->parent)
				{
					origin_node = origin_node->parent;
				}
				while (origin_node->right != NULL)
				{
					origin_node = origin_node->right;
				}
				return (origin_node);
			}
	};

	template <class Key, class T, class Compare>
	class const_map_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		public :

			typedef Key												key_type;
			typedef T												mapped_type;
			typedef Compare											key_compare;
			typedef std::ptrdiff_t									difference_type;
			typedef ft::pair<const key_type, mapped_type>			value_type;
			typedef const ft::pair<const key_type, mapped_type>*	pointer;
			typedef const ft::pair<const key_type, mapped_type>&	reference;
			typedef avl<value_type>									tree_type;

			// Constructors / destructor

			const_map_iterator() : node(NULL) {}

			const_map_iterator(map_iterator<Key, T, Compare> const & src)
			{
				*this = src;
			}

			const_map_iterator(const_map_iterator const & src)
			{
				*this = src;
			}

			const_map_iterator&		operator=(map_iterator<Key, T, Compare>const & rhs)
			{
				this->node = rhs.node;
				return (*this);
			}

			const_map_iterator&		operator=(const_map_iterator const & rhs)
			{
				this->node = rhs.node;
				return (*this);
			}

			const_map_iterator(tree_type *node) : node(node)
			{
			}

			virtual ~const_map_iterator() {}

			// comparison operators

			template <class T2>
			bool			operator==(const T2& rhs) const
			{
				return (this->node == rhs.node);
			}

			template <class T2>
			bool			operator!=(const T2& rhs) const
			{
				return (!(*this == rhs));
			}

			// member access operators

			pointer 		operator->() const
			{
				return (this->node->value);
			}

			reference		operator*() const
			{
				return (*(this->node->value));
			}

			// Increment / decrement operators

			const_map_iterator&		operator++()
			{
				const Key		origin_value = this->node->value->first;

				if (this->node->end)
					this->operator--();
				else
				{
					while ((this->_compare(this->node->value->first, origin_value) ||
								
							 (!this->_compare(this->node->value->first, origin_value)
								&& !this->_compare(origin_value, this->node->value->first)))
							&& !this->node->end)
					{
						if (this->node->right && 
							(this->_compare(origin_value, this->node->right->value->first)
							 || this->node->right->end))
							this->node = this->node->right;
						else
							this->node = this->node->parent;
					}
					while (this->node->left && 
						this->_compare(origin_value, this->node->left->value->first))
					{
						this->node = this->node->left;
					}
				}
				return (*this);
			}

			const_map_iterator		operator++(int)
			{
				const_map_iterator		tmp(*this);

				this->operator++();
				return (tmp);
			}

			const_map_iterator&		operator--()
			{
				tree_type		origin_node(*(this->node));

				if (this->node->end)
					this->node = this->node->parent;
				else if (!this->_compare(get_first_value()->first, origin_node.value->first)
						&& !this->_compare(origin_node.value->first, get_first_value()->first))
					this->node = get_last();
				else
				{
					while (!this->_compare(this->node->value->first, origin_node.value->first))
					{
						if (this->node->left &&
								this->_compare(this->node->left->value->first,
								origin_node.value->first))
							this->node = this->node->left;
						else
							this->node = this->node->parent;
					}
					while (this->node->right &&
						this->_compare(this->node->right->value->first, origin_node.value->first))
					{
						this->node = this->node->right;
					}
				}
				return (*this);
			}

			const_map_iterator		operator--(int)
			{
				const_map_iterator		tmp(*this);

				this->operator--();
				return (tmp);
			}


			tree_type		*node;
			key_compare		_compare;

		private :

			const value_type		*get_first_value()
			{
				tree_type		*origin_node;

				origin_node = this->node;
				while (origin_node->parent)
				{
					origin_node = origin_node->parent;
				}
				while (origin_node->left != NULL)
				{
					origin_node = origin_node->left;
				}
				return (origin_node->value);
			}

			tree_type		*get_last()
			{
				tree_type		*origin_node;

				origin_node = this->node;
				while (origin_node->parent)
				{
					origin_node = origin_node->parent;
				}
				while (origin_node->right != NULL)
				{
					origin_node = origin_node->right;
				}
				return (origin_node);
			}
	};

	template <class Key,
			 class T,
			 class Compare = ft::less<Key>,
			 class Alloc = std::allocator<ft::pair<const Key, T> >
			>
	class map
	{
		public :

			typedef Key											key_type;
			typedef T											mapped_type;
			typedef pair<const key_type, mapped_type>			value_type;
			typedef Compare										key_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::map_iterator<Key, T, Compare>			iterator;
			typedef ft::const_map_iterator<Key, T, Compare>		const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	 	const_reverse_iterator;

			// ...

			typedef std::ptrdiff_t								difference_type;
			typedef size_t										size_type;
			typedef typename allocator_type::template 
									rebind<avl<value_type> >::other			alloc_avl;

			class value_compare : public ft::binary_function<value_type, value_type, bool>
			{
				friend class map;

				public:

					typedef typename ft::binary_function<value_type,
							value_type, bool>::result_type		result_type;
					typedef typename ft::binary_function<value_type,
							value_type, bool>::first_argument_type
								first_argument_type;
					typedef typename ft::binary_function<value_type,
							value_type, bool>::second_argument_type
								second_argument_type;

				bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}


				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}
		};

		// constructors / destructors

		explicit map(const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
				: _compare(comp), _comp(this->_compare), _alloc(alloc), _size(0), _root(NULL), _alloc_avl()
		{
			value_type		end_node_value;

			this->_end_node = this->create_node(value_type());
			this->_end_node->end = 1;
			this->_root = this->_end_node;
		}

		template <class InputIterator>
			map(InputIterator first, InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
				: _compare(comp), _comp(this->_compare), _alloc(alloc), _size(0), _root(NULL), _alloc_avl()

			{
				value_type		end_node_value;

				this->_end_node = this->create_node(value_type());
				this->_end_node->end = 1;
				this->_root = this->_end_node;
				this->insert(first, last);
			}



		map(const map& x) : _compare(x._compare), _comp(x._comp),
			_alloc(x._alloc), _size(0), _root(NULL), _alloc_avl()
		{
				value_type		end_node_value;

				this->_end_node = this->create_node(value_type());
				this->_end_node->end = 1;
				this->_root = this->_end_node;
				this->insert(x.begin(), x.end());
		}

		~map()
		{
			this->clear();
			this->delete_node(this->_end_node);

		}

		map&	operator=(const map& x)
		{
			this->_compare = x._compare;
			this->_comp = x._comp;
			this->_alloc = x._alloc;
			this->clear();

			this->insert(x.begin(), x.end());
			return (*this);
		}

		// iterator

		iterator		begin()
		{
			avl<value_type>			*node;

			node = this->_root;
			while (node->left != NULL)
			{
				node = node->left;
			}
			return (iterator(node));
		}

		const_iterator		begin() const
		{
			avl<value_type>			*node;

			node = this->_root;
			while (node->left != NULL)
			{
				node = node->left;
			}
			return (const_iterator(node));
		}

		reverse_iterator	rbegin()
		{
			return (reverse_iterator(this->end()));
		}

		const_reverse_iterator	rbegin() const
		{
			return (const_reverse_iterator(this->end()));
		}

		iterator		end()
		{
			return (iterator(this->_end_node));
		}

		const_iterator		end() const
		{
			return (iterator(this->_end_node));
		}

		reverse_iterator	rend()
		{
			return (reverse_iterator(this->begin()));
		}

		const_reverse_iterator		rend() const
		{
			avl<value_type>			*node;

			node = this->_root;
			while (node->left != NULL)
			{
				node = node->left;
			}
			return (const_reverse_iterator(node));
		}

		// capacity

		bool			empty() const
		{
			return (!(this->_size));
		}

		size_type		size() const
		{
			return (this->_size);
		}

		size_type		max_size() const
		{
			return (this->_alloc_avl.max_size() - 1);
		}

		// element access

		mapped_type&		operator[](const key_type& k)
		{
			return ((*((this->insert(ft::make_pair(k,mapped_type()))).first)).second);
		}

		// modifiers

		ft::pair<iterator, bool>		insert(const value_type& val)
		{
			ft::pair<iterator, bool>	ret;

			ret = this->insertion(&this->_root, val, NULL);
			if (ret.second)
				this->_size++;
			return (ret);
		}
		
		iterator	insert(iterator position, const value_type& val)
		{
			iterator			next_to_position;
			avl<value_type>		*new_node;
			avl<value_type>		*old_node;

			next_to_position = position;
			next_to_position++;
			if (!position.node->end && this->_compare(position->first, val.first) && (next_to_position.node->end
				|| this->_compare(val.first, next_to_position->first)))
			{
				new_node = this->create_node(val);
				old_node = position.node->right;
				if (old_node)
					position.node->right->parent = new_node;
				position.node->right = new_node;
				new_node->parent = position.node;
				new_node->right = old_node;
				this->_size++;
				return (new_node);
			}
			else
				return (insert(val).first);
		}

		template <class InputIterator>
		void	insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				this->insert(*first);
				first++;
			}
		}

		void	erase(iterator position)
		{
			if (deletion(position))
				this->_size--;
		}

		size_type		erase(const key_type& k)
		{
			iterator		node;

			node = this->find(k);
			if (node == this->end())
				return (0);
			deletion(node);
			this->_size--;
			return (1);
		}

		void			erase(iterator first, iterator last)
		{
			iterator		next_it;

			while (first != last)
			{
				next_it = first;
				++next_it;
				deletion(first);
				this->_size--;
				first = next_it;
			}
		}

		void			swap(map& x)
		{
			const key_compare			compare = this->_compare;
			const allocator_type		alloc = this->_alloc;
			const size_type				size = this->_size;
			avl<value_type>		*root = this->_root;
			avl<value_type>		*end_node = this->_end_node;
			const alloc_avl				alloc_avl = this->_alloc_avl;

			this->_compare = x._compare;
			this->_alloc = x._alloc;
			this->_size = x._size;
			this->_root = x._root;
			this->_end_node = x._end_node;
			this->_alloc_avl = x._alloc_avl;

			x._compare = compare;
			x._alloc = alloc;
			x._size = size;
			x._root = root;
			x._end_node = end_node;
			x._alloc_avl = alloc_avl;
		}

		void			clear()
		{
			this->erase(this->begin(), this->end());
		}


		// observers

		key_compare		key_comp() const
		{
			return (this->_compare);
		}

		value_compare	value_comp() const
		{
			return (this->_comp);
		}

		// operations
		
		iterator		find(const key_type& k)
		{
			avl<value_type>		*node;

			node = this->_root;
			while (node && !node->end)
			{
				if (!this->_compare(node->value->first, k) && 
						!this->_compare(k, node->value->first))
					return (iterator(node));
				if (this->_compare(k, node->value->first))
					node = node->left;
				else
					node = node->right;
			}
			return (this->end());
		}

		const_iterator		find(const key_type& k) const
		{
			avl<value_type>		*node;

			node = this->_root;
			while (node && !node->end)
			{
				if (!this->_compare(node->value->first, k) && 
						!this->_compare(k, node->value->first))
					return (iterator(node));
				if (this->_compare(k, node->value->first))
					node = node->left;
				else
					node = node->right;
			}
			return (this->end());
		}

		size_type			count(const key_type& k) const
		{
			return (this->find(k).node != this->_end_node);
		}

		iterator			lower_bound(const key_type& k)
		{
			iterator		elem;

			elem = find(k);
			if (elem != this->end())
				return (elem);
			for (iterator it = this->begin(); it != this->end(); ++it)
			{
				if (this->_compare(k, it.node->value->first))
					return (it);
			}
			return (this->end());
		}

		const_iterator			lower_bound(const key_type& k) const
		{
			const_iterator		elem;

			elem = find(k);
			if (elem != this->end())
				return (elem);
			for (const_iterator it = this->begin(); it != this->end(); ++it)
			{
				if (this->_compare(k, it.node->value->first))
					return (it);
			}
			return (this->end());
		}

		iterator			upper_bound(const key_type& k)
		{
			iterator		elem;

			elem = find(k);
			if (elem != this->end())
				return (++elem);
			for (iterator it = this->begin(); it != this->end(); ++it)
			{
				if (this->_compare(k, it.node->value->first))
					return (it);
			}
			return (this->end());
		}

		const_iterator			upper_bound(const key_type& k) const
		{
			const_iterator		elem;

			elem = find(k);
			if (elem != this->end())
				return (++elem);
			for (const_iterator it = this->begin(); it != this->end(); ++it)
			{
				if (this->_compare(k, it.node->value->first))
					return (it);
			}
			return (this->end());
		}

		pair<const_iterator, const_iterator>		equal_range(const key_type& k) const
		{
			pair <const_iterator, const_iterator>		range;

			range.first = this->lower_bound(k);
			range.second = this->upper_bound(k);
			return (range);
		}

		pair<iterator, iterator>					equal_range(const key_type& k)
		{
			pair <iterator, iterator>		range;

			range.first = this->lower_bound(k);
			range.second = this->upper_bound(k);
			return (range);
		}

		// allocator
		
		allocator_type		get_allocator() const
		{
			return (this->_alloc);
		}
/*
 
// 		Functions useful to debug

		avl<value_type>		*get_tree()
		{
			return (this->_root);
		}

		bool		is_balanced(void) const
		{
			return (check_node(this->_root));
		}

		bool		check_node(const avl<value_type> *node) const
		{
			if (!node || (node && node->end))
				return (true);
			if (abs(this->get_height(node->left, 0, 0) - this->get_height(node->right, 0, 0)) >= 2)
				return (false);
			if (!check_node(node->right))
				return (false);
			if (!check_node(node->left))
				return (false);
			return (true);
		}

		void		print(void) const
		{
			browse_tree(this->_root, 'R', 0);
		}

		void	browse_tree(avl<value_type> *node, char floor, int depth) const
		{
			if (!node || (node && node->end))
				return ;

			for (int i = 0; i < depth; i++)
			{
				if (i % 5 == 1)
					std::cout << "\033[1;31m> \033[0m";
				else if (i % 5 == 2)
					std::cout << "\033[1;32m> \033[0m";
				else if (i % 5 == 3)
					std::cout << "\033[1;33m> \033[0m";
				else if (i % 5 == 4)
					std::cout << "\033[1;34m> \033[0m";
				else if (i % 5 == 0)
					std::cout << "\033[1;35m> \033[0m";
			}
			std::cout << floor << ": " << node->value->first << " " << node->height << std::endl;
			browse_tree(node->right, 'r', depth + 1);
			browse_tree(node->left, 'l', depth + 1);
		}
	*/

	private :

		key_compare										_compare;
		value_compare									_comp;
		allocator_type									_alloc;
		size_type										_size;
		avl<value_type>									*_root;
		avl<value_type>									*_end_node;
		alloc_avl										_alloc_avl;

		// binary tree function

		int			get_height(avl<value_type> *node)
		{
			if (!node)
				return (0);
			return (node->height);
		}

		int			max_height(avl<value_type> *first, avl<value_type> *second)
		{
			int		first_height;
			int		second_height;

			if (!first || first->end)
				first_height = 0;
			else
				first_height = first->height;
			if (!second || second->end)
				second_height = 0;
			else
				second_height = second->height;

			if (first_height > second_height)
				return (first_height);
			else
				return (second_height);
		}

		void		right_rotate(avl<value_type> *y)
		{
			avl<value_type>		*y_parent;
			avl<value_type>		*x;

			y_parent = y->parent;
			x = y->left;
			y->height = max_height(y->right, x->right) + 1;
			x->height = max_height(y, x->left) + 1;

			y->parent = x;
			y->left = x->right;
			if (x->right)
				y->left->parent = y;
			x->parent = y_parent;
			x->right = y;
			if (y_parent)
			{
				if (y_parent->right == y)
					y_parent->right = x;
				else
					y_parent->left = x;
			}
			if (!x->parent)
				this->_root = x;
		}

		void		left_rotate(avl<value_type> *x)
		{
			avl<value_type>		*x_parent;
			avl<value_type>		*y;

			x_parent = x->parent;
			y = x->right;

			// update height
			x->height = max_height(x->left, y->left) + 1;
			y->height = max_height(x, y->right) + 1;

			x->parent = y;
			x->right = y->left;
			if (y->left)
				x->right->parent = x;
			y->parent = x_parent;
			y->left = x;
			if (x_parent)
			{
				if (x_parent->left == x)
					x_parent->left = y;
				else
					x_parent->right = y;
			}
			if (!y->parent)
				this->_root = y;
		}

		void		balance_left_cases(avl<value_type> *last_inserted, avl<value_type> *first_unbalanced)
		{
			avl<value_type>		*subtree_root;

			if (this->_compare(last_inserted->value->first, first_unbalanced->left->value->first) ||
					(!this->_compare(last_inserted->value->first, first_unbalanced->left->value->first)
					 && !this->_compare(first_unbalanced->left->value->first, last_inserted->value->first)))
			{
				// left left case
				subtree_root = first_unbalanced->left;
				right_rotate(first_unbalanced);
				update_height(subtree_root, true);
			}
			else
			{
				// left right case
				subtree_root = first_unbalanced->left->right;
				left_rotate(first_unbalanced->left);
				right_rotate(first_unbalanced);
				update_height(subtree_root, true);
			}
		}

		void		balance_right_cases(avl<value_type> *last_inserted, avl<value_type> *first_unbalanced)
		{
			avl<value_type>		*subtree_root;

			if (this->_compare(last_inserted->value->first, first_unbalanced->right->value->first) ||
					(!this->_compare(last_inserted->value->first, first_unbalanced->right->value->first)
					 && !this->_compare(first_unbalanced->right->value->first, last_inserted->value->first)))
			{
				// right left case
				subtree_root = first_unbalanced->right->left;
				right_rotate(first_unbalanced->right);
				left_rotate(first_unbalanced);
				update_height(subtree_root, true);
			}
			else
			{
				// right right case
				subtree_root = first_unbalanced->right;
				left_rotate(first_unbalanced);
				update_height(subtree_root, true);
			}
		}

		void		balance(avl<value_type> *last_inserted)
		{
			avl<value_type>		*first_unbalanced;
			int					size_difference;

			first_unbalanced = last_inserted;
			while (first_unbalanced != NULL)
			{
				size_difference = get_height(first_unbalanced->left) - get_height(first_unbalanced->right);
				if (size_difference <= -2 || size_difference >= 2)
				{
					if (size_difference >= 2)
						balance_left_cases(last_inserted, first_unbalanced);
					else
						balance_right_cases(last_inserted, first_unbalanced);
					break ;
				}
				first_unbalanced = first_unbalanced->parent;
			}
		}

		void		balance_left_cases_deletion(avl<value_type> *first_unbalanced)
		{
			avl<value_type>		*subtree_root;

			if (get_height(first_unbalanced->left->left) >= get_height(first_unbalanced->left->right))
			{
				// left left case
				subtree_root = first_unbalanced->left;
				right_rotate(first_unbalanced);
				update_height(subtree_root, true);
			}
			else
			{
				// left right case
				subtree_root = first_unbalanced->left->right;
				left_rotate(first_unbalanced->left);
				right_rotate(first_unbalanced);
				update_height(subtree_root, true);
			}
		}

		void		balance_right_cases_deletion(avl<value_type> *first_unbalanced)
		{
			avl<value_type>		*subtree_root;

			if (get_height(first_unbalanced->right->left) >= get_height(first_unbalanced->right->right))
			{
				// right left case
				subtree_root = first_unbalanced->right->left;
				right_rotate(first_unbalanced->right);
				left_rotate(first_unbalanced);
				update_height(subtree_root, true);
			}
			else
			{
				// right right case
				subtree_root = first_unbalanced->right;
				left_rotate(first_unbalanced);
				update_height(subtree_root, true);
			}
		}

		void		balance_deletion(avl<value_type> *deleted_substitute)
		{
			avl<value_type>		*first_unbalanced;
			int					size_difference;

			first_unbalanced = deleted_substitute;
			while (first_unbalanced != NULL)
			{
				size_difference = get_height(first_unbalanced->left) - get_height(first_unbalanced->right);
				if (size_difference <= -2 || size_difference >= 2)
				{
					if (size_difference >= 2)
						balance_left_cases_deletion(first_unbalanced);
					else
						balance_right_cases_deletion(first_unbalanced);
					break ;
				}
				first_unbalanced = first_unbalanced->parent;
			}
		}

		void	update_height_after_insertion(avl<value_type> *node)
		{
			int		child_height;

			child_height = node->height;
			node = node->parent;
			while (node)
			{
				if (node->height <= child_height)
					node->height = child_height + 1;
				else
					break ;
				child_height = node->height;
				node = node->parent;
			}
		}

		void	update_height(avl<value_type> *node, bool height_node_updated)
		{
			int		child_height;
			avl<value_type>		*prev_node;

			if (node)
			{
				if (height_node_updated)
					child_height = node->height;
				else
					child_height = 0;
				prev_node = node;
				node = node->parent;
			}
			while (node)
			{
				if (this->_compare(node->value->first, prev_node->value->first))
				{
					if (node->left && node->left->height != node->height - 1)
					{
						if (node->height != child_height + 1)
						{
							node->height = child_height + 1;
						}
						else
							break ;
					}
					else if (!height_node_updated)
					{
						node->height = child_height + 1;
					}
				}
				else
				{
					if (node->right && node->right->height != node->height - 1)
					{
						if (node->height != child_height + 1)
							node->height = child_height + 1;
						else
							break ;
					}
				}
				child_height = node->height;
				prev_node = node;
				node = node->parent;
			}
		}

		avl<value_type>				*create_node(value_type node_value)
		{
			avl<value_type>			*new_node;
			value_type				*node_value_ptr;

			node_value_ptr = this->_alloc.allocate(1);
			this->_alloc.construct(node_value_ptr, node_value);

			new_node = this->_alloc_avl.allocate(1);
			this->_alloc_avl.construct(new_node, node_value_ptr);
			return (new_node);
		}

		ft::pair<iterator, bool>		insertion(avl<value_type> **tree, value_type node_value, avl<value_type> *parent)
		{
			bool							end_node;
			ft::pair<iterator, bool>		ret;

			if (!(*tree) || (*tree && *tree == this->_end_node))
			{
				if ((*tree) == this->_end_node)
					end_node = true;
				else
					end_node = false;
				(*tree) = this->create_node(node_value);
				(*tree)->parent = parent;
				update_height_after_insertion(*tree);
				if (end_node)
				{
					(*tree)->right = this->_end_node;
					this->_end_node->parent = *tree;
				}
				ret.first = iterator(*tree);
				ret.second = true;
				balance(*tree);
				return (ret);
			}
			else if (!this->_compare((*tree)->value->first, node_value.first)
					&& !this->_compare(node_value.first, (*tree)->value->first))
			{
				ret.first = iterator(*tree);
				ret.second = false;
				return (ret);
			}
			else if (!this->_compare((*tree)->value->first, node_value.first))
				return (this->insertion(&(*tree)->left, node_value, *tree));
			else
				return (this->insertion(&(*tree)->right, node_value, *tree));
		}

		void						delete_node(avl<value_type> *node)
		{
			this->_alloc.destroy(node->value);
			this->_alloc.deallocate(node->value, 1);

			this->_alloc_avl.destroy(node);
			this->_alloc_avl.deallocate(node, 1);
		}


		bool				deletion(iterator node)
		{
			if (!node.node->left && (!node.node->right ||
				(node.node->right && node.node->right->end)))
			{
				//no child
				if (node.node->parent)
				{
					if (this->_compare(node->first,
								node.node->parent->value->first))
						node.node->parent->left = NULL;
					else
					{
						if (node.node->right)
						{
							node.node->parent->right = this->_end_node;
							this->_end_node->parent = node.node->parent;
						}
						else
							node.node->parent->right = NULL;
					}
					update_height(node.node, false);
					balance_deletion(node.node->parent);
				}
				else
				{
					this->_end_node->parent = NULL;
					this->_root = this->_end_node;
				}
			}
			else if (node.node->left && (!node.node->right ||
						(node.node->right && node.node->right->end)))
			{
				// only left child
				iterator		prev;

				prev = node;
				--prev;
				if (node.node->parent)
				{
					if (this->_compare(node->first,
								node.node->parent->value->first))
						node.node->parent->left = node.node->left;
					else
						node.node->parent->right = node.node->left;
				}
				node.node->left->parent = node.node->parent;
				prev.node->right = node.node->right;
				if (node.node->right)
				{
					//replace end_node
					node.node->right->parent = prev.node;
				}
				if (!node.node->parent)
					this->_root = node.node->left;
				update_height(node.node->left, true);
				this->balance_deletion(node.node->left);
			}
			else if (node.node->right && (!node.node->left
					|| (node.node->left && node.node->left->end)))
			{
				// only right child
				if (node.node->parent)
				{
					if (this->_compare(node->first,
								node.node->parent->value->first))
						node.node->parent->left = node.node->right;
					else
						node.node->parent->right = node.node->right;
				}
				node.node->right->parent = node.node->parent;
				if (!node.node->parent)
					this->_root = node.node->right;
				update_height(node.node->right, true);
				this->balance_deletion(node.node->right);
			}
			else
			{
				iterator		next;

				next = node;
				next++;
				if (node.node->parent)
				{
					if (this->_compare(node->first,
								node.node->parent->value->first))
						node.node->parent->left = next.node;
					else
						node.node->parent->right = next.node;
				}
				next.node->left = node.node->left;
				if (node.node->right != next.node)
				{
					next.node->parent->left = next.node->right;
					if (next.node->right)
						next.node->right->parent = next.node->parent;
					node.node->right->parent = next.node;
					next.node->right = node.node->right;
				}
				next.node->parent = node.node->parent;
				node.node->left->parent = next.node;
				if (!node.node->parent)
				{
					this->_root = next.node;
				}
				update_height(next.node, true);
				this->balance_deletion(next.node);
			}
			delete_node(node.node);
			return (true);
		}

	// non-member overloads

	friend bool operator==( const map &lhs, const map &rhs )
	{
		return ((!ft::lexicographical_compare(lhs.begin(), lhs.end(), 
						rhs.begin(), rhs.end())
					&& !ft::lexicographical_compare(rhs.begin(), rhs.end(), 
						lhs.begin(), lhs.end())));
	}

	friend bool operator!=( const map &lhs, const map &rhs )
	{
		return (!(lhs == rhs));
	}

	friend bool operator<( const map &lhs, const map &rhs )
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
					rhs.begin(), rhs.end()));
	}

	friend bool operator>( const map &lhs, const map &rhs )
	{
		return (rhs < lhs);
	}

	friend bool operator<=( const map &lhs, const map &rhs )
	{
		return ((lhs < rhs) || (lhs == rhs));
	}

	friend bool operator>=( const map &lhs, const map &rhs )
	{
		return (!(lhs < rhs));
	}


	friend void	swap(map &x, map &y)
	{
		x.swap(y);
	}

	};

}

#endif
