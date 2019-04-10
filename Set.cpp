#include "Set.h"


//initializes list with dummy node.
template<typename T>
Set<T>::Set()
{
	HeadPtr = new Node;
	iSize = 0;
	HeadPtr->NextPtr = HeadPtr;
	HeadPtr->PrevPtr = HeadPtr;
}


//copy constructor initialzies a new Set, inserts all the data from s and then swaps it with the this set.
template<typename T>
Set<T>::Set(const Set &s)
{
	Set S;
	this->swap(S);
	for (Node* CurrPtr = s.HeadPtr->NextPtr; CurrPtr != s.HeadPtr; CurrPtr = CurrPtr->NextPtr)
		this->insert(CurrPtr->Data);
}



template<typename T>
bool Set<T>::empty() const
{
	return (iSize == 0);
}

template<typename T>
int Set<T>::size() const
{
	return iSize;
	
}


//insert calls the findloc function to find the appropriate place the value should go, 
//then it checks if the value is already placed or not
//if not, it then makes a new node with that value and calls the placeloc function to place it.
template<typename T>
bool Set<T>::insert(const T &value)
{
	Node* BefPtr = findloc(value);
	if (BefPtr != HeadPtr && BefPtr->Data == value)
		return false;
	Node* NewNode = new Node(value);
	placeloc(BefPtr, NewNode);
	iSize++;
	return true;
}


//findloc traverses traverses the list to find the appropriate spot
template<typename T>
typename Set<T>::Node* Set<T>::findloc(const T &value) const
{
	Node* CurrPtr = HeadPtr->NextPtr;
	while (CurrPtr != HeadPtr && CurrPtr->Data <= value)
		CurrPtr = CurrPtr->NextPtr;
	return CurrPtr->PrevPtr;
}

//erase removes a given value from a list (if it exists) by calling the findloc function
//and checking if it is the correct value
template<typename T>
bool Set<T>::erase(const T &value)
{
	Node* CurrPtr = findloc(value);
	if (CurrPtr != HeadPtr && CurrPtr->Data == value)
	{
		CurrPtr->NextPtr->PrevPtr = CurrPtr->PrevPtr;
		CurrPtr->PrevPtr->NextPtr = CurrPtr->NextPtr;
		delete CurrPtr;
		iSize--;
		return true;
	}
	else
		return false;
}

//contains calls the fincloc function and checks if the value is present.
template<typename T>
bool Set<T>::contains(const T &value) const
{
	Node* CurrPtr = findloc(value);
	if (CurrPtr != HeadPtr && CurrPtr->Data == value)
		return true;
	else
		return false;
}

//get returns the value that is greater than the given number of values. 
//thanks to the way the values are stored (in ascending order)
//the number that is bigger than n values is in n^th position
template<typename T>
bool Set<T>::get(int pos, T &value) const
{
	if (0 >= pos || pos > iSize)
		return false;

	Node* CurrPtr = HeadPtr->NextPtr;
	//More efficient way would have been to traverse the list in reverse if the pos is greater than half the size. 
	//I preferred to keep the code cleaner like this.
	for (int i = 0; i < pos - 1; i++)
		CurrPtr = CurrPtr->NextPtr;
	value = CurrPtr->Data;
	return true;
}

//swap simply swaps the headptrs and the size.
template<typename T>
void Set<T>::swap(Set &other)
{
	Node* TempPtr = HeadPtr;
	HeadPtr = other.HeadPtr;
	other.HeadPtr = TempPtr;

	int iTemp = iSize;
	iSize = other.iSize;
	other.iSize = iTemp;
}

//placeloc "stiches" the list with the new node.
template<typename T>
void Set<T>::placeloc(Node* s1, Node* s2)
{
	s1->NextPtr->PrevPtr = s2;
	s2->NextPtr = s1->NextPtr;
	s1->NextPtr = s2;
	s2->PrevPtr = s1;
}



template<typename T>
void unite(const Set<T> &s1, const Set<T> &s2, Set<T> &result)
{
	result = s1;
	T Data;
	for (int i = 1; i <= s2.size(); i++)
	{
		s2.get(i, Data);
		result.insert(Data);
	}
}

template<typename T>
void subtract(const Set<T> &s1, const Set<T> &s2, Set<T> &result)
{
	result = s1;
	T Data;
	for (int i = 1; i <= s2.size(); i++)
	{
		s2.get(i, Data);
		result.erase(Data);
	}

}


//dump is used for debugging
template<typename T>
void Set<T>::dump() const
{
	Node* CurrPtr = HeadPtr->NextPtr;
	while(CurrPtr != HeadPtr)
	{
		std::cerr << CurrPtr->Data << ' ';
		CurrPtr = CurrPtr->NextPtr;
	}
	std::cerr << std::endl;
}


//operator will call copy constructor, and then assign that to the calling set, 
//then it returns the set to allow multiple operator calls on one line (s1 = s2 = s3)
template<typename T>
typename Set<T>::Set &Set<T>::operator=(const Set &s1)
{
	Set<T> Copy(s1);
	swap(Copy);
	return *this;
}




//destructor traverses list and deletes all nodes
template<typename T>
Set<T>::~Set()
{
	Node* CurrPtr = HeadPtr;
	Node* NextCPtr = HeadPtr;
	for (int i = 0; i < iSize; i++)
	{
		NextCPtr = NextCPtr->NextPtr;
		delete CurrPtr;
		CurrPtr = NextCPtr;
	}

}













