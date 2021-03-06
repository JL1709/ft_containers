#ifndef FT_TREE_HPP
#define FT_TREE_HPP

#include <memory>
#include "ft_iterator.hpp"
#include "ft_utility.hpp"
#include "ft_algorithm.hpp"

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
class rb_tree
{
	protected:
		typedef typename std::allocator<void>::pointer void_pointer; 

		enum color_type {red, black};
		struct Node
		{
			color_type   color;
			void_pointer parent_link;
			void_pointer left_link;
			void_pointer right_link;
			Value        value_field;
			
		};
		static typename Allocator::template rebind<Node>::other Node_allocator;
		static std::allocator<Value> value_allocator;

	public:
		typedef Key													key_type;
		typedef Value												value_type;
		typedef typename std::allocator<Value>::pointer				pointer;
		typedef typename std::allocator<Value>::const_pointer		const_pointer;
		typedef typename std::allocator<Value>::reference			reference;
		typedef typename std::allocator<Value>::const_reference		const_reference;
		typedef typename Allocator::template rebind<Node>::other	Node_allocator_type;
		typedef typename std::allocator<Node>::pointer				link_type;
		typedef typename std::allocator<Node>::size_type			size_type;
		typedef typename std::allocator<Node>::difference_type		difference_type;

	protected:
		template <class T>
		const T& max(const T& a, const T& b) {return  a < b ? b : a;}
	    size_type init_page_size() {return max(size_type(1), size_type(4096/sizeof(Key)));}
		size_type buffer_size() {return init_page_size();}
		struct Node_buffer;
		friend struct Node_buffer;
		struct Node_buffer {
			void_pointer next_buffer;
			link_type buffer;
		};
	public:
		typedef typename std::allocator<Node_buffer> buffer_allocator_type;
		typedef typename std::allocator<Node_buffer>::pointer buffer_pointer;   

	protected:
		static typename std::allocator<Node_buffer> buffer_allocator;
		static buffer_pointer buffer_list;
		static link_type free_list;
		static link_type next_avail;
		static link_type last;
		void add_new_buffer() {
			buffer_pointer tmp = buffer_allocator.allocate((size_type)1);
			tmp->buffer = Node_allocator.allocate(buffer_size());
			tmp->next_buffer = buffer_list;
			buffer_list = tmp;
			next_avail = buffer_list->buffer;
			last = next_avail + buffer_size();
		}
		static size_type number_of_trees;
		void deallocate_buffers();
		link_type get_node()
		{
			link_type tmp = free_list;
			return free_list ? 
				(free_list = (link_type)(free_list->right_link), tmp) 
					: (next_avail == last ? (add_new_buffer(), next_avail++) 
					: next_avail++);
		}
		void put_node(link_type p)
		{
			p->right_link = free_list;
			free_list = p;
		}

	protected:
		link_type header;
		link_type& root() { return parent(header); }
		link_type& root() const { return parent(header); }
		link_type& leftmost() { return left(header); }
		link_type& leftmost() const { return left(header); }
		link_type& rightmost() { return right(header); }
		link_type& rightmost() const { return right(header); }
		size_type node_count; // keeps track of size of tree
		bool insert_always;   // checks whether an element already in the tree is inserted again

		Compare key_compare;
		static link_type NIL;
		static link_type&										left(link_type x) {return (link_type&)((*x).left_link);}
		static link_type&										right(link_type x) {return (link_type&)((*x).right_link);}
		static link_type&										parent(link_type x) {return (link_type&)((*x).parent_link);}
		static reference										value(link_type x) { return (*x).value_field; }
		static typename std::allocator<Key>::const_reference	key(link_type x) {return KeyOfValue()(value(x));}
		static color_type&										color(link_type x) {return (color_type&)(*x).color;}
		static link_type										minimum(link_type x) {while (left(x) != NIL) x = left(x); return x;}
		static link_type										maximum(link_type x) {while (right(x) != NIL) x = right(x); return x;}

