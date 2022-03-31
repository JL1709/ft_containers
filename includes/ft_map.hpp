/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 11:16:01 by julian            #+#    #+#             */
/*   Updated: 2022/03/31 12:00:52 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <memory>
#include <cstddef>
#include "ft_utility.hpp"
#include "ft_iterator.hpp"
#include "ft_bidirectional_iterator.hpp"
#include "ft_tree.hpp"
#include "ft_type_traits.hpp"

template <class Arg, class Result>
struct unary_function {
    typedef Arg argument_type;
    typedef Result result_type;
};


template <class T, class U>
struct select1st : public unary_function<T, U> {
    const U& operator()(const T& x) const { return x.first; }
};

namespace ft
{
	template < 
		class Key,													// map::key_type
		class T,													// map::mapped_type
		class Compare = std::less<Key>,								// map::key_compare
		class Allocator = std::allocator<ft::pair<const Key,T> >	// map::allocator_type
		>
	class map
	{
		public:
/* MEMBER TYPES ------------------------------------------------------------- */
			typedef Key 											key_type;
			typedef T 												mapped_type;
			typedef ft::pair<const Key, T> 							value_type;
			typedef std::size_t 									size_type;
			typedef std::ptrdiff_t 									difference_type;
			typedef Compare 										key_compare;
			typedef Allocator 										allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef typename rb_tree<key_type, value_type, select1st<value_type, key_type>, key_compare, allocator_type>::iterator					iterator;
			typedef typename rb_tree<key_type, value_type, select1st<value_type, key_type>, key_compare, allocator_type>::const_iterator			const_iterator;
			typedef typename rb_tree<key_type, value_type, select1st<value_type, key_type>, key_compare, allocator_type>::reverse_iterator			reverse_iterator;
			typedef typename rb_tree<key_type, value_type, select1st<value_type, key_type>, key_compare, allocator_type>::const_reverse_iterator	const_reverse_iterator;

/* MEMBER Objects------------------------------------------------------------ */
		private:
			typedef rb_tree<key_type, value_type, select1st<value_type, key_type>, key_compare, allocator_type> RBTree;
			RBTree	t;
			Allocator _alloc;
			
		public:
/* MEMBER CLASSES------------------------------------------------------------ */

			class value_compare : std::binary_function<value_type, value_type, bool>
			{
				friend class map;
				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {};
				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
					bool operator()(const value_type& lhs, const value_type& rhs) const {return comp(lhs.first, rhs.first);}
			};

/* MEMBER FUNCTIONS --------------------------------------------------------- */

	// constructor, destructor, assignation operator, allocator
	
			explicit map (const key_compare& comp = key_compare(), const Allocator& alloc = Allocator()) : t(comp, false), _alloc(alloc) {}

			template <class InputIterator>
			map(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), \
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) : _alloc(alloc)
			{
				this->insert(first, last);
			}

			map(const map& other) : t(other.t, false) {}
			
			virtual ~map() {}

			map &operator=(const map& other)
			{
				t = other.t;
				return *this;
			}

			allocator_type get_allocator() const {return _alloc;}

	// Element access
	
			T& operator[](const Key& key) {return (*((t.insert(ft::make_pair(key, T()))).first)).second;}

	// Iterators
	
			iterator				begin() {return t.begin();}
			iterator				end() {return t.end();}
			const_iterator			begin() const {return t.begin();}
			const_iterator			end() const {return t.end();}
			reverse_iterator		rbegin() {return reverse_iterator(end());}
			reverse_iterator		rend() {return reverse_iterator(begin());}
			const_reverse_iterator	rbegin() const {return const_reverse_iterator(end());}
			const_reverse_iterator	rend() const {return const_reverse_iterator(begin());}

	// Capacity
	
			bool empty() const {return t.empty();}
			size_type size() const {return t.size();}
			size_type max_size() const {return t.max_size();}

	// Modifiers
	
			void clear() {t.clear();}
			
			ft::pair<iterator, bool> insert(const value_type& value) {return t.insert(value);}
			
			iterator insert(iterator pos, const value_type& value) {return t.insert(pos, value);}
			
			template<class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
					this->insert(*first++);				
			}

			void erase(iterator pos) {t.erase(pos);}
			void erase(iterator first, iterator last) {t.erase(first, last);}
			size_type erase(const Key& key) {return t.erase(key);}
			
			void swap(map& other) {t.swap(other.t);}

	// Lookup
	
			size_type count(const Key& key) const {return t.count(key);}
			
			iterator find(const Key& key) {return t.find(key);}
			const_iterator find(const Key& key) const {return t.find(key);}

			ft::pair<iterator,iterator> equal_range(const Key& key) {return t.equal_range(key);}
			ft::pair<const_iterator,const_iterator> equal_range(const Key& key) const {return t.equal_range(key);}

			iterator lower_bound(const Key& key) {return t.lower_bound(key);}
			const_iterator lower_bound(const Key& key) const {return t.lower_bound(key);}

			iterator upper_bound(const Key& key) {return t.upper_bound(key);}
			const_iterator upper_bound(const Key& key) const {return t.upper_bound(key);}

	// Observers
			
			key_compare key_comp() const {return t.key_comp();}
			value_compare value_comp() const {return value_compare(t.key_comp());}
	};

/* NON-MEMBER FUNCTIONS------------------------------------------------------ */

	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template< class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}
					
	template<class Key, class T, class Compare, class Alloc>
	bool operator<(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template<class Key, class T, class Compare, class Alloc>
	void swap(ft::map<Key,T,Compare,Alloc>& lhs, ft::map<Key,T,Compare,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
}

#endif
