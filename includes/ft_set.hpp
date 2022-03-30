/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 14:22:23 by julian            #+#    #+#             */
/*   Updated: 2022/03/30 10:39:02 by jludt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SET_HPP
#define FT_SET_HPP

#include <memory>
#include <cstddef>
#include "ft_utility.hpp"
#include "ft_iterator.hpp"
#include "ft_bidirectional_iterator.hpp"
#include "ft_tree.hpp"
#include "ft_type_traits.hpp"

template <class Arg, class Result>
struct set_unary_function 
{
	typedef Arg argument_type;
	typedef Result result_type;
};

template <class T, class U>
struct ident : public set_unary_function<T, U> 
{
	const U& operator()(const T& x) const { return x; }
};

namespace ft
{
	template < class Key,							// set::key_type/value_type
			class Compare = std::less<Key>,			// set::key_compare/value_compare
			class Allocator = std::allocator<Key>	// set::allocator_type
			> 
	class set
	{
		public:
/* MEMBER TYPES ------------------------------------------------------------- */
			typedef Key												key_type;
			typedef Key												value_type;
			typedef std::size_t										size_type;
			typedef std::ptrdiff_t									difference_type;
			typedef Compare											key_compare;
			typedef Compare											value_compare;
			typedef Allocator										allocator_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference 		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer 			const_pointer;
			typedef typename rb_tree<key_type, value_type, ident<value_type, key_type>, key_compare>::const_iterator			iterator;
			typedef typename rb_tree<key_type, value_type, ident<value_type, key_type>, key_compare>::const_iterator			const_iterator;
			typedef typename rb_tree<key_type, value_type, ident<value_type, key_type>, key_compare>::const_reverse_iterator	reverse_iterator;
			typedef typename rb_tree<key_type, value_type, ident<value_type, key_type>, key_compare>::const_reverse_iterator	const_reverse_iterator;
			// typedef typename ft::reverse_iterator<iterator>			reverse_iterator;
			// typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator; 

/* MEMBER Objects------------------------------------------------------------ */
		private:
			typedef rb_tree<key_type, value_type, ident<value_type, key_type>, key_compare> RBTree;
			RBTree	t;
			Allocator _alloc;

		public:
/* MEMBER FUNCTIONS --------------------------------------------------------- */

	// constructor, destructor, assignation operator, allocator
			explicit set(const Compare& comp = key_compare(), const Allocator& alloc = Allocator()) : t(comp, false), _alloc(alloc) {}

			template< class InputIt >
			set(InputIt first, InputIt last, const Allocator& alloc = Allocator(), \
					typename ft::enable_if<!ft::is_integral<InputIt>::value>::type* = 0) : _alloc(alloc)
			{
				this->insert(first, last);
			}

			set(const set& other) : t(other.t, false) {}

			virtual ~set() {}
	
			set& operator=(const set& other)
			{
				t = other.t;
				return *this;
			}

			allocator_type get_allocator() const {return _alloc;}

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

			iterator insert(const_iterator pos, const value_type& value) {return t.insert(pos, value);}

			template<class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
					this->insert(*first++);
			}

			void erase(const_iterator pos) {t.erase(pos);}
			void erase(const_iterator first, const_iterator last) {t.erase(first, last);}
			size_type erase(const Key& key) {return t.erase(key);}

			void swap(set& other) {t.swap(other.t);}

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
			value_compare value_comp() const {return t.key_comp();}
	};

	

/* NON-MEMBER FUNCTIONS------------------------------------------------------ */

	template<class Key, class Compare, class Alloc>
	bool operator==(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs)
	{
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template< class Key, class Compare, class Alloc>
	bool operator!=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}
					
	template<class Key, class Compare, class Alloc>
	bool operator<(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<class Key, class Compare, class Alloc>
	bool operator<=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template<class Key, class Compare, class Alloc>
	bool operator>(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template<class Key, class Compare, class Alloc>
	bool operator>=(const ft::set<Key,Compare,Alloc>& lhs, const ft::set<Key,Compare,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}

	template<class Key, class Compare, class Alloc>
	void swap(ft::set<Key,Compare,Alloc>& lhs, ft::set<Key,Compare,Alloc>& rhs)
	{
		lhs.swap(rhs);
	}
};

#endif