	public:
		class iterator;
		friend class iterator;
		class const_iterator;
		friend class const_iterator;
		class iterator : public ft::bidirectional_iterator<Value, difference_type>
		{
			friend class rb_tree<Key, Value, KeyOfValue, Compare, Allocator>;
			friend class const_iterator;
			protected:
				link_type node;
				iterator(link_type x) : node(x) {}
			public:
				iterator() {}
				iterator(const iterator& x) : node(x.node) {}
				bool operator==(const iterator& y) { return node == y.node; }
				bool operator==(const const_iterator& y) const { return node == y.node; }
				bool operator!=(const iterator& y) const { return node != y.node; }
				reference operator*() { return value(node); }
				reference operator*() const { return value(node); }
				pointer operator->() { return &(value(node));}
				pointer operator->() const { return &(value(node));}
				iterator& operator++()
				{
					if (right(node) != NIL)
					{
						node = right(node);
						while (left(node) != NIL)
							node = left(node);
					} 
					else 
					{
						link_type y = parent(node);
						while (node == right(y))
						{
							node = y;
							y = parent(y);
						}
						if (right(node) != y)
							node = y;
					}
					return *this;
				}
				iterator operator++(int) 
				{
					iterator tmp = *this;
					++*this;
					return tmp;
				}
				iterator& operator--()
				{
					if (color(node) == red && parent(parent(node)) == node)  
						node = right(node);
					else if (left(node) != NIL)
					{
						link_type y = left(node);
						while (right(y) != NIL)
							y = right(y);
						node = y;
					} 
					else
					{
						link_type y = parent(node);
						while (node == left(y)) {
							node = y;
							y = parent(y);
						}
						node = y;
					}
					return *this;
				}
				iterator operator--(int)
				{
					iterator tmp = *this;
					--*this;
					return tmp;
				}
		};
		class const_iterator : public ft::bidirectional_iterator<Value, difference_type>
		{
			friend class rb_tree<Key, Value, KeyOfValue, Compare, Allocator>;
			friend class iterator;
			protected:
				link_type node;
				const_iterator(link_type x) : node(x) {}
			public:
				const_iterator() {}
				const_iterator(const iterator& x) : node(x.node) {}
				bool operator==(const const_iterator& y) const {return node == y.node;}
				bool operator!=(const const_iterator& y) const {return node != y.node;}
				const_reference operator*() const { return value(node); }
				const_reference operator*() { return value(node); }
				const_pointer operator->() { return &(value(node)); }
				const_pointer operator->() const { return &(value(node)); }
				const_iterator& operator++()
				{
					if (right(node) != NIL)
					{
						node = right(node);
						while (left(node) != NIL)
							node = left(node);
					}
					else
					{
						link_type y = parent(node);
						while (node == right(y))
						{
							node = y;
							y = parent(y);
						}
						if (right(node) != y)
							node = y;
					}
					return *this;
				}
				const_iterator operator++(int)
				{
					const_iterator tmp = *this;
					++*this;
					return tmp;
				}
				const_iterator& operator--()
				{
					if (color(node) == red && parent(parent(node)) == node)  
						node = right(node);
					else if (left(node) != NIL) {
						link_type y = left(node);
						while (right(y) != NIL)
							y = right(y);
						node = y;
					} else {
						link_type y = parent(node);
						while (node == left(y)) {
							node = y;
							y = parent(y);
						}
						node = y;
					}
					return *this;
				}
				const_iterator operator--(int)
				{
					const_iterator tmp = *this;
					--*this;
					return tmp;
				}
		};

		typedef ft::reverse_bidirectional_iterator<iterator, value_type, reference, pointer, difference_type> 					reverse_iterator; 
    	typedef ft::reverse_bidirectional_iterator<const_iterator, value_type, const_reference, const_pointer, difference_type> const_reverse_iterator;
	
	private:
		iterator _insert(link_type x, link_type y, const value_type& v);
		link_type _copy(link_type x, link_type p);
		void _erase(link_type x);
		void init()
		{
			++number_of_trees;
			if (NIL == 0)
			{
				NIL = get_node();
				color(NIL) = black;
				parent(NIL) = 0;
				left(NIL) = 0;
				right(NIL) = 0;
			}
			header = get_node();
			color(header) = red;
			root() = NIL;
			leftmost() = header;
			rightmost() = header;
		}
	
