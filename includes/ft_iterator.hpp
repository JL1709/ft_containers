/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:55:36 by julian            #+#    #+#             */
/*   Updated: 2022/03/01 22:04:02 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ITERATOR_HPP
#define FT_ITERATOR_HPP

#include <cstddef>
#include <memory>

namespace ft
{
/* -------------------------------------------------------------------------------------------------------------- */
	// https://en.cppreference.com/w/cpp/iterator/iterator_tags
	
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag       : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};
	
/* -------------------------------------------------------------------------------------------------------------- */
	// https://www.cplusplus.com/reference/iterator/iterator_traits/
	
	template<class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template<class T>
	struct iterator_traits<T*>
	{
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template<class T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t				difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

/* -------------------------------------------------------------------------------------------------------------- */
	// https://www.cplusplus.com/reference/iterator/iterator/
	
	template<class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

/* -------------------------------------------------------------------------------------------------------------- */
	// https://www.cplusplus.com/reference/iterator/reverse_iterator/
	// https://en.cppreference.com/w/cpp/iterator/reverse_iterator

	template <class Iterator>
	class reverse_iterator
	{
		public:
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

		public:
			reverse_iterator() : current() {}
			explicit reverse_iterator (iterator_type x) : current(x) {};
			
			template<class U>
			reverse_iterator (const reverse_iterator<U>& other) : current(other.base()) {}

			template <class U>
			reverse_iterator&	operator=(const reverse_iterator<U>& other) {current = other.base(); return *this;}
			
			iterator_type		base() const {return current;}

			reference			operator* () const {Iterator tmp = current; return *--tmp;}
			pointer				operator->() const {return std::addressof(operator*());}
			reference 			operator[](difference_type n) const {return current[-n-1];}
			reverse_iterator&	operator++() {--current; return *this;}
			reverse_iterator&	operator--() {++current; return *this;}
			reverse_iterator	operator++(int) {reverse_iterator tmp(*this); --current; return tmp;}
			reverse_iterator	operator--(int) {reverse_iterator tmp(*this); ++current; return tmp;}
			reverse_iterator 	operator+ (difference_type n) const {return reverse_iterator(current-n);}
			reverse_iterator 	operator- (difference_type n) const {return reverse_iterator(current+n);}
			reverse_iterator&	operator+=(difference_type n) {current -= n; return *this;}
			reverse_iterator&	operator-=(difference_type n) {current += n; return *this;}

		protected:
			iterator_type	current;
	};
	
	template<class Iterator1, class Iterator2>
	bool operator==(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {return (lhs.base() == rhs.base());}
	
	template<class Iterator1, class Iterator2>
	bool operator!=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {return (lhs.base() != rhs.base());}
	
	template<class Iterator1, class Iterator2>
	bool operator<(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {return (lhs.base() > rhs.base());}
	
	template<class Iterator1, class Iterator2>
	bool operator<=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {return (lhs.base() >= rhs.base());}
	
	template<class Iterator1, class Iterator2>
	bool operator>(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {return (lhs.base() < rhs.base());}
	
	template<class Iterator1, class Iterator2>
	bool operator>=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) {return (lhs.base() <= rhs.base());}

	template<class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& it) {return reverse_iterator<Iter>(it.base() - n);}

	template < class T1, class T2 >
	typename reverse_iterator<T1>::difference_type
	operator-(const reverse_iterator<T1>& x, const reverse_iterator<T2>& y) {return (y.base() - x.base());}
}

#endif
