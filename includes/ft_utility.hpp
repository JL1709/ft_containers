/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utility.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:56:30 by julian            #+#    #+#             */
/*   Updated: 2022/01/31 19:50:43 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILITY_HPP
#define FT_UTILITY_HPP

namespace ft
{
/* ------------------------------------------------------------------------- */
	// https://www.cplusplus.com/reference/utility/pair/pair/
	// https://en.cppreference.com/w/cpp/utility/pair

	template<class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		T1 first;
		T2 second;

		pair() : first(), second() {}
		pair(const T1& x, const T2& y) : first(x), second(y) {}
		
		template<class U1, class U2> 
		pair (const pair<U1,U2>& p) : first(p.first), second(p.second) {}

		pair& operator=(const pair& other) {first = other.first; second = other.second; return *this;}
	};

	template< class T1, class T2 >
	bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {return (lhs.first == rhs.first && lhs.second == rhs.second);}

	template< class T1, class T2 >
	bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)	{return !(lhs == rhs);}

	template< class T1, class T2 >
	bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		if (lhs.first < rhs.first)
			return true;
		if (rhs.first < lhs.first)
			return false;
		if (lhs.second < rhs.second)
			return true;
		else
			return false;
	}

	template< class T1, class T2 >
	bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {return !(rhs < lhs);}

	template< class T1, class T2 >
	bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {return (rhs < lhs);}

	template< class T1, class T2 >
	bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)	{return !(lhs < rhs);}

	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y) {return (pair<T1,T2>(x, y));}
}

#endif
