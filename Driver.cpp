#include <iostream>
#include <cassert>
#include <string>
#include "Set.h"
#include "Set.cpp"


template<typename T>
void testfunction();

int main()
{
	testfunction<std::string>();
	system("pause");
	return 0;
}



template<typename T>
void testfunction()
{
	Set<T> s1;
	assert(s1.insert("")); //inserting empty string.
	assert(s1.insert("apple")); // inserting words.
	assert(s1.insert("zulu"));
	assert(s1.insert("george"));
	assert(!s1.insert("apple")); // inserting previous entry.
	assert(!s1.insert(""));
	assert(s1.size() == 4); // expecting 4 entries.

	std::cerr << "dumping s1 after inserting entries" << std::endl;
	s1.dump(); // display list.

	Set<T> s2(s1); //call copy constructor.
	std::cerr << "dumping s2 after calling copy constructor" << std::endl;
	s2.dump(); //check copy constructor works.


	assert(s2.erase("apple")); // check erase function.
	assert(!s2.erase("apple")); // try attempt where entry does not exist.
	assert(s2.erase(""));
	assert(s2.erase("zulu"));
	assert(s2.size() == 1);
	std::cerr << "dumping s2 after deleting entries" << std::endl;
	s2.dump(); //check list values.

	T val;
	assert(s2.get(1, val) && val == "george");
	assert(!s2.get(3, val) && val == "george");
	assert(!s2.get(0, val) && val == "george");

	Set<T> s3;
	
	s1.insert("car");
	s2.insert("truck");


	unite(s1, s2, s3);
	std::cerr << "dumping s3 after unite function" << std::endl;
	s3.dump(); // check unite function.

	subtract(s1, s2, s3);
	std::cerr << "dumping s3 after subtract function" << std::endl;
	s3.dump(); //check subtract function;

	s3.swap(s1);
	std::cerr << "dumping s3 after swapping with s1" << std::endl;
	s3.dump();

	Set<T> emptyset;
	assert(emptyset.empty()); //ensure set is empty;

	s3.swap(emptyset);
	std::cerr << "dumping s3 after swapping with empty set" << std::endl;
	s3.dump();


	s3 = s2 = s1; 
	
	std::cerr << "dumping s1, s2 and s3 after calling operator=" << std::endl;
	s3.dump(); // check operator=
	s2.dump();
	s1.dump();
}
