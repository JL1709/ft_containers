/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_std.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:47:05 by julian            #+#    #+#             */
/*   Updated: 2022/02/03 13:24:19 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <set>

#include <sys/time.h>
#include <iomanip>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

int main()
{
	struct timespec start, end;
	// start timer.
	clock_gettime(CLOCK_MONOTONIC, &start);
	// unsync the I/O of C and C++.
	// ios_base::sync_with_stdio(false);
	
	std::cout << GREEN << "****************************" << std::endl;
	std::cout          << "*          VECTOR          *" << std::endl;
	std::cout          << "****************************" << RESET << std::endl;

	std::cout << YELLOW << "\nvector::vector\n" << RESET;
	
	// constructors used in the same order as described above:
	std::vector<int> vfirst;                                // empty vector of ints
	std::vector<int> vsecond (4,100);                       // four ints with value 100
	std::vector<int> vthird (vsecond.begin(),vsecond.end());  // iterating through second
	std::vector<int> vfourth (vthird);                       // a copy of third
	// the iterator constructor can also be used to construct from arrays:
	int vmyints[] = {16,2,77,29};
	std::vector<int> fifth (vmyints, vmyints + sizeof(vmyints) / sizeof(int) );
	std::cout << "The contents of fifth are:";
	for (std::vector<int>::iterator vit = fifth.begin(); vit != fifth.end(); ++vit)
	std::cout << ' ' << *vit;
	std::cout << '\n';
	
	std::cout << YELLOW << "\nvector::operator=\n" << RESET;

	std::vector<int> vfoo0 (3,0);
	std::vector<int> vbar0 (5,0);
	vbar0 = vfoo0;
	vfoo0 = std::vector<int>();
	std::cout << "Size of vfoo0: " << int(vfoo0.size()) << '\n';
	std::cout << "Size of vbar0: " << int(vbar0.size()) << '\n';

	std::cout << YELLOW << "\nvector::begin & vector::end\n" << RESET;
	
	std::vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);
	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::rbegin | vector::rend\n" << RESET;

	std::vector<int> myvector2 (5);  // 5 default-constructed ints
	int i=0;
	std::vector<int>::reverse_iterator rit = myvector2.rbegin();
	for (; rit!= myvector2.rend(); ++rit)
		*rit = ++i;
	std::cout << "myvector contains:";
	for (std::vector<int>::iterator it = myvector2.begin(); it != myvector2.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::size\n" << RESET;

	std::vector<int> vmyints2;
	std::cout << "0. size: " << vmyints2.size() << '\n';
	for (int i=0; i<10; i++) vmyints2.push_back(i);
		std::cout << "1. size: " << vmyints2.size() << '\n';
	vmyints2.insert (vmyints2.end(),10,100);
	std::cout << "2. size: " << vmyints2.size() << '\n';
	vmyints2.pop_back();
	std::cout << "3. size: " << vmyints2.size() << '\n';

	std::cout << YELLOW << "\nvector::size | vector::capacity | vector::max_size\n" << RESET;

	std::vector<int> myvector3;
	// set some content in the vector:
	for (int i=0; i<100; i++) myvector3.push_back(i);
	std::cout << "size: " << myvector3.size() << "\n";
	std::cout << "capacity: " << myvector3.capacity() << "\n";
	std::cout << "max_size: " << myvector3.max_size() << "\n";

	std::cout << YELLOW << "\nvector::resize\n" << RESET;

	std::vector<int> myvector4;
	for (int i=1;i<10;i++) myvector4.push_back(i);
	myvector4.resize(5);
	myvector4.resize(8,100);
	myvector4.resize(12);
	std::cout << "myvector contains:";
	for (unsigned i=0;i<myvector4.size();i++)
	std::cout << ' ' << myvector4[i];
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::empty\n" << RESET;

	std::vector<int> myvector5;
	int sum (0);
	for (int i=1;i<=10;i++) myvector5.push_back(i);
	while (!myvector5.empty())
	{
		sum += myvector5.back();
		myvector5.pop_back();
	}
	std::cout << "total: " << sum << '\n';

	std::cout << YELLOW << "\nvector::reserve\n" << RESET;

	std::vector<int>::size_type vsz;
	std::vector<int> vfoo;
	vsz = vfoo.capacity();
	std::cout << "making vfoo grow:\n";
	for (int i=0; i<100; ++i) {
		vfoo.push_back(i);
		if (vsz!=vfoo.capacity()) {
		vsz = vfoo.capacity();
		std::cout << "capacity changed: " << vsz << '\n';
		}
	}
	std::vector<int> vbar;
	vsz = vbar.capacity();
	vbar.reserve(100);   // this is the only difference with foo above
	std::cout << "making vbar grow:\n";
	for (int i=0; i<100; ++i) {
		vbar.push_back(i);
		if (vsz!=vbar.capacity()) {
		vsz = vbar.capacity();
		std::cout << "capacity changed: " << vsz << '\n';
		}
	}

	std::cout << YELLOW << "\nvector::operator[]\n" << RESET;

	std::vector<int> myvector6 (10);   // 10 zero-initialized elements
	std::vector<int>::size_type sz = myvector6.size();
	// assign some values:
	for (unsigned i=0; i<sz; i++) myvector6[i]=i;
	// reverse vector using operator[]:
	for (unsigned i=0; i<sz/2; i++)
	{
		int temp;
		temp = myvector6[sz-1-i];
		myvector6[sz-1-i]=myvector6[i];
		myvector6[i]=temp;
	}
	std::cout << "myvector6 contains:";
	for (unsigned i=0; i<sz; i++)
		std::cout << ' ' << myvector6[i];
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::at\n" << RESET;

	std::vector<int> myvector7 (10);   // 10 zero-initialized ints
	// assign some values:
	for (unsigned i=0; i<myvector7.size(); i++)
		myvector7.at(i)=i;
	std::cout << "myvector7 contains:";
	for (unsigned i=0; i<myvector7.size(); i++)
		std::cout << ' ' << myvector7.at(i);
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::front\n" << RESET;
	
	std::vector<int>myvector8;
	myvector8.push_back(78);
	myvector8.push_back(16);
	// now front equals 78, and back 16
	myvector8.front() -=myvector8.back();
	std::cout << "myvector8.front() is now " <<myvector8.front() << '\n';

	std::cout << YELLOW << "\nvector::back\n" << RESET;

	std::vector<int> myvector9;
	myvector9.push_back(10);
	while (myvector9.back() != 0)
	{
		myvector9.push_back ( myvector9.back() -1 );
	}
	std::cout << "myvector9 contains:";
	for (unsigned i=0; i<myvector9.size() ; i++)
		std::cout << ' ' << myvector9[i];
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::assign\n" << RESET;

	std::vector<int> vfirst2;
	std::vector<int> vsecond2;
	std::vector<int> vthird2;
	vfirst2.assign (7,100);             // 7 ints with a value of 100
	std::vector<int>::iterator it;
	it=vfirst2.begin()+1;
	vsecond2.assign (it,vfirst2.end()-1); // the 5 central values of first
	int vmyints3[] = {1776,7,4};
	vthird2.assign (vmyints3,vmyints3+3);   // assigning from array.
	std::cout << "Size of first: " << int (vfirst2.size()) << '\n';
	std::cout << "Size of second: " << int (vsecond2.size()) << '\n';
	std::cout << "Size of third: " << int (vthird2.size()) << '\n';

	std::cout << YELLOW << "\nvector::push_back\n" << RESET;
	
	std::vector<int> myvector10;
	for (int i = 0; i < 10; ++i)
		myvector10.push_back (i);
	std::cout << "myvector10 stores " << int(myvector10.size()) << " numbers.\n";

	std::cout << YELLOW << "\nvector::pop_back\n" << RESET;

	std::vector<int> myvector11;
	int sum2 (0);
	myvector11.push_back (100);
	myvector11.push_back (200);
	myvector11.push_back (300);
	while (!myvector11.empty())
	{
		sum2+=myvector11.back();
		myvector11.pop_back();
	}
	std::cout << "The elements of myvector11 add up to " << sum2 << '\n';

	std::cout << YELLOW << "\nvector::insert\n" << RESET;

	std::vector<int> myvector12 (3,100);
	std::vector<int>::iterator it12;
	it12 = myvector12.begin();
	it12 = myvector12.insert ( it12 , 200 );
	myvector12.insert (it12,2,300);
	// "it12" no longer valid, get a new one:
	it12 = myvector12.begin();
	std::vector<int> anothervector (2,400);
	myvector12.insert (it12+2,anothervector.begin(),anothervector.end());
	int myarray [] = { 501,502,503 };
	myvector12.insert (myvector12.begin(), myarray, myarray+3);
	std::cout << "myvector12 contains:";
	for (it12=myvector12.begin(); it12<myvector12.end(); it12++)
		std::cout << ' ' << *it12;
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::erase\n" << RESET;

	std::vector<int> myvector13;
	// set some values (from 1 to 10)
	for (int i=1; i<=10; i++) myvector13.push_back(i);
	// erase the 6th element
	myvector13.erase (myvector13.begin()+5);
	// erase the first 3 elements:
	myvector13.erase (myvector13.begin(),myvector13.begin()+3);
	std::cout << "myvector13 contains:";
	for (unsigned i=0; i<myvector13.size(); ++i)
		std::cout << ' ' << myvector13[i];
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::swap\n" << RESET;

	std::vector<int> vfoo3 (3,100);   // three ints with a value of 100
	std::vector<int> vbar3 (5,200);   // five ints with a value of 200
	std::cout << "vfoo3 contains:";
	for (unsigned i=0; i<vfoo3.size(); i++)
		std::cout << ' ' << vfoo3[i];
	std::cout << '\n';
	std::cout << "vbar3 contains:";
	for (unsigned i=0; i<vbar3.size(); i++)
		std::cout << ' ' << vbar3[i];
	std::cout << "\n\n";
	vfoo3.swap(vbar3);
	std::cout << "vfoo3 contains:";
	for (unsigned i=0; i<vfoo3.size(); i++)
		std::cout << ' ' << vfoo3[i];
	std::cout << '\n';
	std::cout << "vbar3 contains:";
	for (unsigned i=0; i<vbar3.size(); i++)
		std::cout << ' ' << vbar3[i];
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::clear\n" << RESET;

	std::vector<int> myvector14;
	myvector14.push_back (100);
	myvector14.push_back (200);
	myvector14.push_back (300);

	std::cout << "myvector14 contains:";
	for (unsigned i=0; i<myvector14.size(); i++)
		std::cout << ' ' << myvector14[i];
	std::cout << '\n';

	myvector14.clear();
	myvector14.push_back (1101);
	myvector14.push_back (2202);

	std::cout << "myvector14 contains:";
	for (unsigned i=0; i<myvector14.size(); i++)
		std::cout << ' ' << myvector14[i];
	std::cout << '\n';

	std::cout << YELLOW << "\nvector::get_allocator\n" << RESET;

	std::vector<int> myvector15;
	int * vp;
	unsigned int vi;
	// allocate an array with space for 5 elements using vector's allocator:
	vp = myvector15.get_allocator().allocate(5);
	// construct values in-place on the array:
	for (vi=0; vi<5; vi++) myvector15.get_allocator().construct(&vp[vi],vi);
	std::cout << "The allocated array contains:";
	for (vi=0; vi<5; vi++) std::cout << ' ' << vp[vi];
	std::cout << '\n';
	// destroy and deallocate:
	for (vi=0; vi<5; vi++) myvector15.get_allocator().destroy(&vp[vi]);
	myvector15.get_allocator().deallocate(vp,5);

	std::cout << YELLOW << "\nrelational operators (vector)\n" << RESET;

	std::vector<int> vfoo4 (3,100);   // three ints with a value of 100
	std::vector<int> vbar4 (2,200);   // two ints with a value of 200
	if (vfoo4==vbar4) std::cout << "vfoo4 and vbar4 are equal\n";
	if (vfoo4!=vbar4) std::cout << "vfoo4 and vbar4 are not equal\n";
	if (vfoo4< vbar4) std::cout << "vfoo4 is less than vbar4\n";
	if (vfoo4> vbar4) std::cout << "vfoo4 is greater than vbar4\n";
	if (vfoo4<=vbar4) std::cout << "vfoo4 is less than or equal to vbar4\n";
	if (vfoo4>=vbar4) std::cout << "vfoo4 is greater than or equal to vbar4\n";

	std::cout << YELLOW << "\nswap (vector)\n" << RESET;

	std::vector<int> vfoo5 (3,100);   // three ints with a value of 100
	std::vector<int> vbar5 (5,200);   // five ints with a value of 200
	std::cout << "vfoo5 contains:";
	for (std::vector<int>::iterator it = vfoo5.begin(); it!=vfoo5.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	std::cout << "vbar5 contains:";
	for (std::vector<int>::iterator it = vbar5.begin(); it!=vbar5.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	vfoo5.swap(vbar5);
	std::cout << "vfoo5 contains:";
	for (std::vector<int>::iterator it = vfoo5.begin(); it!=vfoo5.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';
	std::cout << "vbar5 contains:";
	for (std::vector<int>::iterator it = vbar5.begin(); it!=vbar5.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	// stop timer.
	// clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
	// clock_gettime(CLOCK_REALTIME, &end);
	clock_gettime(CLOCK_MONOTONIC, &end);

	// Calculating total time taken by the program.
	double time_taken;
	time_taken = (end.tv_sec - start.tv_sec) * 1e9;
	time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

	std::cout << CYAN << "\nTime taken by program for VECTOR is : " << std::fixed << time_taken << std::setprecision(9);
	std::cout << " sec" << std::endl << RESET;
	
	
	return (0);
}