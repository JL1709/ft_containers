/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_std.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 11:47:05 by julian            #+#    #+#             */
/*   Updated: 2022/02/04 15:15:21 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <set>

#include <sys/time.h>
#include <iomanip>
#include <fstream>

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BLUE    "\033[34m"

// functions for map & set
bool fncomp (char lhs, char rhs) {return lhs<rhs;}
bool fncomp (int lhs, int rhs) {return lhs<rhs;}

struct classcomp 
{
	bool operator() (const char& lhs, const char& rhs) const
	{return lhs<rhs;}
};

struct classcomp2
{
	bool operator() (const int& lhs, const int& rhs) const
	{return lhs<rhs;}
};

int main()
{
	std::ofstream outFile;
	outFile.open("std_containers.txt");
	struct timespec startVektor, endVektor;
	struct timespec startStack, endStack;
	struct timespec startMap, endMap;
	struct timespec startSet, endSet;

	// start timer.
	clock_gettime(CLOCK_MONOTONIC, &startVektor);
	
	outFile << GREEN << "\n****************************" << std::endl;
	outFile          <<   "*          VECTOR          *" << std::endl;
	outFile          <<   "****************************" << RESET << std::endl;

	outFile << YELLOW << "\nvector::vector\n" << RESET;
	
	// constructors used in the same order as described above:
	std::vector<int> vfirst;                                // empty vector of ints
	std::vector<int> vsecond (4,100);                       // four ints with value 100
	std::vector<int> vthird (vsecond.begin(),vsecond.end());  // iterating through second
	std::vector<int> vfourth (vthird);                       // a copy of third
	// the iterator constructor can also be used to construct from arrays:
	int vmyints[] = {16,2,77,29};
	std::vector<int> fifth (vmyints, vmyints + sizeof(vmyints) / sizeof(int) );
	outFile << "The contents of fifth are:";
	for (std::vector<int>::iterator vit = fifth.begin(); vit != fifth.end(); ++vit)
	outFile << ' ' << *vit;
	outFile << '\n';
	
	outFile << YELLOW << "\nvector::operator=\n" << RESET;

	std::vector<int> vfoo0 (3,0);
	std::vector<int> vbar0 (5,0);
	vbar0 = vfoo0;
	vfoo0 = std::vector<int>();
	outFile << "Size of vfoo0: " << int(vfoo0.size()) << '\n';
	outFile << "Size of vbar0: " << int(vbar0.size()) << '\n';

	outFile << YELLOW << "\nvector::begin & vector::end\n" << RESET;
	
	std::vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);
	outFile << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		outFile << ' ' << *it;
	outFile << '\n';

	outFile << YELLOW << "\nvector::rbegin | vector::rend\n" << RESET;

	std::vector<int> myvector2 (5);  // 5 default-constructed ints
	int i=0;
	std::vector<int>::reverse_iterator rit = myvector2.rbegin();
	for (; rit!= myvector2.rend(); ++rit)
		*rit = ++i;
	outFile << "myvector contains:";
	for (std::vector<int>::iterator it = myvector2.begin(); it != myvector2.end(); ++it)
		outFile << ' ' << *it;
	outFile << '\n';

	outFile << YELLOW << "\nvector::size\n" << RESET;

	std::vector<int> vmyints2;
	outFile << "0. size: " << vmyints2.size() << '\n';
	for (int i=0; i<10; i++) vmyints2.push_back(i);
		outFile << "1. size: " << vmyints2.size() << '\n';
	vmyints2.insert (vmyints2.end(),10,100);
	outFile << "2. size: " << vmyints2.size() << '\n';
	vmyints2.pop_back();
	outFile << "3. size: " << vmyints2.size() << '\n';

	outFile << YELLOW << "\nvector::size | vector::capacity | vector::max_size\n" << RESET;

	std::vector<int> myvector3;
	// set some content in the vector:
	for (int i=0; i<100; i++) myvector3.push_back(i);
	outFile << "size: " << myvector3.size() << "\n";
	outFile << "capacity: " << myvector3.capacity() << "\n";
	outFile << "max_size: " << myvector3.max_size() << "\n";

	outFile << YELLOW << "\nvector::resize\n" << RESET;

	std::vector<int> myvector4;
	for (int i=1;i<10;i++) myvector4.push_back(i);
	myvector4.resize(5);
	myvector4.resize(8,100);
	myvector4.resize(12);
	outFile << "myvector contains:";
	for (unsigned i=0;i<myvector4.size();i++)
	outFile << ' ' << myvector4[i];
	outFile << '\n';

	outFile << YELLOW << "\nvector::empty\n" << RESET;

	std::vector<int> myvector5;
	int sum (0);
	for (int i=1;i<=10;i++) myvector5.push_back(i);
	while (!myvector5.empty())
	{
		sum += myvector5.back();
		myvector5.pop_back();
	}
	outFile << "total: " << sum << '\n';

	outFile << YELLOW << "\nvector::reserve\n" << RESET;

	std::vector<int>::size_type vsz;
	std::vector<int> vfoo;
	vsz = vfoo.capacity();
	outFile << "making vfoo grow:\n";
	for (int i=0; i<100; ++i) {
		vfoo.push_back(i);
		if (vsz!=vfoo.capacity()) {
		vsz = vfoo.capacity();
		outFile << "capacity changed: " << vsz << '\n';
		}
	}
	std::vector<int> vbar;
	vsz = vbar.capacity();
	vbar.reserve(100);   // this is the only difference with foo above
	outFile << "making vbar grow:\n";
	for (int i=0; i<100; ++i) {
		vbar.push_back(i);
		if (vsz!=vbar.capacity()) {
		vsz = vbar.capacity();
		outFile << "capacity changed: " << vsz << '\n';
		}
	}

	outFile << YELLOW << "\nvector::operator[]\n" << RESET;

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
	outFile << "myvector6 contains:";
	for (unsigned i=0; i<sz; i++)
		outFile << ' ' << myvector6[i];
	outFile << '\n';

	outFile << YELLOW << "\nvector::at\n" << RESET;

	std::vector<int> myvector7 (10);   // 10 zero-initialized ints
	// assign some values:
	for (unsigned i=0; i<myvector7.size(); i++)
		myvector7.at(i)=i;
	outFile << "myvector7 contains:";
	for (unsigned i=0; i<myvector7.size(); i++)
		outFile << ' ' << myvector7.at(i);
	outFile << '\n';

	outFile << YELLOW << "\nvector::front\n" << RESET;
	
	std::vector<int>myvector8;
	myvector8.push_back(78);
	myvector8.push_back(16);
	// now front equals 78, and back 16
	myvector8.front() -=myvector8.back();
	outFile << "myvector8.front() is now " <<myvector8.front() << '\n';

	outFile << YELLOW << "\nvector::back\n" << RESET;

	std::vector<int> myvector9;
	myvector9.push_back(10);
	while (myvector9.back() != 0)
	{
		myvector9.push_back ( myvector9.back() -1 );
	}
	outFile << "myvector9 contains:";
	for (unsigned i=0; i<myvector9.size() ; i++)
		outFile << ' ' << myvector9[i];
	outFile << '\n';

	outFile << YELLOW << "\nvector::assign\n" << RESET;

	std::vector<int> vfirst2;
	std::vector<int> vsecond2;
	std::vector<int> vthird2;
	vfirst2.assign (7,100);             // 7 ints with a value of 100
	std::vector<int>::iterator it;
	it=vfirst2.begin()+1;
	vsecond2.assign (it,vfirst2.end()-1); // the 5 central values of first
	int vmyints3[] = {1776,7,4};
	vthird2.assign (vmyints3,vmyints3+3);   // assigning from array.
	outFile << "Size of first: " << int (vfirst2.size()) << '\n';
	outFile << "Size of second: " << int (vsecond2.size()) << '\n';
	outFile << "Size of third: " << int (vthird2.size()) << '\n';

	outFile << YELLOW << "\nvector::push_back\n" << RESET;
	
	std::vector<int> myvector10;
	for (int i = 0; i < 10; ++i)
		myvector10.push_back (i);
	outFile << "myvector10 stores " << int(myvector10.size()) << " numbers.\n";

	outFile << YELLOW << "\nvector::pop_back\n" << RESET;

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
	outFile << "The elements of myvector11 add up to " << sum2 << '\n';

	outFile << YELLOW << "\nvector::insert\n" << RESET;

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
	outFile << "myvector12 contains:";
	for (it12=myvector12.begin(); it12<myvector12.end(); it12++)
		outFile << ' ' << *it12;
	outFile << '\n';

	outFile << YELLOW << "\nvector::erase\n" << RESET;

	std::vector<int> myvector13;
	// set some values (from 1 to 10)
	for (int i=1; i<=10; i++) myvector13.push_back(i);
	// erase the 6th element
	myvector13.erase (myvector13.begin()+5);
	// erase the first 3 elements:
	myvector13.erase (myvector13.begin(),myvector13.begin()+3);
	outFile << "myvector13 contains:";
	for (unsigned i=0; i<myvector13.size(); ++i)
		outFile << ' ' << myvector13[i];
	outFile << '\n';

	outFile << YELLOW << "\nvector::swap\n" << RESET;

	std::vector<int> vfoo3 (3,100);   // three ints with a value of 100
	std::vector<int> vbar3 (5,200);   // five ints with a value of 200
	outFile << "vfoo3 contains:";
	for (unsigned i=0; i<vfoo3.size(); i++)
		outFile << ' ' << vfoo3[i];
	outFile << '\n';
	outFile << "vbar3 contains:";
	for (unsigned i=0; i<vbar3.size(); i++)
		outFile << ' ' << vbar3[i];
	outFile << "\n\n";
	vfoo3.swap(vbar3);
	outFile << "vfoo3 contains:";
	for (unsigned i=0; i<vfoo3.size(); i++)
		outFile << ' ' << vfoo3[i];
	outFile << '\n';
	outFile << "vbar3 contains:";
	for (unsigned i=0; i<vbar3.size(); i++)
		outFile << ' ' << vbar3[i];
	outFile << '\n';

	outFile << YELLOW << "\nvector::clear\n" << RESET;

	std::vector<int> myvector14;
	myvector14.push_back (100);
	myvector14.push_back (200);
	myvector14.push_back (300);

	outFile << "myvector14 contains:";
	for (unsigned i=0; i<myvector14.size(); i++)
		outFile << ' ' << myvector14[i];
	outFile << '\n';

	myvector14.clear();
	myvector14.push_back (1101);
	myvector14.push_back (2202);

	outFile << "myvector14 contains:";
	for (unsigned i=0; i<myvector14.size(); i++)
		outFile << ' ' << myvector14[i];
	outFile << '\n';

	outFile << YELLOW << "\nvector::get_allocator\n" << RESET;

	std::vector<int> myvector15;
	int * vp;
	unsigned int vi;
	// allocate an array with space for 5 elements using vector's allocator:
	vp = myvector15.get_allocator().allocate(5);
	// construct values in-place on the array:
	for (vi=0; vi<5; vi++) myvector15.get_allocator().construct(&vp[vi],vi);
	outFile << "The allocated array contains:";
	for (vi=0; vi<5; vi++) outFile << ' ' << vp[vi];
	outFile << '\n';
	// destroy and deallocate:
	for (vi=0; vi<5; vi++) myvector15.get_allocator().destroy(&vp[vi]);
	myvector15.get_allocator().deallocate(vp,5);

	outFile << YELLOW << "\nrelational operators (vector)\n" << RESET;

	std::vector<int> vfoo4 (3,100);   // three ints with a value of 100
	std::vector<int> vbar4 (2,200);   // two ints with a value of 200
	if (vfoo4==vbar4) outFile << "vfoo4 and vbar4 are equal\n";
	if (vfoo4!=vbar4) outFile << "vfoo4 and vbar4 are not equal\n";
	if (vfoo4< vbar4) outFile << "vfoo4 is less than vbar4\n";
	if (vfoo4> vbar4) outFile << "vfoo4 is greater than vbar4\n";
	if (vfoo4<=vbar4) outFile << "vfoo4 is less than or equal to vbar4\n";
	if (vfoo4>=vbar4) outFile << "vfoo4 is greater than or equal to vbar4\n";

	outFile << YELLOW << "\nswap (vector)\n" << RESET;

	std::vector<int> vfoo5 (3,100);   // three ints with a value of 100
	std::vector<int> vbar5 (5,200);   // five ints with a value of 200
	outFile << "vfoo5 contains:";
	for (std::vector<int>::iterator it = vfoo5.begin(); it!=vfoo5.end(); ++it)
		outFile << ' ' << *it;
	outFile << '\n';
	outFile << "vbar5 contains:";
	for (std::vector<int>::iterator it = vbar5.begin(); it!=vbar5.end(); ++it)
		outFile << ' ' << *it;
	outFile << '\n';
	vfoo5.swap(vbar5);
	outFile << "vfoo5 contains:";
	for (std::vector<int>::iterator it = vfoo5.begin(); it!=vfoo5.end(); ++it)
		outFile << ' ' << *it;
	outFile << '\n';
	outFile << "vbar5 contains:";
	for (std::vector<int>::iterator it = vbar5.begin(); it!=vbar5.end(); ++it)
		outFile << ' ' << *it;
	outFile << '\n';

	// stop timer.
	// clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
	// clock_gettime(CLOCK_REALTIME, &end);
	clock_gettime(CLOCK_MONOTONIC, &endVektor);

/* ------------------------------------------------------------------------------------------------------------------ */

	// start timer.
	clock_gettime(CLOCK_MONOTONIC, &startStack);
	
	outFile << GREEN << "\n***************************" << std::endl;
	outFile          <<   "*          STACK          *" << std::endl;
	outFile          <<   "***************************" << RESET << std::endl;

	outFile << YELLOW << "\nstack::stack\n" << RESET;

	std::deque<int> smydeque (3,200);          // deque with 3 elements
	std::vector<int> smyvector (2,200);        // vector with 2 elements
	std::stack<int> sfirst;                    // empty stack
	std::stack<int> ssecond (smydeque);         // stack initialized to copy of deque
	std::stack<int,std::vector<int> > sthird;  // empty stack using vector
	std::stack<int,std::vector<int> > sfourth (smyvector);
	outFile << "size of sfirst: " << sfirst.size() << '\n';
	outFile << "size of ssecond: " << ssecond.size() << '\n';
	outFile << "size of sthird: " << sthird.size() << '\n';
	outFile << "size of sfourth: " << sfourth.size() << '\n';

	outFile << YELLOW << "\nstack::empty\n" << RESET;

	std::stack<int> mystack;
	int ssum (0);
	for (int i=1;i<=10;i++) mystack.push(i);
	while (!mystack.empty())
	{
		ssum += mystack.top();
		mystack.pop();
	}
	outFile << "total: " << ssum << '\n';

	outFile << YELLOW << "\nstack::size\n" << RESET;
	
	std::stack<int> smyints;
	outFile << "0. size: " << smyints.size() << '\n';
	for (int i=0; i<5; i++) smyints.push(i);
	outFile << "1. size: " << smyints.size() << '\n';
	smyints.pop();
	outFile << "2. size: " << smyints.size() << '\n';

	outFile << YELLOW << "\nstack::top\n" << RESET;

	std::stack<int> mystack2;
	mystack2.push(10);
	mystack2.push(20);
	mystack2.top() -= 5;
	outFile << "mystack2.top() is now " << mystack2.top() << '\n';

	outFile << YELLOW << "\nstack::push | stack::pop\n" << RESET;

	std::stack<int> mystack3;
	for (int i=0; i<5; ++i) mystack3.push(i);
	outFile << "Popping out elements...";
	while (!mystack3.empty())
	{
		outFile << ' ' << mystack3.top();
		mystack3.pop();
	}
	outFile << '\n';

	outFile << YELLOW << "\nrelational operators (stack)\n" << RESET;

	std::stack<int> mystackA;
	outFile << "StackA contains: ";
	for (int i=1;i<=10;i++)
	{
		outFile << i << " ";
		mystackA.push(i);
	}
	outFile << '\n';

	outFile << "StackB contains: ";
	std::stack<int> mystackB;
	for (int i=1;i<=10;i++)
	{
		outFile << i << " ";
		mystackB.push(i);
	}
	outFile << '\n';
	outFile << std::boolalpha;
	outFile << "operator== "<<(mystackA == mystackB) << '\n';
	outFile << "operator!= "<<(mystackA != mystackB) << '\n';
	outFile << "operator<  "<<(mystackA < mystackB) << '\n';
	outFile << "operator<= "<<(mystackA <= mystackB) << '\n';
	outFile << "operator>  "<<(mystackA > mystackB) << '\n';
	outFile << "operator>= "<<(mystackA >= mystackB) << '\n';
	outFile << std::noboolalpha;

	clock_gettime(CLOCK_MONOTONIC, &endStack);