	public:	
		rb_tree(const Compare& comp = Compare(), bool always = false) : node_count(0), insert_always(always), key_compare(comp) 
		{
			init();
		}
		rb_tree(const value_type* first, const value_type* last, const Compare& comp = Compare(), bool always = false) : node_count(0), insert_always(always), key_compare(comp)
		{ 
			init();
			insert(first, last);
		}
		rb_tree(const rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& x, bool always = false) : node_count(x.node_count), insert_always(always), key_compare(x.key_compare)
		{ 
			++number_of_trees;
			header = get_node();
			color(header) = red;
			root() = _copy(x.root(), header);
			if (root() == NIL)
			{
				leftmost() = header;
				rightmost() = header;
			}
			else
			{
				leftmost() = minimum(root());
				rightmost() = maximum(root());
			}
		}
		~rb_tree() 
		{
			erase(begin(), end());
			put_node(header);
			if (--number_of_trees == 0) {
				put_node(NIL);
				NIL = 0;
				deallocate_buffers();
				free_list = 0;    
				next_avail = 0;
				last = 0;
			}
		}
		rb_tree<Key, Value, KeyOfValue, Compare, Allocator> &operator=(const rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& x);

	// accessors:

		iterator				begin() {return leftmost();}
		iterator				end() {return header;}
		const_iterator			begin() const {return leftmost();}
		const_iterator			end() const {return header;}
		reverse_iterator		rbegin() {return reverse_iterator(end());}
		reverse_iterator		rend() {return reverse_iterator(begin());}
		const_reverse_iterator	rbegin() const {return const_reverse_iterator(end());}
		const_reverse_iterator	rend() const {return const_reverse_iterator(begin());}

		Compare		key_comp() const {return key_compare;}
		bool		empty() const {return node_count == 0;}
		size_type	size() const {return node_count;}
		size_type	max_size() const {return Node_allocator.max_size();}
		void		swap(rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& t)
		{
			ft::swap(header, t.header);
			ft::swap(node_count, t.node_count);
			ft::swap(insert_always, t.insert_always);
			ft::swap(key_compare, t.key_compare);
		}

	// clear/insert/erase

		void clear(void);
		
		typedef  ft::pair<iterator, bool> pair_iterator_bool; 

		pair_iterator_bool	insert(const value_type& x);
		iterator			insert(const_iterator position, const value_type& x);
		void				insert(const_iterator first, const_iterator last);
		void				insert(const value_type* first, const value_type* last);

		void		erase(const_iterator position);
		size_type	erase(const key_type& x);
		void		erase(const_iterator first, const_iterator last);
		void		erase(const key_type* first, const key_type* last);

	// set operations:

		iterator		find(const key_type& x);
		const_iterator	find(const key_type& x) const;

		size_type count(const key_type& x) const;

		iterator		lower_bound(const key_type& x);
		const_iterator	lower_bound(const key_type& x) const;
		iterator		upper_bound(const key_type& x);
		const_iterator	upper_bound(const key_type& x) const;

		typedef ft::pair<iterator, iterator> pair_iterator_iterator; 
		pair_iterator_iterator		equal_range(const key_type& x);
		typedef  ft::pair<const_iterator, const_iterator> pair_citerator_citerator;
		pair_citerator_citerator	equal_range(const key_type& x) const;

		void rotate_left(link_type x);
		void rotate_right(link_type x);
}; // end of class rb_tree


template <class BidirectionalIterator, class Distance>
void __distance(BidirectionalIterator first, BidirectionalIterator last, Distance& n, ft::bidirectional_iterator_tag)
{
	 while (first != last) { ++first; ++n; }
}

