/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random_access_iterator.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/02/04 14:01:42 by julian           ###   ########.fr       */
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

			random_access_iterator<T>&	operator=(const random_access_iterator<T>& rhs) {_ptr = rhs._ptr; return (*this);}
			random_access_iterator<T>&	operator=(pointer ptr) {_ptr = ptr; return (*this);}

			// Increment/decrement
			random_access_iterator<T>&	operator++() {++_ptr; return (*this);}
			random_access_iterator<T>	operator++(int) {random_access_iterator tmp(*this); ++_ptr; return (tmp);}
			random_access_iterator<T>&	operator--() {--_ptr; return (*this);}
			random_access_iterator<T>	operator--(int) {random_access_iterator tmp(*this); --_ptr; return (tmp);}
			
			// Arithmetic
			random_access_iterator<T>&	operator+=(const difference_type& val) {_ptr += val; return (*this);}
			random_access_iterator<T>&	operator-=(const difference_type& val) {_ptr -= val; return (*this);}
			random_access_iterator<T>	operator+(const difference_type& val) {return (random_access_iterator(_ptr + val));}
			random_access_iterator<T>	operator-(const difference_type& val) {return (random_access_iterator(_ptr - val));}
			difference_type				operator-(const random_access_iterator<T>& rhs) {return (_ptr - rhs._ptr);}

			//Pointer like operators
			reference	operator*() {return (*_ptr);}
			reference	operator*() const {return (*_ptr);}
			pointer		operator->() {return (_ptr);}
			reference	operator[](const difference_type& val) {return (_ptr[val]);}
		
			// Comparison operator
			bool	operator==(const random_access_iterator<T>& rhs) const {return (_ptr == rhs._ptr);}
			bool	operator!=(const random_access_iterator<T>& rhs) const {return (_ptr != rhs._ptr);}
			bool	operator<(const random_access_iterator<T>& rhs) const {return (_ptr < rhs._ptr);}
			bool	operator<=(const random_access_iterator<T>& rhs) const {return (_ptr <= rhs._ptr);}
			bool	operator>(const random_access_iterator<T>& rhs) const {return (_ptr > rhs._ptr);}
			bool	operator>=(const random_access_iterator<T>& rhs) const {return (_ptr >= rhs._ptr);}

		protected:
			pointer	_ptr;
	};
}

#endif
