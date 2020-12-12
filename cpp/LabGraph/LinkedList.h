#pragma once

//proto
template <typename T>
class LinkedList;

// node class
template<typename T>
class Node
{
	friend LinkedList<T>;
public:
	//Node(const T& _data, const Node* _next = NULL) : data(_data), next(_next) {}; //constructor
	//~Node() { delete[] this.data; }
private:
	T data;
	Node* next; //ptr to the next node
};

template<typename T>
class LinkedList
{
public:
	//constructors
	LinkedList();
	LinkedList(int count);
	LinkedList(const LinkedList<T>& arr);
	//LinkedList(const T* const arr, size_t count, size_t start = 0);
	//functions
	size_t GetLength() const;
	void Set(const T& item, const size_t index);
	T GetFirst() const;
	T GetLast() const;
	T& Get(size_t index) const;
	void Append(const T& value);
	void InsertAt(const T& item, size_t index);
	void Prepend(const T& value);
	bool Equal(const LinkedList<T>& linkedlist) {
		if (this == &linkedlist)
			return true;
		if (this->count == linkedlist.count)
		{
			for (size_t i = 0; i < this->count; i++)
				if (this->Get(i) != linkedlist.Get(i)) {
					return false;
				}
			return true;
		}
		return false;
	}
	void RemoveAt(size_t index);
	//LinkedList<T>* Concat(LinkedList<T>* list);
	//operators
	LinkedList<T>& operator=(const LinkedList<T>& list);
	T& operator[](const size_t index);
	const T& operator[](const size_t index) const;
	inline bool operator==(const LinkedList<T>& linkedlist) { return Equal(linkedlist); }
	inline bool operator!=(const LinkedList<T>& linkedlist) { return !(*this == linkedlist); }
	~LinkedList();
	//~LinkedList() { delete[] this->data; }
private:
	Node<T>* data;
	size_t count;
};

// constructors ------------------------------------------------------------------------------
// empty
template<typename T>
LinkedList<T>::LinkedList()
{
	this->data = NULL;
	this->count = 0;
}
//copy
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) : LinkedList()
{
	for (size_t i = 0; i < list.count; i++)
	{
		this->Append(list.Get(i));
	}
}
/*
//from const arr
template<typename T>
LinkedList<T>::LinkedList(const T* const arr, size_t count, size_t start) : LinkedList()
{
	for (size_t i = 0; i < this->count; i++)
	{
		this->data[i + this->LCap] = arr[i + start];
	}
}
*/

// functions ---------------------------------------------------------------------------------
//get size
template<typename T>
size_t LinkedList<T>::GetLength() const
{
	return this->count;
}
//set element by index
template<typename T>
void LinkedList<T>::Set(const T& item, const size_t index) {
	if (this->count <= index) {
		throw std::exception("IndexOutOfRangeException");
	}
	else {
		Node<T>* tempHead = this->data;
		for (int i = 0; i < index; i++) {
			tempHead = tempHead->next;
		}
		tempHead->data = item;
	}
}
//get element by index
template<typename T>
T& LinkedList<T>::Get(size_t index) const
{
	if (this->count <= index) {
		throw std::exception("IndexOutOfRangeException");
	}
	else if (index == 0) { return this->data->data;  }
	else {
		Node<T>* tempHead = this->data;
		for (int i = 0; i < index; i++) {
			tempHead = tempHead->next;
		}
		return tempHead->data;
	}
}
//get first
template<typename T>
T LinkedList<T>::GetFirst() const
{
	return Get(0);
}
//get last
template<typename T>
T LinkedList<T>::GetLast() const
{
	return Get(this->count - 1);
}
//append
template<typename T>
void LinkedList<T>::Append(const T& value)
{
	Node<T>* temp = new Node<T>;
	temp->data = value;
	temp->next = NULL;

	if (this->data == NULL) {
		this->data = temp;
	}
	else {
		Node<T>* tempHead = this->data; // head is not NULL
		while (tempHead->next != NULL) {
			tempHead = tempHead->next; // go to end of list
		}
		tempHead->next = temp; // linking to newnode
	}

	this->count++;
}
//insertAt
template<typename T>
void LinkedList<T>::InsertAt(const T& item, size_t index)
{
	if (this->count <= index || this->count < 0) {
		throw std::exception("IndexOutOfRangeException");
	}
	else {
		if (index == 0) {
			this->Prepend(item);
			return;
		}
		Node<T>* temp = new Node<T>;
		temp->data = item;

		if (this->data == NULL) {
			temp->next = NULL;
			this->data = temp;
		}
		else {
			Node<T>* tempHead = this->data; // head is not NULL
			for (int i = 0; i < index - 1; i++) {
				tempHead = tempHead->next; // go to index
			}
			temp->next = tempHead->next; // linking temp to next
			tempHead->next = temp; // linking to temp
		}

		this->count++;
	}

}
//prepend
template<typename T>
void LinkedList<T>::Prepend(const T& value)
{
	Node<T>* temp = new Node<T>;
	temp->data = value;

	if (this->data == NULL) {
		temp->next = NULL;
		this->data = temp;
	}
	else {
		temp->next = this->data;
		this->data = temp;
	}

	this->count++;
}
/*
//concat
template<typename T>
LinkedList<T>* LinkedList<T>::Concat(LinkedList<T>* list)
{
	Node* temp = new Node<T>;
	temp->data = value;

	if (this->data == NULL) {
		temp->next = NULL;
		this->data = temp;
	}
	else {
		temp->next = this->data->next;
		this->data = temp;
	}

	this->count++;
}
*/
//removeat element by index
template<typename T>
void LinkedList<T>::RemoveAt(size_t index)
{
	if (this->count <= index || this->count < 0) {
		throw std::exception("IndexOutOfRangeException");
	}
	else {
		if (this->count == 1) {
			delete this->data;
			this->data = NULL;
			this->count = 0;
			return;
		}
		if (index == 0) {
			Node<T>* old = this->data;
			this->data = old->next;
			delete old;
			this->count--;
			return;
		}
		Node<T>* tempHead = this->data; // head is not NULL
		for (int i = 0; i < (index - 1); i++) {
			tempHead = tempHead->next; // go to index
		}
		Node<T>* old = tempHead->next;
		tempHead->next = old->next;
		delete old;
	}

	this->count--;
}

// operators ----------------------------------------------------------------------------------

//let use =
template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list)
{
	if (this == &list)
		return *this;
	delete[] this->data;
	try
	{
		this->data = NULL;
	}
	catch (const std::bad_alloc& exc)
	{
		throw exc.what();
	}
	for (size_t i = 0; i < list.count; i++)
		this->Append(list.data[i]);
	//this->count = list.count;
	return *this;
}

//let use []
template<typename T>
T& LinkedList<T>::operator[](const size_t index)
{
	if (index >= this->count)
		throw std::exception("IndexOutOfRangeException");
	return this->Get(index);
}

template<typename T>
const T& LinkedList<T>::operator[](const size_t index) const
{
	if (index >= this->count)
		throw std::exception("IndexOutOfRangeException");
	return this->Get(index);
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	if (this->data != NULL) {
		Node<T>* tempHead = this->data; // head is not NULL
		while (tempHead->next != NULL) {
			Node<T>* old = tempHead;
			tempHead = tempHead->next; // go to end of list
			delete old;
		}
		delete tempHead;
	}
}