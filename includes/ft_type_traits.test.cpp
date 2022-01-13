/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_traits.test.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 15:49:21 by julian            #+#    #+#             */
/*   Updated: 2022/01/13 17:48:10 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// https://www.cplusplus.com/reference/type_traits/enable_if/

// enable_if example: two ways of using enable_if
#include <iostream>
#include "ft_type_traits.hpp"

// 1. the return type (bool) is only valid if T is an integral type:
template <class T>
typename ft::enable_if<std::is_integral<T>::value,bool>::type
  is_odd (T i) {return bool(i%2);}

// 2. the second template argument is only valid if T is an integral type:
// template <class T, class = typename ft::enable_if<std::is_integral<T>::value>::type>
// bool is_even (T i) {return !bool(i%2);}

int main() {

  short int i = 1;    // code does not compile if type of i is not integral

  std::cout << std::boolalpha;
  std::cout << "i is odd: " << is_odd(i) << std::endl;
//   std::cout << "i is even: " << is_even(i) << std::endl;

  std::cout << std::boolalpha;
  std::cout << "is_integral:" << std::endl;
  std::cout << "char: " << ft::is_integral<char>::value << std::endl;
  std::cout << "int: " << ft::is_integral<int>::value << std::endl;
  std::cout << "float: " << ft::is_integral<float>::value << std::endl;	

  return 0;
}