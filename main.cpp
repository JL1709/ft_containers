/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 15:12:43 by julian            #+#    #+#             */
/*   Updated: 2022/02/02 16:30:19 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include "includes/ft_stack.hpp"
#include "includes/ft_iterator.hpp"
#include "includes/ft_vector.hpp"
#include "includes/ft_map.hpp"
#include "includes/ft_set.hpp"
#include "includes/ft_random_access_iterator.hpp"

int main(void)
{
/* --------------------------------- FT:SET --------------------------------- */

	// ft::set<int> myset;
	// ft::set<int>::iterator it;
	// ft::pair<ft::set<int>::iterator,bool> ret;

	// // set some initial values:
	// for (int i=1; i<=5; ++i) myset.insert(i*10);    // set: 10 20 30 40 50

	// ret = myset.insert(20);               // no new element inserted

	// if (ret.second==false) it=ret.first;  // "it" now points to element 20

	// myset.insert (it,25);                 // max efficiency inserting
	// myset.insert (it,24);                 // max efficiency inserting
	// myset.insert (it,26);                 // no max efficiency inserting

	// int myints[]= {5,10,15};              // 10 already in set, not inserted
	// myset.insert (myints,myints+3);

	// std::cout << "myset contains:";
	// for (it=myset.begin(); it!=myset.end(); ++it)
	// std::cout << ' ' << *it;
	// std::cout << '\n';

	
/* --------------------------------- FT:MAP --------------------------------- */

	// ft::map<char,int> map;

 	// map.insert (ft::pair<char,int>('a',100));
 	// map.insert (ft::pair<char,int>('z',200));

	// ft::pair<ft::map<char,int>::iterator,bool> ret;
	// ret = map.insert(ft::pair<char,int>('z',500) );
	// if (ret.second==false) 
	// {
	// 	std::cout << "element 'z' already existed";
	// 	std::cout << " with a value of " << ret.first->second << '\n';
	// }

	// // second insert function version (with hint position):
	// ft::map<char,int>::iterator it = map.begin();
	// map.insert(it, ft::pair<char,int>('b',300));  // max efficiency inserting
	// map.insert(it, ft::pair<char,int>('c',400));  // no max efficiency inserting

	// // third insert function version (range insertion):
	// ft::map<char,int> anothermap;
	// anothermap.insert(map.begin(),map.find('c'));

	// // showing contents:
	// std::cout << "map contains:\n";
	// for (it=map.begin(); it!=map.end(); ++it)
	// 	std::cout << it->first << " => " << it->second << '\n';

	// std::cout << "anothermap contains:\n";
	// for (it=anothermap.begin(); it!=anothermap.end(); ++it)
	// 	std::cout << it->first << " => " << it->second << '\n';

	// std::cout << "test\n";
	// map.erase('c');
	// std::cout << "map contains:\n";
	// for (ft::map<char,int>::iterator it=map.begin(); it!=map.end(); ++it)
	// 	std::cout << it->first << " => " << it->second << '\n';

	// erase
	ft::map<char,int> mymap;
	ft::map<char,int>::iterator it;

	// insert some values:
	mymap['a']=10;
	mymap['b']=20;
	mymap['c']=30;
	mymap['d']=40;
	mymap['e']=50;
	mymap['f']=60;

	// show content:
	std::cout << "All values:\n";
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << std::endl;

	std::cout << "Erase 'b' by iterator:\n";
	it=mymap.find('b');
	mymap.erase (it);                   // erasing by iterator
	
	// show content:
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << std::endl;

	std::cout << "Erase 'c' by key:\n";
	mymap.erase ('c');                  // erasing by key

	// show content:
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << std::endl;

	std::cout << "Erase 'e' till the end() by range:\n";
	it=mymap.find ('e');
	mymap.erase ( it, mymap.end());    // erasing by range

	// show content:
	for (it=mymap.begin(); it!=mymap.end(); ++it)
		std::cout << it->first << " => " << it->second << '\n';
	std::cout << std::endl;
 



	
