/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_traits.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:07:43 by julian            #+#    #+#             */
/*   Updated: 2022/01/28 18:16:15 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TYPE_TRAITS_HPP
#define FT_TYPE_TRAITS_HPP

namespace ft
{
/* ------------------------------------------------------------------------- */
	// https://www.cplusplus.com/reference/type_traits/enable_if/
	
	template<bool Cond, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> {typedef T type;};

/* ------------------------------------------------------------------------- */
	// https://www.cplusplus.com/reference/type_traits/is_integral/
	// https://en.cppreference.com/w/cpp/types/integral_constant

	template<class T, T v>
	struct integral_constant
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant type;
		operator value_type() const {return value;}
	};

	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;
	
	template <class T>	struct is_integral							: public false_type {};
	template <>			struct is_integral<bool>					: public true_type {};
	template <>			struct is_integral<char>					: public true_type {};
	template <>			struct is_integral<char16_t>				: public true_type {};
	template <>			struct is_integral<char32_t>				: public true_type {};
	template <>			struct is_integral<wchar_t>					: public true_type {};
	template <>			struct is_integral<signed char>				: public true_type {};
	template <>			struct is_integral<short int>				: public true_type {};
	template <>			struct is_integral<int>						: public true_type {};
	template <>			struct is_integral<long int>				: public true_type {};
	template <>			struct is_integral<long long int>			: public true_type {};
	template <>			struct is_integral<unsigned char>			: public true_type {};
	template <>			struct is_integral<unsigned short int>		: public true_type {};
	template <>			struct is_integral<unsigned int>			: public true_type {};
	template <>			struct is_integral<unsigned long int>		: public true_type {};
	template <>			struct is_integral<unsigned long long int>	: public true_type {};
}

#endif