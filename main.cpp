/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:12:43 by julian            #+#    #+#             */
/*   Updated: 2022/01/17 18:56:52 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include "includes/ft_iterator.hpp"
#include "includes/ft_vector.hpp"
#include "includes/ft_random_access_iterator.hpp"

int main(void)
{
 	// ft::vector<int> first;                                // default
 	// ft::vector<int> second (4,100);                       // fill
  	// ft::vector<int> third (second.begin(),second.end());  // range
  	// ft::vector<int> fourth (third);                       // copy
	// ft::vector<int> fifth = second;
	
	// std::cout << "first - size " << first.size() << std::endl;
	// std::cout << "second - size " << second.size() << std::endl;
	// std::cout << "third - size " << third.size() << std::endl;
	
	// std::cout << "The contents of second are (index):   ";
	// for (int i = 0; i < 4; i++)
	// 	std::cout << ' ' << second[i];
	// std::cout << '\n';

	// std::cout << "The contents of second are (iterator):";
  	// for (ft::vector<int>::iterator it = second.begin(); it != second.end(); ++it)
    // 	std::cout << ' ' << *it;
  	// std::cout << '\n';

	// std::cout << "The contents of third are:            ";
	// for (int i = 0; i < 4; i++)
	// 	std::cout << ' ' << third[i];
	// std::cout << '\n';
	
	// std::cout << "The contents of fourth are:           ";
	// for (int i = 0; i < 4; i++)
	// 	std::cout << ' ' << fourth[i];
	// std::cout << '\n';

	// std::cout << "The contents of fifth are:            ";
	// for (int i = 0; i < 4; i++)
	// 	std::cout << ' ' << fifth[i];
	// std::cout << '\n';

	// // the iterator constructor can also be used to construct from arrays:
	// int myints[] = {16,2,77,29};
	// ft::vector<int> sixth (myints, myints + sizeof(myints) / sizeof(int) );

	// std::cout << "The contents of sixth are:            ";
	// for (ft::vector<int>::iterator it = sixth.begin(); it != sixth.end(); ++it)
	// std::cout << ' ' << *it;
	// std::cout << '\n';

	// second = ft::vector<int>();
	// std::cout << "Size of second: " << int(second.size()) << std::endl;;
  	// std::cout << "Size of fifth: " << int(fifth.size()) << std::endl;

	// std::cout << "The contents of second are (index):   ";
	// for (int i = 0; i < 4; i++)
	// 	std::cout << ' ' << second[i];
	// std::cout << '\n';

	// std::cout << "The contents of second are (iterator):";
  	// for (ft::vector<int>::iterator it = second.begin(); it != second.end(); ++it)
    // 	std::cout << ' ' << *it;
  	// std::cout << '\n';

	// std::cout << "The contents of fifth are:            ";
	// for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
	// std::cout << ' ' << *it;
	// std::cout << '\n';

	// ft::vector<int> myvector(129, 42);

	// set some content in the vector:
	// for (int i=0; i<129; i++) myvector.push_back('c');

	// std::cout << "size: " << myvector.size() << "\n";
	// std::cout << "capacity: " << myvector.capacity() << "\n";
	// std::cout << "max_size: " << myvector.max_size() << "\n";



	// ---------- push_back() ---------- //

	// ft::vector<int> pbVector;

  	// // set some values (from 1 to 10)
	// std::cout << "The contents of pbVector are: " << std::endl;
  	// for (int i = 1; i <= 5; i++) 
	// {
	// 	pbVector.push_back(i);
	// 	for (int j = 1; j <= i; j++)
	// 		std::cout << "value = " << pbVector[j - 1] << ", capacity = " << pbVector.capacity() << std::endl;
	// 	std::cout << std::endl;
	// }

	// ---------- resize() ---------- //
	
	// std::vector<int> myvector;

	// // set some initial content:
	// for (int i=1;i<10;i++) myvector.push_back(i);

	// myvector.resize(5);
	// // myvector.resize(8,100);
	// // myvector.resize(12);

	// std::cout << "myvector contains:";
	// for (size_t i=0;i<myvector.size();i++)
	// 	std::cout << ' ' << myvector[i];
	// std::cout << '\n';

	// ---------- erase() ---------- //
		
	// ft::vector<int> eraseVector;

	// // set some values (from 1 to 10)
	// for (int i=1; i<=10; i++) eraseVector.push_back(i);

	// // erase the 6th element
	// eraseVector.erase (eraseVector.begin()+5);

	// // erase the first 3 elements:
	// // eraseVector.erase (eraseVector.begin(),eraseVector.begin()+3);

	// std::cout << "eraseVector contains:";
	// for (unsigned i=0; i<eraseVector.size(); ++i)
	// 	std::cout << ' ' << eraseVector[i];
	// std::cout << '\n';

	// ---------- at() ---------- //

	// std::vector<int> myvector (10);   // 10 zero-initialized ints

	// // assign some values:
	// for (unsigned i=0; i<myvector.size(); i++)
	// 	myvector.at(i)=i;

	// std	::cout << "myvector contains:";
	// for (unsigned i=0; i<myvector.size(); i++)
	// 	std::cout << ' ' << myvector.at(i);
	// std::cout << '\n';

	// ---------- exception for at() ---------- //
	
	std::vector<int> myvector(10);
	try 
	{
		myvector.at(20)=100;      // vector::at throws an out-of-range
	}
	catch (const std::out_of_range& oor)
	{
		std::cerr << "Out of Range error: " << oor.what() << '\n';
	}

	return (0);
}