/* -------------------------------- FT:STACK -------------------------------- */

	// ft::vector<int> myvector1 (3,100);         // vector with 3 elements
	// ft::vector<int> myvector2 (2,200);         // vector with 2 elements

	// ft::stack<int> first;                      // empty stack
	// ft::stack<int> second (myvector1);         // stack initialized to copy of deque

	// ft::stack<int,ft::vector<int> > third;     // empty stack using vector
	// ft::stack<int,ft::vector<int> > fourth (myvector2);
	// ft::stack<int> fifth = second;

	// std::cout << "size of first: " << first.size() << '\n';
	// std::cout << "size of second: " << second.size() << '\n';
	// std::cout << "size of third: " << third.size() << '\n';
	// std::cout << "size of fourth: " << fourth.size() << '\n';
	// std::cout << "size of fifth: " << fifth.size() << '\n';

	// ft::stack<int> pStack;
	// std::cout << "push() and top()...\n";
	// for (int i=0; i<5; ++i) 
	// {
	// 	pStack.push(i);
	// 	std::cout << ' ' << pStack.top();
	// }
	// std::cout << '\n';

	// std::cout << "\npop()...\n";
	// while (!pStack.empty())
	// {
	// 	std::cout << ' ' << pStack.top();
	// 	pStack.pop();
	// }
	// std::cout << '\n';

	// std::cout << "\nempty()...\n";
	// std::cout << std::boolalpha;
	// ft::stack<int> container;
	// std::cout << "Initially, container.empty(): " << container.empty() << '\n';
	// container.push(42);
	// std::cout << "After adding elements, container.empty(): " << container.empty() << '\n';
	
	// std::cout << "\nsize()...\n";
	// ft::stack<int> myints;
	// std::cout << "0. size: " << myints.size() << '\n';

	// for (int i=0; i<5; i++) myints.push(i);
	// std::cout << "1. size: " << myints.size() << '\n';

	// myints.pop();
	// std::cout << "2. size: " << myints.size() << '\n';

	// std::cout << "\nrelational operators...\n";
	// ft::stack<int> alice;
	// alice.push(1);
	// alice.push(2);
	// alice.push(3);
	// ft::stack<int> bob;
	// bob.push(7);
	// bob.push(8);
	// bob.push(9);
	// bob.push(10);
	// ft::stack<int> eve(alice);

	// std::cout << std::boolalpha;

	// // Compare non equal containers
	// std::cout << "alice == bob returns " << (alice == bob) << '\n';
	// std::cout << "alice != bob returns " << (alice != bob) << '\n';
	// std::cout << "alice <  bob returns " << (alice < bob) << '\n';
	// std::cout << "alice <= bob returns " << (alice <= bob) << '\n';
	// std::cout << "alice >  bob returns " << (alice > bob) << '\n';
	// std::cout << "alice >= bob returns " << (alice >= bob) << '\n';

	// std::cout << '\n';

	// // Compare equal containers
	// std::cout << "alice == eve returns " << (alice == eve) << '\n';
	// std::cout << "alice != eve returns " << (alice != eve) << '\n';
	// std::cout << "alice <  eve returns " << (alice < eve) << '\n';
	// std::cout << "alice <= eve returns " << (alice <= eve) << '\n';
	// std::cout << "alice >  eve returns " << (alice > eve) << '\n';
	// std::cout << "alice >= eve returns " << (alice >= eve) << '\n';