/* ------------------------------------------------------------------------------------------------------------------ */

	// start timer.
	clock_gettime(CLOCK_MONOTONIC, &startMap);
	
	outFile << GREEN << "\n***************************" << std::endl;
	outFile          <<   "*           MAP           *" << std::endl;
	outFile          <<   "***************************" << RESET << std::endl;

	outFile << YELLOW << "\nmap::map\n" << RESET;

	std::map<char,int> mfirst;
	mfirst['a']=10;
	mfirst['b']=30;
	mfirst['c']=50;
	mfirst['d']=70;
	std::map<char,int> msecond (mfirst.begin(),mfirst.end());
	std::map<char,int> mthird (msecond);
	std::map<char,int,classcomp> mfourth;                 // class as Compare
	bool(*fn_pt)(char,char) = fncomp;
	std::map<char,int,bool(*)(char,char)> mfifth (fn_pt);
	for (std::map<char, int>::iterator mit = mthird.begin(); mit != mthird.end(); ++mit)
		outFile << mit->first << " => " << mit->second << '\n';

	outFile << YELLOW << "\nmap::operator=\n" << RESET;

	std::map<char,int> mfirst2;
	std::map<char,int> msecond2;
	mfirst2['x']=8;
	mfirst2['y']=16;
	mfirst2['z']=32;
	msecond2=mfirst2;                // second now contains 3 ints
	mfirst2=std::map<char,int>();    // and first is now empty
	outFile << "Size of mfirst2: " << mfirst2.size() << '\n';
	outFile << "Size of msecond2: " << msecond2.size() << '\n';

	outFile << YELLOW << "\nmap::begin | map::end\n" << RESET;

	std::map<char,int> mymap;
	mymap['b'] = 100;
	mymap['a'] = 200;
	mymap['c'] = 300;
	// show content:
	for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
		outFile << it->first << " => " << it->second << '\n';

	outFile << YELLOW << "\nmap::rbegin | map::rend\n" << RESET;

	std::map<char,int> mymap2;
	mymap2['x'] = 100;
	mymap2['y'] = 200;
	mymap2['z'] = 300;
	// show content:
	std::map<char,int>::reverse_iterator mrit;
	for (mrit=mymap2.rbegin(); mrit!=mymap2.rend(); ++mrit)
		outFile << mrit->first << " => " << mrit->second << '\n';

	outFile << YELLOW << "\nmap::empty\n" << RESET;

	std::map<char,int> mymap3;
	mymap3['a']=10;
	mymap3['b']=20;
	mymap3['c']=30;
	while (!mymap3.empty())
	{
		outFile << mymap3.begin()->first << " => " << mymap3.begin()->second << '\n';
		mymap3.erase(mymap3.begin());
	}

	outFile << YELLOW << "\nmap::size\n" << RESET;
	
	std::map<char,int> mymap4;
	mymap4['a']=101;
	mymap4['b']=202;
	mymap4['c']=302;
	outFile << "mymap4.size() is " << mymap4.size() << '\n';

	outFile << YELLOW << "\nmap::max_size\n" << RESET;

	std::map<int,int> mymap5;
	if (mymap5.max_size()>1000)
	{
		for (int i=0; i<1000; i++) mymap5[i]=0;
		outFile << "The map contains 1000 elements.\n";
	}
	else outFile << "The map could not hold 1000 elements.\n";

	outFile << YELLOW << "\nmap::operator[]\n" << RESET;
	
	std::map<char,std::string> mymap6;
	mymap6['a']="an element";
	mymap6['b']="another element";
	mymap6['c']=mymap6['b'];
	outFile << "mymap6['a'] is " << mymap6['a'] << '\n';
	outFile << "mymap6['b'] is " << mymap6['b'] << '\n';
	outFile << "mymap6['c'] is " << mymap6['c'] << '\n';
	outFile << "mymap6['d'] is " << mymap6['d'] << '\n';
	outFile << "mymap6 now contains " << mymap6.size() << " elements.\n";

	outFile << YELLOW << "\nmap::insert\n" << RESET;

	std::map<char,int> mymap7;
	// first insert function version (single parameter):
	mymap7.insert ( std::pair<char,int>('a',100) );
	mymap7.insert ( std::pair<char,int>('z',200) );
	std::pair<std::map<char,int>::iterator,bool> ret;
	ret = mymap7.insert ( std::pair<char,int>('z',500) );
	if (ret.second==false) {
		outFile << "element 'z' already existed";
		outFile << " with a value of " << ret.first->second << '\n';
	}
	// second insert function version (with hint position):
	std::map<char,int>::iterator mit7 = mymap7.begin();
	mymap7.insert (mit7, std::pair<char,int>('b',300));  // max efficiency inserting
	mymap7.insert (mit7, std::pair<char,int>('c',400));  // no max efficiency inserting
	// third insert function version (range insertion):
	std::map<char,int> anothermap;
	anothermap.insert(mymap7.begin(),mymap7.find('c'));
	// showing contents:
	outFile << "mymap7 contains:\n";
	for (mit7=mymap7.begin(); mit7!=mymap7.end(); ++mit7)
		outFile << mit7->first << " => " << mit7->second << '\n';
	outFile << "anothermap contains:\n";
	for (mit7=anothermap.begin(); mit7!=anothermap.end(); ++mit7)
		outFile << mit7->first << " => " << mit7->second << '\n';

	outFile << YELLOW << "\nmap::erase\n" << RESET;

	std::map<char,int> mymap8;
	std::map<char,int>::iterator mit8;
	// insert some values:
	mymap8['a']=10;
	mymap8['b']=20;
	mymap8['c']=30;
	mymap8['d']=40;
	mymap8['e']=50;
	mymap8['f']=60;
	mit8=mymap8.find('b');
	mymap8.erase (mit8);                   // erasing by iterator
	mymap8.erase ('c');                  // erasing by key
	mit8=mymap8.find ('e');
	mymap8.erase ( mit8, mymap8.end() );    // erasing by range
	// show content:
	for (mit8=mymap8.begin(); mit8!=mymap8.end(); ++mit8)
		outFile << mit8->first << " => " << mit8->second << '\n';

	outFile << YELLOW << "\nmap::swap\n" << RESET;
	
	std::map<char,int> mfoo;
	std::map<char,int> mbar;
	mfoo['x']=100;
	mfoo['y']=200;
	mbar['a']=11;
	mbar['b']=22;
	mbar['c']=33;
	outFile << "mfoo contains:\n";
	for (std::map<char,int>::iterator it=mfoo.begin(); it!=mfoo.end(); ++it)
		outFile << it->first << " => " << it->second << '\n';
	outFile << "mbar contains:\n";
	for (std::map<char,int>::iterator it=mbar.begin(); it!=mbar.end(); ++it)
		outFile << it->first << " => " << it->second << '\n';
	outFile << "\nswapping\n\n";
	mfoo.swap(mbar);
	outFile << "mfoo contains:\n";
	for (std::map<char,int>::iterator it=mfoo.begin(); it!=mfoo.end(); ++it)
		outFile << it->first << " => " << it->second << '\n';
	outFile << "mbar contains:\n";
	for (std::map<char,int>::iterator it=mbar.begin(); it!=mbar.end(); ++it)
		outFile << it->first << " => " << it->second << '\n';

	outFile << YELLOW << "\nmap::clear\n" << RESET;

	std::map<char,int> mymap9;
	mymap9['x']=100;
	mymap9['y']=200;
	mymap9['z']=300;
	outFile << "mymap9 contains:\n";
	for (std::map<char,int>::iterator it=mymap9.begin(); it!=mymap9.end(); ++it)
		outFile << it->first << " => " << it->second << '\n';
	mymap9.clear();
	mymap9['a']=1101;
	mymap9['b']=2202;
	outFile << "mymap9 contains:\n";
	for (std::map<char,int>::iterator it=mymap9.begin(); it!=mymap9.end(); ++it)
		outFile << it->first << " => " << it->second << '\n';
		
	outFile << YELLOW << "\nmap::key_comp\n" << RESET;

	std::map<char,int> mymap10;
	std::map<char,int>::key_compare mycomp = mymap10.key_comp();
	mymap10['a']=100;
	mymap10['b']=200;
	mymap10['c']=300;
	outFile << "mymap10 contains:\n";
	char highest = mymap10.rbegin()->first;     // key value of last element
	std::map<char,int>::iterator mit10 = mymap10.begin();
	do {
		outFile << mit10->first << " => " << mit10->second << '\n';
	} while ( mycomp((*mit10++).first, highest) );
	outFile << '\n';

	outFile << YELLOW << "\nmap::value_comp\n" << RESET;

	std::map<char,int> mymap11;
	mymap11['x']=1001;
	mymap11['y']=2002;
	mymap11['z']=3003;
	outFile << "mymap11 contains:\n";
	std::pair<char,int> highest2 = *mymap11.rbegin();          // last element
	std::map<char,int>::iterator mit11 = mymap11.begin();
	do {
		outFile << mit11->first << " => " << mit11->second << '\n';
	} while ( mymap11.value_comp()(*mit11++, highest2) );

	outFile << YELLOW << "\nmap::find\n" << RESET;

	std::map<char,int> mymap12;
	std::map<char,int>::iterator mit12;
	mymap12['a']=50;
	mymap12['b']=100;
	mymap12['c']=150;
	mymap12['d']=200;
	mit12 = mymap12.find('b');
	if (mit12 != mymap12.end())
		mymap12.erase (mit12);
	// print content:
	outFile << "elements in mymap12:" << '\n';
	outFile << "a => " << mymap12.find('a')->second << '\n';
	outFile << "c => " << mymap12.find('c')->second << '\n';
	outFile << "d => " << mymap12.find('d')->second << '\n';

	outFile << YELLOW << "\nmap::count\n" << RESET;

	std::map<char,int> mymap13;
	char c;
	mymap13 ['a']=101;
	mymap13 ['c']=202;
	mymap13 ['f']=303;
	for (c='a'; c<'h'; c++)
	{
		outFile << c;
		if (mymap13.count(c)>0)
			outFile << " is an element of mymap13.\n";
		else 
			outFile << " is not an element of mymap13.\n";
	}

	outFile << YELLOW << "\nmap::lower_bound | map::upper_bound\n" << RESET;

	std::map<char,int> mymap14;
	std::map<char,int>::iterator itlow;
	std::map<char,int>::iterator itup;
	mymap14['a']=20;
	mymap14['b']=40;
	mymap14['c']=60;
	mymap14['d']=80;
	mymap14['e']=100;
	itlow=mymap14.lower_bound ('b');  // itlow points to b
	itup=mymap14.upper_bound ('d');   // itup points to e (not d!)
	mymap14.erase(itlow,itup);        // erases [itlow,itup)
	// print content:
	for (std::map<char,int>::iterator it=mymap14.begin(); it!=mymap14.end(); ++it)
		outFile << it->first << " => " << it->second << '\n';

	outFile << YELLOW << "\nmap::equal_range\n" << RESET;

	std::map<char,int> mymap15;
	mymap15['a']=10;
	mymap15['b']=20;
	mymap15['c']=30;
	std::pair<std::map<char,int>::iterator,std::map<char,int>::iterator> mret2;
	mret2 = mymap15.equal_range('b');
	outFile << "lower bound points to: ";
	outFile << mret2.first->first << " => " << mret2.first->second << '\n';
	outFile << "upper bound points to: ";
	outFile << mret2.second->first << " => " << mret2.second->second << '\n';

	outFile << YELLOW << "\nmap::get_allocator\n" << RESET;

	int psize;
	std::map<char,int> mymap16;
	std::pair<const char,int>* p;
	// allocate an array of 5 elements using mymap16's allocator:
	p=mymap16.get_allocator().allocate(5);
	// assign some values to array
	psize = sizeof(std::map<char,int>::value_type)*5;
	outFile << "The allocated array has a size of " << psize << " bytes.\n";
	mymap16.get_allocator().deallocate(p,5);

	outFile << YELLOW << "\nrelational operators (map)\n" << RESET;

	std::map<int, char> malice;
	malice.insert ( std::pair<int,char>(1,'a') );
	malice.insert ( std::pair<int,char>(2,'b') );
	malice.insert ( std::pair<int,char>(3,'c') );
	std::map<int, char> mbob;
	mbob.insert ( std::pair<int,char>(7,'Z') );
	mbob.insert ( std::pair<int,char>(8,'Y') );
	mbob.insert ( std::pair<int,char>(9,'X') );
	mbob.insert ( std::pair<int,char>(10,'W') );
	std::map<int, char> meve;
	meve.insert ( std::pair<int,char>(1,'a') );
	meve.insert ( std::pair<int,char>(2,'b') );
	meve.insert ( std::pair<int,char>(3,'c') );
	outFile << std::boolalpha;
	// Compare non equal containers
	outFile << "malice == mbob returns " << (malice == mbob) << '\n';
	outFile << "malice != mbob returns " << (malice != mbob) << '\n';
	outFile << "malice <  mbob returns " << (malice < mbob) << '\n';
	outFile << "malice <= mbob returns " << (malice <= mbob) << '\n';
	outFile << "malice >  mbob returns " << (malice > mbob) << '\n';
	outFile << "malice >= mbob returns " << (malice >= mbob) << '\n';
	outFile << '\n';
	// Compare equal containers
	outFile << "malice == meve returns " << (malice == meve) << '\n';
	outFile << "malice != meve returns " << (malice != meve) << '\n';
	outFile << "malice <  meve returns " << (malice < meve) << '\n';
	outFile << "malice <= meve returns " << (malice <= meve) << '\n';
	outFile << "malice >  meve returns " << (malice > meve) << '\n';
	outFile << "malice >= meve returns " << (malice >= meve) << '\n';
	outFile << std::noboolalpha;

	outFile << YELLOW << "\nswap (map)\n" << RESET;

	std::map<int, char> malice2;
	malice2.insert ( std::pair<int,char>(1,'a') );
	malice2.insert ( std::pair<int,char>(2,'b') );
	malice2.insert ( std::pair<int,char>(3,'c') );
	std::map<int, char> mbob2;
	mbob2.insert ( std::pair<int,char>(7,'Z') );
	mbob2.insert ( std::pair<int,char>(8,'Y') );
	mbob2.insert ( std::pair<int,char>(9,'X') );
	mbob2.insert ( std::pair<int,char>(10,'W') );
	// Print state before swap
	outFile << "malice2:\n";
	for (std::map<int,char>::iterator it=malice2.begin(); it!=malice2.end(); ++it)
		outFile << it->first << " => " << it->second << '\n';
	outFile << "\n" "mbob2:\n";
	for (std::map<int,char>::iterator it=mbob2.begin(); it!=mbob2.end(); ++it)
		outFile << it->first << " => " << it->second << '\n';
	outFile << "\n-- SWAP\n\n";
	std::swap(malice2, mbob2);
	// Print state after swap
	outFile << "malice2:\n";
	for (std::map<int,char>::iterator it=malice2.begin(); it!=malice2.end(); ++it)
		outFile << it->first << " => " << it->second << '\n';
	outFile << "\n" "mbob2:\n";
	for (std::map<int,char>::iterator it=mbob2.begin(); it!=mbob2.end(); ++it)
		outFile << it->first << " => " << it->second << '\n';

	clock_gettime(CLOCK_MONOTONIC, &endMap);


