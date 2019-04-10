#ifndef SET_H
#define SET_H

/*
Set is a circular, doubly linked list which utilizes a dummy node to streamline it's functions. 
The "data" is stored from lowest to highest value. Each "data" is unique; copies are not stored.
*/

template<typename T>
class Set
{
private:
	struct Node
	{
		Node* NextPtr;
		Node* PrevPtr;
		T Data;
		Node() : NextPtr(nullptr), PrevPtr(nullptr) {};
		Node(const T &D) : NextPtr(nullptr), PrevPtr(nullptr), Data(D) {};
	};
	Node* HeadPtr;
	int iSize;
	//findloc function returns the node which is equal to and/or comes before value.
	typename Node* findloc(const T &value) const;
	//placeloc function places a node after a specified node and links it with the rest of the list
	void placeloc(Node* n1, Node* n2);

public:
	Set();
	Set(const Set &s);
	bool empty() const;
	int size() const;
	bool insert(const T &value);
	bool erase(const T &value);
	bool contains(const T &value) const;
	//get finds the value that is the pos^th largest in the list
	bool get(int pos, T &value) const;
	void swap(Set &s);
	//dump is used for debugging
	void dump() const;
	Set &operator=(const Set &s);
	~Set();
};

//unite will unite two sets and equate it to result
template<typename T>
void unite(const Set<T> &s1, const Set<T> &s2, Set<T> &result);


//subtract will remove all the data from s1 that is present in s2 and place it in result
template<typename T>
void subtract(const Set<T> &s1, const Set<T> &s2, Set<T> &result);

#endif