template <class InputIterator, class Distance>
 void distance(InputIterator first, InputIterator last, Distance& n)
{
    __distance(first, last, n, ft::bidirectional_iterator_tag());
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::buffer_pointer rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::buffer_list = 0;

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::link_type rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::free_list = 0;

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::link_type rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::next_avail = 0;

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::link_type rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::last = 0;

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::size_type rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::number_of_trees = 0;

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::Node_allocator_type rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::Node_allocator;

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename std::allocator<Value> rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::value_allocator;

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::buffer_allocator_type rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::buffer_allocator;

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::link_type rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::NIL = 0;

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
void rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::deallocate_buffers() 
{
	while (buffer_list) 
	{
		buffer_pointer tmp = buffer_list;
		buffer_list = (buffer_pointer)(buffer_list->next_buffer);
		Node_allocator.deallocate(tmp->buffer, this->size());
		buffer_allocator.deallocate(tmp, this->size());
	}
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
 bool operator==(const rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& x, const rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& y)
{
	return x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin());
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
 bool operator<(const rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& x, const rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& y)
{
	return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::operator=(const rb_tree<Key, Value, KeyOfValue, Compare, Allocator>& x)
{
	if (this != &x)
	{
		// can't be done as in list because Key may be a constant type
		erase(begin(), end());
		root() = _copy(x.root(), header);
		if (root() == NIL)
		{
			leftmost() = header;
			rightmost() = header;
		} 
		else
		{
			leftmost() = minimum(root());
			rightmost() = maximum(root());
		}
		node_count = x.node_count;
	}
	return *this;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::_insert(link_type x, link_type y, const Value& v)
{
	++node_count;
	link_type z = get_node();
	value_allocator.construct(value_allocator.address(value(z)), v);
	if (y == header || x != NIL || key_compare(KeyOfValue()(v), key(y)))
	{
		left(y) = z;  // also makes leftmost() = z when y == header
		if (y == header)
		{
			root() = z;
			rightmost() = z;
		} 
		else if (y == leftmost())
			leftmost() = z;   // maintain leftmost() pointing to minimum node
	} 
	else
	{
		right(y) = z;
		if (y == rightmost())
			rightmost() = z;   // maintain rightmost() pointing to maximum node
	}
	parent(z) = y;
	left(z) = NIL;
	right(z) = NIL;
	x = z;  // recolor and rebalance the tree
	color(x) = red;
	while (x != root() && color(parent(x)) == red)
	{
		if (parent(x) == left(parent(parent(x))))
		{
			y = right(parent(parent(x)));
			if (color(y) == red)
			{
				color(parent(x)) = black;
				color(y) = black;
				color(parent(parent(x))) = red;
				x = parent(parent(x));
			}
			else
			{
				if (x == right(parent(x)))
				{
					x = parent(x);
					rotate_left(x);
				}
				color(parent(x)) = black;
				color(parent(parent(x))) = red;
				rotate_right(parent(parent(x)));
			}
		}
		else
		{
			y = left(parent(parent(x)));
			if (color(y) == red)
			{
				color(parent(x)) = black;
				color(y) = black;
				color(parent(parent(x))) = red;
				x = parent(parent(x));
			}
			else
			{
				if (x == left(parent(x)))
				{
					x = parent(x);
					rotate_right(x);
				}
				color(parent(x)) = black;
				color(parent(parent(x))) = red;
				rotate_left(parent(parent(x)));
			}
		}
	}
	color(root()) = black;
	return iterator(z);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
void rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::clear(void)
{
	erase(begin(), end());
}


template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::pair_iterator_bool rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::insert(const Value& v)
{
	link_type y = header;
	link_type x = root();
	bool comp = true;
	while (x != NIL)
	{
		y = x;
		comp = key_compare(KeyOfValue()(v), key(x));
		x = comp ? left(x) : right(x);
	}
	if (insert_always)
		return pair_iterator_bool(_insert(x, y, v), true);
	iterator j = iterator(y);
	if (comp)
	{
		if (j == begin())
			return pair_iterator_bool(_insert(x, y, v), true);
		else
			--j;
	}
	if (key_compare(key(j.node), KeyOfValue()(v)))
		return pair_iterator_bool(_insert(x, y, v), true);
	return pair_iterator_bool(j, false);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::insert(const_iterator position, const Value& v)
{
	if (position == const_iterator(begin()))
	{
		if (size() > 0 && key_compare(KeyOfValue()(v), key(position.node)))
			return _insert(position.node, position.node, v);
			// first argument just needs to be non-NIL 
		else
			return insert(v).first;
	}
	else if (position == const_iterator(end()))
	{
		if (key_compare(key(rightmost()), KeyOfValue()(v)))
			return _insert(NIL, rightmost(), v);
		else
			return insert(v).first;
	}
	else
	{
		const_iterator before = --position;
		if (key_compare(key(before.node), KeyOfValue()(v)) && key_compare(KeyOfValue()(v), key(position.node)))
		{
			if (right(before.node) == NIL)
				return _insert(NIL, before.node, v); 
			else
				return _insert(position.node, position.node, v);
				// first argument just needs to be non-NIL 
		}
		else
			return insert(v).first;
	}
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
void rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::insert(const_iterator first, const_iterator last)
{
	while (first != last) insert(*first++);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
void rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::insert(const Value* first, const Value* last)
{
	while (first != last) insert(*first++);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
void rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::erase(const_iterator position) 
{
	link_type z = position.node;
	link_type y = z;
	link_type x;
	if (left(y) == NIL)
		x = right(y);
	else
		if (right(y) == NIL) 
			x = left(y);
		else
		{
			y = right(y);
			while (left(y) != NIL)
				y = left(y);
			x = right(y);
		}
	if (y != z)  // relink y in place of z
	{
		parent(left(z)) = y; 
		left(y) = left(z);
		if (y != right(z)) {
			parent(x) = parent(y); // possibly x == NIL
			left(parent(y)) = x;   // y must be a left child
			right(y) = right(z);
			parent(right(z)) = y;
		} else
			parent(x) = y;  // needed in case x == NIL
		if (root() == z)
			root() = y;
		else if (left(parent(z)) == z)
			left(parent(z)) = y;
		else 
			right(parent(z)) = y;
		parent(y) = parent(z);
		ft::swap(color(y), color(z));
		y = z;
						// y points to node to be actually deleted
	}
	else 
	{  
		parent(x) = parent(y);   // possibly x == NIL
		if (root() == z)
			root() = x;
		else 
			if (left(parent(z)) == z)
				left(parent(z)) = x;
			else
				right(parent(z)) = x;
		if (leftmost() == z)
		{
			if (right(z) == NIL)  // left(z) must be NIL also
				leftmost() = parent(z);
				// makes leftmost() == header if z == root()
			else 
				leftmost() = minimum(x);
		}
		if (rightmost() == z)
		{
			if (left(z) == NIL) // right(z) must be NIL also
				rightmost() = parent(z);  
				// makes rightmost() == header if z == root()
			else  // x == left(z)
				rightmost() = maximum(x);
		}
	}
	if (color(y) != red)
	{
		while (x != root() && color(x) == black)
			if (x == left(parent(x))) {
				link_type w = right(parent(x));
				if (color(w) == red) {
					color(w) = black;
					color(parent(x)) = red;
					rotate_left(parent(x));
					w = right(parent(x));
				}
				if (color(left(w)) == black && color(right(w)) == black) {
					color(w) = red;
					x = parent(x);
				} else {
					if (color(right(w)) == black) {
						color(left(w)) = black;
						color(w) = red;
						rotate_right(w);
						w = right(parent(x));
					}
					color(w) = color(parent(x));
					color(parent(x)) = black;
					color(right(w)) = black;
					rotate_left(parent(x));
					break;
				}
			}
			else // same as then clause with "right" and "left" exchanged
			{
				link_type w = left(parent(x));
				if (color(w) == red) {
					color(w) = black;
					color(parent(x)) = red;
					rotate_right(parent(x));
					w = left(parent(x));
				}
				if (color(right(w)) == black && color(left(w)) == black)
				{
					color(w) = red;
					x = parent(x);
				}
				else
				{
					if (color(left(w)) == black)
					{
						color(right(w)) = black;
						color(w) = red;
						rotate_left(w);
						w = left(parent(x));
					}
					color(w) = color(parent(x));
					color(parent(x)) = black;
					color(left(w)) = black;
					rotate_right(parent(x));
					break;
				}
			}
		color(x) = black;
	}
	value_allocator.destroy(&(value(y)));
	put_node(y);
	--node_count;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::size_type rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::erase(const Key& x)
{
	pair_iterator_iterator p = equal_range(x);
	size_type n = 0;
	distance(p.first, p.second, n);
	erase(p.first, p.second);
	return n;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::link_type rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::_copy(link_type x, link_type p)
{
	// structural copy
	link_type r = x;
	while (x != NIL)
	{
		link_type y = get_node();
		if (r == x) r = y;  // save for return value
		value_allocator.construct(value_allocator.address(value(y)), value(x));
		// value_allocator.construct(&(value(y)), &(value(x)));
		left(p) = y;
		parent(y) = p;
		color(y) = color(x);
		right(y) = _copy(right(x), y);
		p = y;
		x = left(x);
	}
	left(p) = NIL;
	return r;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
void rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::_erase(link_type x) {
	while (x != NIL) {
	_erase(right(x));
	link_type y = left(x);
		value_allocator.destroy(&value(x));
	put_node(x);
	x = y;
	}
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
void rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::erase(const_iterator first, const_iterator last)
{
	if (first == begin() && last == end() && node_count != 0)
	{
		_erase(root());
		leftmost() = header;
		root() = NIL;
		rightmost() = header;
		node_count = 0;
	}
	else
		while (first != last) erase(first++);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
void rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::erase(const Key* first, const Key* last)
{
	while (first != last) erase(*first++);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::find(const Key& k)
{
	link_type y = header; /* Last node which is not less than k. */
	link_type x = root(); /* Current node. */
	while (x != NIL)
	{
		if (!key_compare(key(x), k))
			y = x, x = left(x);
		else
			x = right(x);
	}
	iterator j = iterator(y);
	return (j == end() || key_compare(k, key(j.node))) ? end() : j;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::const_iterator rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::find(const Key& k) const
{
	link_type y = header; /* Last node which is not less than k. */
	link_type x = root(); /* Current node. */
	while (x != NIL)
	{
		if (!key_compare(key(x), k))
			y = x, x = left(x);
		else
			x = right(x);
	}
	const_iterator j = const_iterator(y);   
	return (j == end() || key_compare(k, key(j.node))) ? end() : j;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::size_type rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::count(const Key& k) const 
{
	ft::pair<const_iterator, const_iterator> p = equal_range(k);
	size_type n = 0;
	distance(p.first, p.second, n);
	return n;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::lower_bound(const Key& k)
{
	link_type y = header; /* Last node which is not less than k. */
	link_type x = root(); /* Current node. */
	while (x != NIL)
	{
		if (!key_compare(key(x), k))
			y = x, x = left(x);
		else
			x = right(x);
	}
	return iterator(y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::const_iterator rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::lower_bound(const Key& k) const
{
	link_type y = header; /* Last node which is not less than k. */
	link_type x = root(); /* Current node. */
	while (x != NIL)
	{
		if (!key_compare(key(x), k))
			y = x, x = left(x);
		else
			x = right(x);
	}
	return const_iterator(y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::iterator rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::upper_bound(const Key& k)
{
	link_type y = header; /* Last node which is greater than k. */
	link_type x = root(); /* Current node. */
	while (x != NIL)
	{
		if (key_compare(k, key(x)))
			y = x, x = left(x);
		else
			x = right(x);
	}
	return iterator(y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::const_iterator rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::upper_bound(const Key& k) const 
{
	link_type y = header; /* Last node which is greater than k. */
	link_type x = root(); /* Current node. */
	while (x != NIL)
	{
		if (key_compare(k, key(x)))
			y = x, x = left(x);
		else
			x = right(x);
	}
	return const_iterator(y);
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::pair_iterator_iterator rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::equal_range(const Key& k)
{
	return pair_iterator_iterator(lower_bound(k), upper_bound(k));
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::pair_citerator_citerator rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::equal_range(const Key& k) const
{
	return pair_citerator_citerator(lower_bound(k), upper_bound(k));
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
void rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::rotate_left(link_type x)
{
	link_type y = right(x);
	right(x) = left(y);
	if (left(y) != NIL)
		parent(left(y)) = x;
	parent(y) = parent(x);
	if (x == root())
		root() = y;
	else if (x == left(parent(x)))
		left(parent(x)) = y;
	else
		right(parent(x)) = y;
	left(y) = x;
	parent(x) = y;
}

template <class Key, class Value, class KeyOfValue, class Compare, class Allocator>
void rb_tree<Key, Value, KeyOfValue, Compare, Allocator>::rotate_right(link_type x)
{
	link_type y = left(x);
	left(x) = right(y);
	if (right(y) != NIL)
		parent(right(y)) = x;
	parent(y) = parent(x);
	if (x == root())
		root() = y;
	else if (x == right(parent(x)))
		right(parent(x)) = y;
	else
		left(parent(x)) = y;
	right(y) = x;
	parent(x) = y;
}

#endif