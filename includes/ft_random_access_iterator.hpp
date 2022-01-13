/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random_access_iterator.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:17:21 by julian            #+#    #+#             */
/*   Updated: 2022/01/13 18:02:39 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RANDOM_ACCESS_ITERATOR_HPP
#define FT_RANDOM_ACCESS_ITERATOR_HPP

#include <iterator>
#include "ft_iterator.hpp"
#include <cstddef>

namespace ft
{
	template< typename T>
	class random_access_iterator 
	{
		public:
			typedef ft::random_access_iterator_tag	iterator_category;
			typedef T								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef T*								pointer;
			typedef T&								reference;
		
		public:
			random_access_iterator(T* ptr = nullptr) : _ptr(ptr) {}
			random_access_iterator(const random_access_iterator<T>& rhs) {*this = rhs;}
			~random_access_iterator() {}

			random_access_iterator<T>&	operator=(const random_access_iterator<T>& rhs) {this->_ptr = rhs._ptr; return (*this);}
			random_access_iterator<T>&	operator=(T* ptr) {_ptr = ptr; return (*this);}

			operator		bool() const {if (_ptr) return true; else return false;}
			bool			operator==(const random_access_iterator<T>& rhs) const {return (_ptr == rhs._ptr);}
			bool			operator!=(const random_access_iterator<T>& rhs) const {return (_ptr != rhs._ptr);}

			random_access_iterator<T>&	operator+=(const difference_type& val) {_ptr += val; return (*this);}
			random_access_iterator<T>&	operator-=(const difference_type& val) {_ptr -= val; return (*this);}
			random_access_iterator<T>&	operator++() {++_ptr; return (*this);}
			random_access_iterator<T>&	operator--() {--_ptr; return (*this);}
			random_access_iterator<T>	operator++(int){random_access_iterator tmp(*this); ++_ptr; return (tmp);}
			random_access_iterator<T>	operator--(int){random_access_iterator tmp(*this); --_ptr; return (tmp);}
			random_access_iterator<T>	operator+(const difference_type& val) {return (random_access_iterator(_ptr + val));}
			random_access_iterator<T>	operator-(const difference_type& val) {return (random_access_iterator(_ptr - val));}

			difference_type	operator-(const random_access_iterator<T> rhs) {return (std::distance(rhs._ptr, _ptr));}

			reference		operator*() {return (*_ptr);}
			reference		operator*() const {return (*_ptr);}
			pointer			operator->() {return (_ptr);}

		protected:
			pointer	_ptr;
	};

	template< typename T>
	class reverse_random_access_iterator : public ft::random_access_iterator<T>
	{
		public:
			typedef std::ptrdiff_t difference_type;
		
		public:
			reverse_random_access_iterator(T* ptr = nullptr) : random_access_iterator<T>(ptr) {}
			reverse_random_access_iterator(const reverse_random_access_iterator<T>& rhs) {this->_ptr = rhs._ptr; return (*this);}
			~reverse_random_access_iterator() {}

			reverse_random_access_iterator<T>&	operator=(const reverse_random_access_iterator<T>& rhs) {this->_ptr = rhs._ptr; return (*this);}
			reverse_random_access_iterator<T>&	operator=(T* ptr) {this->_ptr = ptr; return (*this);}

			reverse_random_access_iterator<T>&	operator+=(const difference_type& val) {this->_ptr -= val; return (*this);}
			reverse_random_access_iterator<T>&	operator-=(const difference_type& val) {this->_ptr += val; return (*this);}
			reverse_random_access_iterator<T>&	operator++() {--this->_ptr; return (*this);}
			reverse_random_access_iterator<T>&	operator--() {++this->_ptr; return (*this);}
			reverse_random_access_iterator<T>	operator++(int){reverse_random_access_iterator tmp(*this); --this->_ptr; return (tmp);}
			reverse_random_access_iterator<T>	operator--(int){reverse_random_access_iterator tmp(*this); ++this->_ptr; return (tmp);}
			reverse_random_access_iterator<T>	operator+(const difference_type& val) {return (reverse_random_access_iterator(this->_ptr - val));}
			reverse_random_access_iterator<T>	operator-(const difference_type& val) {return (reverse_random_access_iterator(this->_ptr + val));}

			difference_type						operator-(const random_access_iterator<T> rhs) {return (std::distance(this->_ptr, rhs._ptr));}

			ft::random_access_iterator<T> 		base() {ft::random_access_iterator<T> rhs(this->_ptr); ++rhs; return (rhs);}
	};
}

#endif
