/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:12:43 by julian            #+#    #+#             */
/*   Updated: 2022/01/13 12:37:31 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include "includes/ft_iterator.hpp"
#include "includes/ft_vector.hpp"
#include "includes/ft_random_access_iterator.hpp"

int main(void)
{
	ft::vector<int> first;
	ft::vector<int> second(4, 100);
	ft::vector<int> third(second);
	// ft::vector<int> fourth = second;
	
	std::cout << "first - size " << first.size() << std::endl;
	std::cout << "second - size " << second.size() << std::endl;
	std::cout << "third - size " << third.size() << std::endl;
	
	std::cout << "The contents of second are:";
	for (int i = 0; i < 4; i++)
		std::cout << ' ' << second[i];
	std::cout << '\n';

	std::cout << "The contents of second are:";
  	for (ft::vector<int>::iterator it = second.begin(); it != second.end(); ++it)
    	std::cout << ' ' << *it;
  	std::cout << '\n';

	std::cout << "The contents of third are:";
	for (int i = 0; i < 4; i++)
		std::cout << ' ' << third[i];
	std::cout << '\n';

	// std::cout << "The contents of fourth are:";
  	// for (ft::vector<int>::iterator it = fourth.begin(); it != fourth.end(); ++it)
    // 	std::cout << ' ' << *it;
  	// std::cout << '\n';

	return (0);
}