/* ------------------------------------------------------------------------------------------------------------------ */

	// start timer.
	clock_gettime(CLOCK_MONOTONIC, &startSet);
	
	outFile << GREEN << "\n***************************" << std::endl;
	outFile          <<   "*           Set           *" << std::endl;
	outFile          <<   "***************************" << RESET << std::endl;

	outFile << YELLOW << "\nset::set\n" << RESET;
	
	std::set<int> setfirst;                           // empty set of ints
	int setmyints[]= {10,20,30,40,50};
	std::set<int> setsecond (setmyints,setmyints+5);        // range
	std::set<int> setthird (setsecond);                  // a copy of second
	std::set<int> setfourth (setsecond.begin(), setsecond.end());  // iterator ctor.
	std::set<int,classcomp> setfifth;                 // class as Compare
	bool(*sfn_pt)(int,int) = fncomp;
	std::set<int,bool(*)(int,int)> setsixth (sfn_pt);  // function pointer as Compare
	for (std::set<int>::iterator mit = setthird.begin(); mit != setthird.end(); ++mit)
		outFile << *mit << '\n';

	outFile << YELLOW << "\nset::operator=\n" << RESET;

	int setmyints2[]={ 12,82,37,64,15 };
	std::set<int> setfirst2 (setmyints2,setmyints2+5);   // set with 5 ints
	std::set<int> setsecond2;                    // empty set
	setsecond2 = setfirst2;                          // now second contains the 5 ints
	setfirst2 = std::set<int>();                 // and first is empty
	outFile << "Size of first: " << int (setfirst2.size()) << '\n';
	outFile << "Size of second: " << int (setsecond2.size()) << '\n';

	outFile << YELLOW << "\nset::begin | set::end\n" << RESET;

	int setints3[] = {75,23,65,42,13};
	std::set<int> myset (setints3,setints3+5);
	outFile << "myset contains:";
	for (std::set<int>::iterator it=myset.begin(); it!=myset.end(); ++it)
		outFile << ' ' << *it;
	outFile << '\n';

	outFile << YELLOW << "\nset::rbegin | set::rend\n" << RESET;

	int setints4[] = {21,64,17,78,49};
	std::set<int> myset2 (setints4,setints4+5);
	std::set<int>::reverse_iterator setrit;
	outFile << "myset2 contains:";
	for (setrit=myset2.rbegin(); setrit != myset2.rend(); ++setrit)
		outFile << ' ' << *setrit;
	outFile << '\n';

	outFile << YELLOW << "\nset::emty\n" << RESET;
	
	std::set<int> myset3;
	myset3.insert(20);
	myset3.insert(30);
	myset3.insert(10);
	outFile << "myset3 contains:";
	while (!myset3.empty())
	{
		outFile << ' ' << *myset3.begin();
		myset3.erase(myset3.begin());
	}
	outFile << '\n';

	outFile << YELLOW << "\nset::size\n" << RESET;

	std::set<int> myset4;
	outFile << "0. size: " << myset4.size() << '\n';
	for (int i=0; i<10; ++i) myset4.insert(i);
	outFile << "1. size: " << myset4.size() << '\n';
	myset4.insert (100);
	outFile << "2. size: " << myset4.size() << '\n';
	myset4.erase(5);
	outFile << "3. size: " << myset4.size() << '\n';

	outFile << YELLOW << "\nset::max_size\n" << RESET;
	
	std::set<int> myset5;
	if (myset5.max_size()>1000)
	{
		for (i=0; i<1000; i++) myset5.insert(i);
		outFile << "The set contains 1000 elements.\n";
	}
	else outFile << "The set could not hold 1000 elements.\n";

	outFile << YELLOW << "\nset::insert\n" << RESET;

	std::set<int> myset6;
	std::set<int>::iterator set_it;
	std::pair<std::set<int>::iterator,bool> set_ret;
	// set some inset_itial values:
	for (int i=1; i<=5; ++i) myset6.insert(i*10);    // set: 10 20 30 40 50
	set_ret = myset6.insert(20);               // no new element inserted
	if (set_ret.second==false) set_it=set_ret.first;  // "set_it" now points to element 20
	myset6.insert (set_it,25);                 // max efficiency inserting
	myset6.insert (set_it,24);                 // max efficiency inserting
	myset6.insert (set_it,26);                 // no max efficiency inserting
	int myints[]= {5,10,15};              // 10 already in set, not inserted
	myset6.insert (myints,myints+3);
	outFile << "myset6 contains:";
	for (set_it=myset6.begin(); set_it!=myset6.end(); ++set_it)
		outFile << ' ' << *set_it;
	outFile << '\n';

	outFile << YELLOW << "\nset::erase\n" << RESET;

	std::set<int> myset7;
	std::set<int>::iterator set_it2;
	// insert some values:
	for (int i=1; i<10; i++) myset7.insert(i*10);  // 10 20 30 40 50 60 70 80 90
	set_it2 = myset7.begin();
	++set_it2;                                         // "set_it2" points now to 20
	myset7.erase (set_it2);
	myset7.erase (40);
	set_it2 = myset7.find (60);
	myset7.erase (set_it2, myset7.end());
	outFile << "myset7 contains:";
	for (set_it2=myset7.begin(); set_it2!=myset7.end(); ++set_it2)
		outFile << ' ' << *set_it2;
	outFile << '\n';

	outFile << YELLOW << "\nset::swap\n" << RESET;

	 int set_myints[]={12,75,10,32,20,25};
	std::set<int> set_first (set_myints,set_myints+3);     // 10,12,75
	std::set<int> set_second (set_myints+3,set_myints+6);  // 20,25,32
	outFile << "set_first contains:";
	for (std::set<int>::iterator it=set_first.begin(); it!=set_first.end(); ++it)
		outFile << ' ' << *it;
	outFile << '\n';
	outFile << "set_second contains:";
	for (std::set<int>::iterator it=set_second.begin(); it!=set_second.end(); ++it)
		outFile << ' ' << *it;
	outFile << '\n';
	outFile << "\nswapping\n\n";
	set_first.swap(set_second);
	outFile << "set_first contains:";
	for (std::set<int>::iterator it=set_first.begin(); it!=set_first.end(); ++it)
		outFile << ' ' << *it;
	outFile << '\n';
	outFile << "set_second contains:";
	for (std::set<int>::iterator it=set_second.begin(); it!=set_second.end(); ++it)
		outFile << ' ' << *it;
	outFile << '\n';

	outFile << YELLOW << "\nset::clear\n" << RESET;

	std::set<int> myset8;
	myset8.insert (100);
	myset8.insert (200);
	myset8.insert (300);
	outFile << "myset8 contains:";
	for (std::set<int>::iterator it=myset8.begin(); it!=myset8.end(); ++it)
		outFile << ' ' << *it;
	outFile << '\n';
	myset8.clear();
	myset8.insert (1101);
	myset8.insert (2202);
	outFile << "myset8 contains:";
	for (std::set<int>::iterator it=myset8.begin(); it!=myset8.end(); ++it)
		outFile << ' ' << *it;
	outFile << '\n';

	outFile << YELLOW << "\nset::key_compare\n" << RESET;

	std::set<int> myset9;
	int set_highest;
	std::set<int>::key_compare set_mycomp = myset9.key_comp();
	for (int i=0; i<=5; i++) myset9.insert(i);
	outFile << "myset9 contains:";
	set_highest=*myset9.rbegin();
	std::set<int>::iterator set_it9=myset9.begin();
	do {
		outFile << ' ' << *set_it9;
	} while ( set_mycomp(*(++set_it9),set_highest) );
	outFile << '\n';

	outFile << YELLOW << "\nset::value_compare\n" << RESET;

	std::set<int> myset10;
	std::set<int>::value_compare set_mycomp2 = myset10.value_comp();
	for (int i=0; i<=5; i++) myset10.insert(i);
	outFile << "myset10 contains:";
	int set_highest2=*myset10.rbegin();
	std::set<int>::iterator set_it10=myset10.begin();
	do {
		outFile << ' ' << *set_it10;
	} while ( set_mycomp2(*(++set_it10),set_highest2) );
	outFile << '\n';

	outFile << YELLOW << "\nset::key_compare\n" << RESET;

	std::set<int> myset11;
	std::set<int>::iterator set_it11;
	// set some inset_it11ial values:
	for (int i=1; i<=5; i++) myset11.insert(i*10);    // set: 10 20 30 40 50
	set_it11=myset11.find(20);
	myset11.erase (set_it11);
	myset11.erase (myset11.find(40));
	outFile << "myset11 contains:";
	for (set_it11=myset11.begin(); set_it11!=myset11.end(); ++set_it11)
		outFile << ' ' << *set_it11;
	outFile << '\n';

	outFile << YELLOW << "\nset::count\n" << RESET;

	std::set<int> myset12;
	// set some initial values:
	for (int i=1; i<5; ++i) myset12.insert(i*3);    // set: 3 6 9 12
	for (int i=0; i<10; ++i)
	{
		outFile << i;
		if (myset12.count(i)!=0)
		outFile << " is an element of myset12.\n";
		else
		outFile << " is not an element of myset12.\n";
	}

	outFile << YELLOW << "\nset::lower_bound | set::upper_bound\n" << RESET;

	std::set<int> myset13;
	std::set<int>::iterator set_itlow;
	std::set<int>::iterator set_itup;
	for (int i=1; i<10; i++) myset13.insert(i*10); // 10 20 30 40 50 60 70 80 90
	set_itlow=myset13.lower_bound (30);                //       ^
	set_itup=myset13.upper_bound (60);                 //                   ^
	myset13.erase(set_itlow,set_itup);                     // 10 20 70 80 90
	outFile << "myset13 contains:";
	for (std::set<int>::iterator it=myset13.begin(); it!=myset13.end(); ++it)
		outFile << ' ' << *it;
	outFile << '\n';

	outFile << YELLOW << "\nset::equal_range\n" << RESET;

	std::set<int> myset14;
	for (int i=1; i<=5; i++) myset14.insert(i*10);   // myset14: 10 20 30 40 50
	std::pair<std::set<int>::const_iterator,std::set<int>::const_iterator> set_ret14;
	set_ret14 = myset14.equal_range(30);
	outFile << "the lower bound points to: " << *set_ret14.first << '\n';
	outFile << "the upper bound points to: " << *set_ret14.second << '\n';

	outFile << YELLOW << "\nset::get_allocator\n" << RESET;

	std::set<int> myset15;
	int * sp;
	unsigned int si;
	// allocate an array of 5 elements using myset15's allocator:
	sp=myset15.get_allocator().allocate(5);
	// assign some values to array
	for (si=0; si<5; si++) sp[si]=(si+1)*10;
	outFile << "The allocated array contains:";
	for (si=0; si<5; si++) outFile << ' ' << sp[si];
	outFile << '\n';
	myset15.get_allocator().deallocate(sp,5);

	outFile << YELLOW << "\nrelational operators (set)\n" << RESET;

	std::set<int> salice;
	salice.insert(1);
	salice.insert(2);
	salice.insert(3);
	std::set<int> sbob;
	sbob.insert(7);
	sbob.insert(8);
	sbob.insert(9);
	sbob.insert(10);
	std::set<int> seve;
	seve.insert(1);
	seve.insert(2);
	seve.insert(3);
	outFile << std::boolalpha;
	// Compare non equal containers
	outFile << "salice == sbob returns " << (salice == sbob) << '\n';
	outFile << "salice != sbob returns " << (salice != sbob) << '\n';
	outFile << "salice <  sbob returns " << (salice < sbob) << '\n';
	outFile << "salice <= sbob returns " << (salice <= sbob) << '\n';
	outFile << "salice >  sbob returns " << (salice > sbob) << '\n';
	outFile << "salice >= sbob returns " << (salice >= sbob) << '\n';
	outFile << '\n';
	// Compare equal containers
	outFile << "salice == seve returns " << (salice == seve) << '\n';
	outFile << "salice != seve returns " << (salice != seve) << '\n';
	outFile << "salice <  seve returns " << (salice < seve) << '\n';
	outFile << "salice <= seve returns " << (salice <= seve) << '\n';
	outFile << "salice >  seve returns " << (salice > seve) << '\n';
	outFile << "salice >= seve returns " << (salice >= seve) << '\n';

	outFile << YELLOW << "\nswap (set)\n" << RESET;


	std::set<int> salice2;
	salice2.insert(1);
	salice2.insert(2);
	salice2.insert(3);
	std::set<int> sbob2;
	sbob2.insert(7);
	sbob2.insert(8);
	sbob2.insert(9);
	sbob2.insert(10);
	// Print state before swap
	outFile << "salice2:\n";
	for (std::set<int>::iterator it=salice2.begin(); it!=salice2.end(); ++it)
		outFile << *it << '\n';
	outFile << "\n" "sbob2:\n";
	for (std::set<int>::iterator it=sbob2.begin(); it!=sbob2.end(); ++it)
		outFile << *it << '\n';
	outFile << '\n';
	outFile << "-- SWAP\n\n";
	std::swap(salice2, sbob2);
	// Print state after swap
	outFile << "salice2:\n";
	for (std::set<int>::iterator it=salice2.begin(); it!=salice2.end(); ++it)
		outFile << *it << '\n';
	outFile << "\n" "sbob2:\n";
	for (std::set<int>::iterator it=sbob2.begin(); it!=sbob2.end(); ++it)
		outFile << *it << '\n';
	outFile << '\n';

	clock_gettime(CLOCK_MONOTONIC, &endSet);

