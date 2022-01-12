/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:17:21 by julian            #+#    #+#             */
/*   Updated: 2022/01/12 16:51:47 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ITERATOR_HPP
#define FT_ITERATOR_HPP

#include <iterator>

namespace ft
{
	template< typename T>
	class iterator 
	{
		public:
			typedef std::random_access_iterator_tag	iterator_category;
			typedef T								value_type;
			typedef std::ptrdiff_t					difference_type;
			typedef T*								pointer;
			typedef T&								reference;
		
		public:
			iterator(T* ptr = nullptr) : _ptr(ptr) {}
			iterator(const iterator<T>& rhs) {*this = rhs;}
			~iterator() {}

			iterator<T>&	operator=(const iterator<T>& rhs) {this->_ptr = rhs._ptr; return (*this);}
			iterator<T>&	operator=(T* ptr) {_ptr = ptr; return (*this);}

			operator		bool() const {if (_ptr) return true; else return false;}
			bool			operator==(const iterator<T>& rhs) const {return (_ptr == rhs._ptr);}
			bool			operator!=(const iterator<T>& rhs) const {return (_ptr != rhs._ptr);}

			iterator<T>&	operator+=(const difference_type& val) {_ptr += val; return (*this);}
			iterator<T>&	operator-=(const difference_type& val) {_ptr -= val; return (*this);}
			iterator<T>&	operator++() {++_ptr; return (*this);}
			iterator<T>&	operator--() {--_ptr; return (*this);}
			iterator<T>		operator++(int){iterator tmp(*this); ++_ptr; return (tmp);}
			iterator<T>		operator--(int){iterator tmp(*this); --_ptr; return (tmp);}
			iterator<T>		operator+(const difference_type& val) {return (iterator(_ptr + val));}
			iterator<T>		operator-(const difference_type& val) {return (iterator(_ptr - val));}

			difference_type	operator-(const iterator<T> rhs) {return (std::distance(rhs._ptr, _ptr));}

			reference		operator*() {return (*_ptr);}
			reference		operator*() const {return (*_ptr);}
			pointer			operator->() {return (_ptr);}

		protected:
			pointer	_ptr;
	};
}

namespace ft
{
	template< typename T>
	class reverse_iterator : public ft::iterator<T>
	{
		public:
			typedef std::ptrdiff_t difference_type;
		
		public:
			reverse_iterator(T* ptr = nullptr) : iterator<T>(ptr) {}
			reverse_iterator(const reverse_iterator<T>& rhs) {this->_ptr = rhs._ptr; return (*this);}
			~reverse_iterator() {}

			reverse_iterator<T>&	operator=(const reverse_iterator<T>& rhs) {this->_ptr = rhs._ptr; return (*this);}
			reverse_iterator<T>&	operator=(T* ptr) {this->_ptr = ptr; return (*this);}

			reverse_iterator<T>&	operator+=(const difference_type& val) {this->_ptr -= val; return (*this);}
			reverse_iterator<T>&	operator-=(const difference_type& val) {this->_ptr += val; return (*this);}
			reverse_iterator<T>&	operator++() {--this->_ptr; return (*this);}
			reverse_iterator<T>&	operator--() {++this->_ptr; return (*this);}
			reverse_iterator<T>		operator++(int){reverse_iterator tmp(*this); --this->_ptr; return (tmp);}
			reverse_iterator<T>		operator--(int){reverse_iterator tmp(*this); ++this->_ptr; return (tmp);}
			reverse_iterator<T>		operator+(const difference_type& val) {return (reverse_iterator(this->_ptr - val));}
			reverse_iterator<T>		operator-(const difference_type& val) {return (reverse_iterator(this->_ptr + val));}

			difference_type			operator-(const iterator<T> rhs) {return (std::distance(this->_ptr, rhs._ptr));}

			ft::iterator<T> 		base() {ft::iterator<T> rhs(this->_ptr); ++rhs; return (rhs);}
	};
}

#endif
