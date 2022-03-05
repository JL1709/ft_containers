/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bidirectional_iterator.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2022/03/05 11:32:41 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FT_BIDIRECTIONAL_ITERATOR_HPP
#define FT_BIDIRECTIONAL_ITERATOR_HPP

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

	template<typename BidirectionalIterator, typename T, typename Reference, typename pointer, typename Distance>
	class reverse_bidirectional_iterator : public bidirectional_iterator<T, Distance> 
	{
   			typedef reverse_bidirectional_iterator<BidirectionalIterator, T, Reference, pointer, Distance> self;

		protected:
    		BidirectionalIterator current;
	
		public:
			reverse_bidirectional_iterator() {}
			reverse_bidirectional_iterator(BidirectionalIterator x) : current(x) {}

			template<typename BiIt2, typename T2, typename Reference2, typename pointer2, typename Distance2>
			reverse_bidirectional_iterator(const reverse_bidirectional_iterator<BiIt2, T2, Reference2, pointer2, Distance2>& other) : current(other.base()) {}
			
			reverse_bidirectional_iterator(self& other) : current(other.base()) {}
			
			BidirectionalIterator const& base() const { return current; }
			BidirectionalIterator base() { return current; }
			
			Reference operator*() const {BidirectionalIterator tmp = current; return *--tmp;}
			Reference operator*() {BidirectionalIterator tmp = current; return *--tmp;}
			pointer	operator->() {return std::addressof(operator*());}
			pointer	operator->() const {return std::addressof(operator*());}
			self& operator++() {--current; return *this;}
			self operator++(int) {self tmp = *this;	--current; return tmp;}
			self& operator--() {++current; return *this;}
			self operator--(int) {self tmp = *this;	++current; return tmp;}
	};

	template<class Iterator1, class Iterator2, class T, class Reference, class pointer, class Distance>
	bool operator==(const ft::reverse_bidirectional_iterator<Iterator1, T, Reference, pointer, Distance>& lhs,
					const ft::reverse_bidirectional_iterator<Iterator2, T, Reference, pointer, Distance>& rhs)
	{
		return (lhs.base() == rhs.base());
	}
	
	template<class Iterator1, class Iterator2, class T, class Reference, class pointer, class Distance>
	bool operator!=(const ft::reverse_bidirectional_iterator<Iterator1, T, Reference, pointer, Distance>& lhs,
					const ft::reverse_bidirectional_iterator<Iterator2, T, Reference, pointer, Distance>& rhs)
	{
		return (lhs.base() != rhs.base());
	}
}

#endif