/* ------------------------------------------------------------------------------------------------------------------ */

	outFile << BLUE << "\n-------------------------------------------------------\n" << RESET;;
	double time_takenStack;
	time_takenStack = (endStack.tv_sec - startStack.tv_sec) * 1e9;
	time_takenStack = (time_takenStack + (endStack.tv_nsec - startStack.tv_nsec)) * 1e-9;
	outFile << CYAN << "Time taken by program for STD_STACK  is " << std::fixed << std::setprecision(9) << time_takenStack;
	outFile << " sec" << std::endl << RESET;
	

	double time_takenVektor;
	time_takenVektor = (endVektor.tv_sec - startVektor.tv_sec) * 1e9;
	time_takenVektor = (time_takenVektor + (endVektor.tv_nsec - startVektor.tv_nsec)) * 1e-9;
	outFile << CYAN << "Time taken by program for STD_VECTOR is " << std::fixed << std::setprecision(9) << time_takenVektor;
	outFile << " sec" << std::endl << RESET;

	double time_takenMap;
	time_takenMap = (endMap.tv_sec - startMap.tv_sec) * 1e9;
	time_takenMap = (time_takenMap + (endMap.tv_nsec - startMap.tv_nsec)) * 1e-9;
	outFile << CYAN << "Time taken by program for STD_MAP    is " << std::fixed << std::setprecision(9) << time_takenMap;
	outFile << " sec" << std::endl << RESET;

	double time_takenSet;
	time_takenSet = (endSet.tv_sec - startSet.tv_sec) * 1e9;
	time_takenSet = (time_takenSet + (endSet.tv_nsec - startSet.tv_nsec)) * 1e-9;
	outFile << CYAN << "Time taken by program for STD_SET    is " << std::fixed << std::setprecision(9) << time_takenSet;
	outFile << " sec" << std::endl << RESET;

	outFile << BLUE << "-------------------------------------------------------\n";
	outFile << "STD_TOTAL                               " << std::fixed << std::setprecision(9) << time_takenVektor + time_takenStack + time_takenMap + time_takenSet;
	outFile << " sec\n" << std::endl << RESET;
	
	outFile.close();

	return (0);
}