/* ------------------------------- FT:VECTOR -------------------------------- */
	
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

	// //set some content in the vector:
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
	
	// ft::vector<int> myvector;

	// // set some initial content:
	// for (int i = 1; i <= 4; i++) 
	// 	myvector.push_back(i);
	// for (size_t i=0;i<myvector.size();i++)
	// 	std::cout << ' ' << myvector[i];
	// std::cout << '\n';
	// std::cout << "capacity = " << myvector.capacity() << std::endl;
	
	// myvector.resize(5);
	// for (size_t i=0;i<myvector.size();i++)
	// 	std::cout << ' ' << myvector[i];
	// std::cout << '\n';
	// std::cout << "capacity = " << myvector.capacity() << std::endl;

	// myvector.resize(8,100);
	// for (size_t i=0;i<myvector.size();i++)
	// 	std::cout << ' ' << myvector[i];
	// std::cout << '\n';
	
	// myvector.resize(12);
	// for (size_t i=0;i<myvector.size();i++)
	// 	std::cout << ' ' << myvector[i];
	// std::cout << '\n';
	// for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
	// 	std::cout << ' ' << *it;
	// std::cout << '\n';

	// myvector.push_back(42);
	// for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
	// 	std::cout << ' ' << *it;
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

	// ft::vector<int> myvector (10);   // 10 zero-initialized ints

	// // assign some values:
	// for (unsigned i=0; i<myvector.size(); i++)
	// 	myvector.at(i)=i;

	// std::cout << "myvector contains:";
	// for (unsigned i=0; i<myvector.size(); i++)
	// 	std::cout << ' ' << myvector.at(i);
	// std::cout << '\n';

	// ---------- exception for at() ---------- //
	
	// ft::vector<int> myvector(10);
	// try 
	// {
	// 	myvector.at(20)=100;      // vector::at throws an out-of-range
	// }
	// catch (const std::out_of_range& oor)
	// {
	// 	std::cerr << "Out of Range error: " << oor.what() << '\n';
	// }

	// ---------- front() ---------- //
	
	// ft::vector<int> fVector;
  	// for (int i = 1; i <= 5; i++) 
	// 	fVector.push_back(i);
 	
	// std::cout << "The first element is '" << fVector.front() << "'.\n";

	// ---------- back() ---------- //
	
	// ft::vector<int> bVector;
  	// for (int i = 1; i <= 5; i++) 
	// 	bVector.push_back(i);
 	
	// std::cout << "The last element is '" << bVector.back() << "'.\n";

	// ---------- data() ---------- //

	// ft::vector<int> myvector (5);

	// int* p = myvector.data();

	// *p = 10;
	// ++p;
	// *p = 20;
	// p[2] = 100;

	// std::cout << "myvector contains:";
	// for (unsigned i=0; i<myvector.size(); ++i)
	// 	std::cout << ' ' << myvector[i];
	// std::cout << '\n';
	
	// ---------- assign() ---------- //

	// ft::vector<int> first;
	// ft::vector<int> second;
	// ft::vector<int> third;

	// first.assign (7,100);             // 7 ints with a value of 100

	// ft::vector<int>::iterator it;
	// it=first.begin()+1;

	// second.assign (it,first.end()-1); // the 5 central values of first

	// int myints[] = {1776,7,4};
	// third.assign (myints,myints+3);   // assigning from array.

	// std::cout << "Size of first: " << int (first.size()) << '\n';
	// std::cout << "Size of second: " << int (second.size()) << '\n';
	// std::cout << "Size of third: " << int (third.size()) << '\n';

	// ---------- clear() ---------- //
	
	// ft::vector<int> myvector;
	// myvector.push_back (100);
	// myvector.push_back (200);
	// myvector.push_back (300);

	// for (unsigned i=0; i<myvector.size(); i++)
	// std::cout << ' ' << myvector[i];
	// std::cout << '\n';

	// myvector.clear();
	// for (unsigned i=0; i<myvector.size(); i++)
	// std::cout << ' ' << myvector[i];
	// std::cout << '\n';
	
	// myvector.push_back (1101);
	// myvector.push_back (2202);

	// for (unsigned i=0; i<myvector.size(); i++)
	// std::cout << ' ' << myvector[i];
	// std::cout << '\n';

	// ---------- get_allocator() ---------- //

	// ft::vector<int> myvector;
	// int * p;
	// unsigned int i;

	// // allocate an array with space for 5 elements using vector's allocator:
	// p = myvector.get_allocator().allocate(5);

	// // construct values in-place on the array:
	// for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);

	// std::cout << "The allocated array contains:";
	// for (i=0; i<5; i++) std::cout << ' ' << p[i];
	// std::cout << '\n';

	// // destroy and deallocate:
	// for (i=0; i<5; i++) myvector.get_allocator().destroy(&p[i]);
	// myvector.get_allocator().deallocate(p,5);

	// ---------- pop_back() ---------- //
	
	// ft::vector<int> numbers;

	// std::cout << "[";
	// for (size_t i = 0; i < numbers.size(); i++)
	// 	std::cout << ' ' << numbers[i];
	// std::cout << " ]\n";

	// numbers.push_back(5);
	// numbers.push_back(3);
	// numbers.push_back(4);

	// std::cout << "[";
	// for (size_t i = 0; i < numbers.size(); i++)
	// 	std::cout << ' ' << numbers[i];
	// std::cout << " ]\n";

	// numbers.pop_back();

	// std::cout << "[";
	// for (size_t i = 0; i < numbers.size(); i++)
	// 	std::cout << ' ' << numbers[i];
	// std::cout << " ]\n";

	// ---------- insert() ---------- //

	// ft::vector<int> myvector (3,100);
	// ft::vector<int>::iterator it;
	
	// for (it=myvector.begin(); it<myvector.end(); it++)
	// std::cout << ' ' << *it;
	// std::cout << '\n';

	// it = myvector.begin();
	// it = myvector.insert ( it, 200 );

	// for (it=myvector.begin(); it<myvector.end(); it++)
	// std::cout << ' ' << *it;
	// std::cout << '\n';

	// // "it" no longer valid, get a new one:
	// it = myvector.end();
	// myvector.insert (it,2,300);

	// for (it=myvector.begin(); it<myvector.end(); it++)
	// std::cout << ' ' << *it;
	// std::cout << '\n';

	// // "it" no longer valid, get a new one:
	// it = myvector.begin();

	// ft::vector<int> anothervector (2,400);
	// myvector.insert (it+2,anothervector.begin(),anothervector.end());

	// for (it=myvector.begin(); it<myvector.end(); it++)
	// std::cout << ' ' << *it;
	// std::cout << '\n';

	// int myarray [] = { 501,502,503 };
	// myvector.insert (myvector.begin(), myarray, myarray+3);

	// for (it=myvector.begin(); it<myvector.end(); it++)
	// std::cout << ' ' << *it;
	// std::cout << '\n';

	// ---------- erase() ---------- //

	// ft::vector<int> myvector;

	// // set some values (from 1 to 10)
	// for (int i=1; i<=10; i++) myvector.push_back(i);

	// for (unsigned i=0; i<myvector.size(); ++i)
	// std::cout << ' ' << myvector[i];
	// std::cout << '\n';

	// // erase the 6th element
	// myvector.erase (myvector.begin() + 5);

	// for (unsigned i=0; i<myvector.size(); ++i)
	// std::cout << ' ' << myvector[i];
	// std::cout << '\n';

	// // erase the first 3 elements:
	// myvector.erase (myvector.begin(),myvector.begin()+3);

	// for (unsigned i=0; i<myvector.size(); ++i)
	// std::cout << ' ' << myvector[i];
	// std::cout << '\n';

	// ---------- ft::vector::swap ---------- //

	// ft::vector<int> foo (3,100);   // three ints with a value of 100
	// ft::vector<int> bar (5,200);   // five ints with a value of 200

	// std::cout << "foo contains:";
	// for (unsigned i=0; i<foo.size(); i++)
	// std::cout << ' ' << foo[i];
	// std::cout << '\n';

	// std::cout << "bar contains:";
	// for (unsigned i=0; i<bar.size(); i++)
	// std::cout << ' ' << bar[i];
	// std::cout << '\n';

	// std::cout << "\nswapping\n" << std::endl;
	// foo.swap(bar);

	// std::cout << "foo contains:";
	// for (unsigned i=0; i<foo.size(); i++)
	// std::cout << ' ' << foo[i];
	// std::cout << '\n';

	// std::cout << "bar contains:";
	// for (unsigned i=0; i<bar.size(); i++)
	// std::cout << ' ' << bar[i];
	// std::cout << '\n';

	// ---------- empty() ---------- //

	// std::cout << std::boolalpha;
	// ft::vector<int> numbers;
	// std::cout << "Initially, numbers.empty(): " << numbers.empty() << '\n';

	// numbers.push_back(42);
	// std::cout << "After adding elements, numbers.empty(): " << numbers.empty() << '\n';

	// ---------- reserve() ---------- //

	// ft::vector<int>::size_type sz;

	// ft::vector<int> foo;
	// sz = foo.capacity();
	// std::cout << "making foo grow:\n";
	// for (int i=0; i<100; ++i) 
	// {
	// 	foo.push_back(i);
	// 	if (sz!=foo.capacity())
	// 	{
	// 		sz = foo.capacity();
	// 		std::cout << "capacity changed: " << sz << '\n';
	// 	}
	// }
	// // foo.reserve(142);
	// // for (ft::vector<int>::iterator it = foo.begin(); it != foo.end(); ++it)
	// // 	std::cout << ' ' << *it;
	// // std::cout << '\n';
	
	// ft::vector<int> bar;
	// sz = bar.capacity();
	// bar.reserve(100);   // this is the only difference with foo above
	// std::cout << "making bar grow:\n";
	// for (int i=0; i<100; ++i)
	// {
	// 	bar.push_back(i);
	// 	if (sz!=bar.capacity())
	// 	{
	// 		sz = bar.capacity();
	// 		std::cout << "capacity changed: " << sz << '\n';
	// 	}
	// }

	// ---------- swap (vector overload -> non-member) ---------- //

	// ft::vector<int> foo (3,100);   // three ints with a value of 100
	// ft::vector<int> bar (5,200);   // five ints with a value of 200
	
	// std::cout << "foo contains:";
	// for (ft::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
	// std::cout << ' ' << *it;
	// std::cout << '\n';

	// std::cout << "bar contains:";
	// for (ft::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
	// std::cout << ' ' << *it;
	// std::cout << '\n';

	// std::cout << "\nswapping\n" << std::endl;
	// foo.swap(bar);

	// std::cout << "foo contains:";
	// for (ft::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
	// std::cout << ' ' << *it;
	// std::cout << '\n';

	// std::cout << "bar contains:";
	// for (ft::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
	// std::cout << ' ' << *it;
	// std::cout << '\n';

	// ---------- relational operators (non-member) ---------- //

	// ft::vector<int> alice;
	// alice.push_back(1);
	// alice.push_back(2);
	// alice.push_back(3);
	// ft::vector<int> bob;
	// bob.push_back(7);
	// bob.push_back(8);
	// bob.push_back(9);
	// bob.push_back(10);
	// ft::vector<int> eve(alice);

	// std::cout << std::boolalpha;

	// // Compare non equal containers
	// std::cout << "alice == bob returns " << (alice == bob) << '\n';
	// std::cout << "alice != bob returns " << (alice != bob) << '\n';
	// std::cout << "alice <  bob returns " << (alice < bob) << '\n';
	// std::cout << "alice <= bob returns " << (alice <= bob) << '\n';
	// std::cout << "alice >  bob returns " << (alice > bob) << '\n';
	// std::cout << "alice >= bob returns " << (alice >= bob) << '\n';

	// std::cout << '\n';

	// // Compare equal containers
	// std::cout << "alice == eve returns " << (alice == eve) << '\n';
	// std::cout << "alice != eve returns " << (alice != eve) << '\n';
	// std::cout << "alice <  eve returns " << (alice < eve) << '\n';
	// std::cout << "alice <= eve returns " << (alice <= eve) << '\n';
	// std::cout << "alice >  eve returns " << (alice > eve) << '\n';
	// std::cout << "alice >= eve returns " << (alice >= eve) << '\n';


	// system("leaks ft_container");
	return (0);
}