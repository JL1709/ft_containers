/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random_access_iterator.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/03/04 18:34:28 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_RANDOM_ACCESS_ITERATOR_HPP
#define FT_RANDOM_ACCESS_ITERATOR_HPP

#include "ft_iterator.hpp"
#include "ft_nullptr.hpp"

namespace ft
{
	template< typename T >
	class random_access_iterator
	{
		private:
			T*	_ptr;
	
		public:
			typedef ft::random_access_iterator_tag	iterator_category;
			typedef T								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef T*								pointer;
			typedef T&								reference;
		
		public:
			random_access_iterator() : _ptr(ft_nullptr) {}
			random_access_iterator(pointer rhs) : _ptr(rhs) {}
			random_access_iterator(const random_access_iterator<T>& rhs) : _ptr(rhs._ptr) {}
			~random_access_iterator() {}

			// casting operator
			operator random_access_iterator<const T>() const {return this->_ptr;}
			
			random_access_iterator&	operator=(const random_access_iterator<T>& rhs) {_ptr = rhs.base(); return (*this);}
			random_access_iterator&	operator=(pointer ptr) {_ptr = ptr; return (*this);}

			pointer const& base() const { return this->_ptr; }
			
			reference	operator*() const {return static_cast<reference>(*_ptr);}
			pointer		operator->() const {return (_ptr);}
			
			random_access_iterator&	operator++() {++_ptr; return (*this);}
			random_access_iterator	operator++(int) {random_access_iterator tmp(*this); ++_ptr; return (tmp);}
			random_access_iterator&	operator--() {--_ptr; return (*this);}
			random_access_iterator	operator--(int) {random_access_iterator tmp(*this); --_ptr; return (tmp);}
			random_access_iterator	operator+(difference_type val) const {return (random_access_iterator(_ptr + val));}
			random_access_iterator&	operator+=(difference_type val) {_ptr += val; return (*this);}
			random_access_iterator	operator-(difference_type val) const {return (random_access_iterator(_ptr - val));}
			random_access_iterator&	operator-=(difference_type val) {_ptr -= val; return (*this);}
			reference	operator[](difference_type val) const {return static_cast<reference>(_ptr[val]);}
	};

	template < class T1, class T2 >
	bool operator==(const random_access_iterator<T1>& x, const random_access_iterator<T2>& y) {return (x.base() == y.base());}
	template < class T1, class T2 >
	bool operator< (const random_access_iterator<T1>& x, const random_access_iterator<T2>& y) {return (x.base() < y.base());}
	template < class T1, class T2 >
	bool operator!=(const random_access_iterator<T1>& x, const random_access_iterator<T2>& y) {return (x.base() != y.base());}
	template < class T1, class T2 >
	bool operator> (const random_access_iterator<T1>& x, const random_access_iterator<T2>& y) {return (x.base() > y.base());}
	template < class T1, class T2 >
	bool operator>=(const random_access_iterator<T1>& x, const random_access_iterator<T2>& y) {return (x.base() >= y.base());}
	template < class T1, class T2 >
	bool operator<=(const random_access_iterator<T1>& x, const random_access_iterator<T2>& y) {return (x.base() <= y.base());}

	template < class T1, class T2 >
	typename random_access_iterator<T1>::difference_type
	operator-(const random_access_iterator<T1>& x, const random_access_iterator<T2>& y) {return (x.base() - y.base());}

	template < class T >
	random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type val, const random_access_iterator<T>& x)
	{
		return random_access_iterator<T>(x.base() + val);
	}
	
}

#endif
