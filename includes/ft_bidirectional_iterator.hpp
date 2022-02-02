/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bidirectional_iterator.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/01/31 21:34:46 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_BIDIRECTIONAL_ITERATOR_HPP
#define FT_BIDIRECTIONAL_ITERATOR_HPP

#include <iterator>
#include "ft_iterator.hpp"
#include <cstddef>
#include "ft_nullptr.hpp"

namespace ft
{
	template< typename T, typename D>
	class bidirectional_iterator 
	{
		public:
			typedef ft::bidirectional_iterator_tag	iterator_category;
			typedef T								value_type;
			typedef D								difference_type;
			typedef T*								pointer;
			typedef T&								reference;
		
		public:
			bidirectional_iterator() : _ptr(ft_nullptr) {}
			bidirectional_iterator(pointer rhs) : _ptr(rhs) {}
			bidirectional_iterator(const bidirectional_iterator& rhs) : _ptr(rhs._ptr) {}
			~bidirectional_iterator() {}

			bidirectional_iterator&	operator=(const bidirectional_iterator& rhs) {_ptr = rhs._ptr; return (*this);}
			bidirectional_iterator&	operator=(pointer ptr) {_ptr = ptr; return (*this);}

			// Increment/decrement
			bidirectional_iterator&	operator++() {++_ptr; return (*this);}
			bidirectional_iterator	operator++(int) {bidirectional_iterator tmp(*this); ++_ptr; return (tmp);}
			bidirectional_iterator&	operator--() {--_ptr; return (*this);}
			bidirectional_iterator	operator--(int) {bidirectional_iterator tmp(*this); --_ptr; return (tmp);}

			//Pointer like operators
			reference	operator*() {return (*_ptr);}
			reference	operator*() const {return (*_ptr);}
			pointer		operator->() {return (_ptr);}
		
			// Comparison operator
			bool	operator==(const bidirectional_iterator& rhs) const {return (_ptr == rhs._ptr);}
			bool	operator!=(const bidirectional_iterator& rhs) const {return (_ptr != rhs._ptr);}

		protected:
			pointer	_ptr;
	};
}

#endif
