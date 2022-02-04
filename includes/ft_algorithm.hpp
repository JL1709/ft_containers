/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algorithm.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:10:08 by julian            #+#    #+#             */
/*   Updated: 2022/02/04 14:19:26 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ALGORITHM_HPP
#define FT_ALGORITHM_HPP

namespace ft
{
/* --------------------------------------------------------------------------------------------------------- */
	// https://www.cplusplus.com/reference/algorithm/equal/
	// https://en.cppreference.com/w/cpp/algorithm/equal
	
	template< class InputIterator1, class InputIterator2 >
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
			if (*first1 != *first2)
				return false;
		return true;
	}

	template< class InputIterator1, class InputIterator2, class BinaryPredicate >
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	{
		for (; first1 != last1; ++first1, ++first2)
			if (!pred(*first1, *first2))
				return false;
		return true;
	}
	
/* ------------------------------------------------------------------------------------------------------------------- */
	// https://www.cplusplus.com/reference/algorithm/lexicographical_compare/
	// https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}


	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

/* ------------------------------------------------------------------------------------------------------------------- */
	// https://en.cppreference.com/w/cpp/algorithm/swap
	// https://www.cplusplus.com/reference/algorithm/swap/

	template< class T >
	void swap( T& a, T& b )
	{
		T tmp(a);
		a = b;
		b = tmp;
	}
}

#endif
