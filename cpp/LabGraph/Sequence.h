#pragma once
#include "DynamicArray.h"
#include "LinkedList.h"
#include <iostream>

template <typename T>
class Sequence
{
public:
	virtual size_t GetLength() const = 0;
	virtual void Set(T item, const size_t index) = 0;
	virtual T Get(const size_t index) const = 0;
	virtual T GetFirst() const = 0;
	virtual T GetLast() const = 0;
	virtual void Append(T element) = 0;
	virtual void Prepend(T element) = 0;
	virtual void InsertAt(T element, const size_t index) = 0;
	virtual Sequence<T>* GetSubSequence(const size_t start, const size_t end) = 0;
	virtual Sequence<T>* Concat(Sequence<T>* other) = 0;
	//virtual bool Equal(const Sequence<T>* sequence) = 0;
	virtual void RemoveAt(size_t index) = 0;
	virtual void Swap(size_t indexA, size_t indexB) = 0;
	// operators -----------------------------------------------------------
	//virtual Sequence<T>* operator=(const Sequence<T>* sequence) = 0;
	virtual T& operator[](const size_t index) = 0;
	virtual const T& operator[](const size_t index) const = 0;
	//virtual inline bool operator==(const Sequence<T>* sequence) = 0;
	//virtual inline bool operator!=(const Sequence<T>* sequence) = 0;
	//friend std::ostream& operator<<(std::ostream& os, Sequence<T> const& sequence);
	virtual ~Sequence() {}
};

template <class T> class ArraySequence : public Sequence<T> {
public:
	// constructors --------------------------------------------------------
	ArraySequence(T* items, int count) : dynamicarray(items, count) {
	}

	ArraySequence() : dynamicarray(0) {
	}

	ArraySequence(int count) : dynamicarray(count) {
	}

	ArraySequence(int count, T fillItem) : dynamicarray(count) {
		for (int i = 0; i < count; i++) {
			this->Set(fillItem, i);
		}
	}

	ArraySequence(const DynamicArray<T>& dynarr) : dynamicarray(dynarr) {
	}

	ArraySequence(const ArraySequence<T>& dynarr) : dynamicarray(dynarr.dynamicarray) {
	}

	// functions -----------------------------------------------------------
	size_t GetLength() const override {
		return dynamicarray.Size();
	}

	void Set(T item, const size_t index) override {
		return dynamicarray.Set(item, index);
	}

	T Get(const size_t index) const override {
		return dynamicarray.Get(index);
	}

	T GetFirst() const override {
		return dynamicarray.Get(0);
	}

	T GetLast() const override {
		return dynamicarray.Get(dynamicarray.Size() - 1);
	}

	void Append(T item) override {
		size_t newSize = dynamicarray.Size() + 1;
		dynamicarray.Resize(newSize);
		dynamicarray.Set(item, newSize - 1);
	}

	void Prepend(T item) override {
		int newSize = dynamicarray.Size() + 1;
		DynamicArray<T> newdynarr(newSize);
		newdynarr.Set(item, 0);
		for (int i = 0; i < newSize; i++) {
			newdynarr.Set(dynamicarray.Get(i), i + 1);
		}
		dynamicarray = newdynarr;
	}

	void InsertAt(T item, const size_t index) override {
		int newSize = dynamicarray.Size() + 1;
		DynamicArray<T> newdynarr(newSize);
		int j = 0;
		for (int i = 0; i < newSize; ++i) {
			if (i == index) {
				newdynarr.Set(item, i);
				continue;
			}
			newdynarr.Set(dynamicarray.Get(j), i);
			j++;
		}
		dynamicarray = newdynarr;
	}

	Sequence<T>* GetSubSequence(const size_t start, const size_t end) override {
		if ((end < 0) || (start < 0) || (start >= GetLength()) || (end >= GetLength()) || (start > end)) {
			throw std::exception("IndexOutOfRangeException");
		}
		int large = end - start + 1;
		ArraySequence<T>* newdynarr = new ArraySequence<T>;
		int j = 0;
		for (int i = 0; i < GetLength(); ++i) {
			if ((i >= start) && (i <= end)) {
				newdynarr->InsertAt(Get(i), j);
				j++;
			}
		}
		return newdynarr;
	}

	Sequence<T>* Concat(Sequence<T>* list) override {
		ArraySequence<T>* newdynarr = new ArraySequence<T>;
		for (int i = 0; i < GetLength(); i++) {
			newdynarr->InsertAt(Get(i), i);
		}
		int j = 0;
		for (int i = GetLength(); i < GetLength() + list->GetLength(); i++) {
			newdynarr->InsertAt(list->Get(j), i);
			j++;
		}

		return newdynarr;
	}

	/*
	bool Equal(const Sequence<T>* sequence) {
		return false;
		//DynamicArray<T> seq(*((DynamicArray<T>*) sequence));
		//return dynamicarray.Equal(seq);
	}
	*/

	void RemoveAt(size_t index) {
		dynamicarray.RemoveAt(index);
	}

	void Swap(size_t indexA, size_t indexB)
	{
		T buffer = this->Get(indexA);
		this->Set(this->Get(indexB), indexA);
		this->Set(buffer, indexB);
	}

	// operators ------------------------------------------------------------
	/*
	Sequence<T>* operator=(const Sequence<T>* sequence) {
		return dynamicarray->operator=(sequence);
	}
	*/

	T& operator[](const size_t index) override {
		return dynamicarray[index];
	}

	const T& operator[](const size_t index) const {
		return dynamicarray[index];
	}

	/*
	inline bool operator==(const Sequence<T>* sequence) {
		return this->Equal(sequence);
	}

	inline bool operator!=(const Sequence<T>* sequence) {
		return !this->Equal(sequence);
	}
	*/

	~ArraySequence() {}

private:
	DynamicArray<T> dynamicarray;
};

template <class T> class LinkedListSequence : public Sequence<T> {
public:
	// constructors --------------------------------------------------------
	LinkedListSequence(T* item, int count) :linkedlist(item, count) {
	}

	LinkedListSequence() :linkedlist() {
	}

	LinkedListSequence(const LinkedList<T>& list) :linkedlist(list) {
	}

	LinkedListSequence(const LinkedListSequence<T>& list) : linkedlist(list.linkedlist) {
	}

	// functions -----------------------------------------------------------
	size_t GetLength() const override {
		return linkedlist.GetLength();
	}

	void Set(T element, const size_t index) override {
		return linkedlist.Set(element, index);
	}

	T Get(const size_t index) const override {
		return linkedlist.Get(index);
	}

	T GetFirst() const override {
		return linkedlist.GetFirst();
	}

	T GetLast() const override {
		return linkedlist.GetLast();
	}

	void Append(T item) override {
		linkedlist.Append(item);
	}

	void Prepend(T item) override {
		linkedlist.Prepend(item);
	}

	void InsertAt(T item, const size_t index) override {
		linkedlist.InsertAt(item, index);
	}

	Sequence<T>* GetSubSequence(const size_t start, const size_t end) override {
		int length = GetLength();
		if (start > end || (start < 0) || (end < 0) || (end >= length) || (start >= length)) {
			throw std::exception("IndexOutOfRangeException");
		}
		LinkedListSequence<T>* newlinkedlist = new LinkedListSequence<T>;
		for (int i = start; i <= end; ++i) {
			newlinkedlist->Append(Get(i));
		}
		return newlinkedlist;
	}

	Sequence<T>* Concat(Sequence<T>* list) override {
		LinkedListSequence<T>* newlinkedlist = new LinkedListSequence<T>;
		for (int i = 0; i < GetLength(); i++) {
			newlinkedlist->Append(Get(i));
		}
		int j = 0;
		for (int i = GetLength(); i < GetLength() + list->GetLength(); i++) {
			newlinkedlist->Append(list->Get(j));
			j++;
		}
		return newlinkedlist;
	}

	/*
	bool Equal(const Sequence<T>* sequence) {

		if (this == sequence)
			return true;
		if (this->GetLength() == sequence->GetLength())
		{
			for (size_t i = 0; i < this->GetLength(); i++)
				if (this->Get(i) != sequence->Get(i)) {
					return false;
				}
			return true;
		}
		return false;
		//return linkedlist.Equal(*((const LinkedList<T>*) sequence));
	}
	*/

	void RemoveAt(size_t index) {
		linkedlist.RemoveAt(index);
	}

	void Swap(size_t indexA, size_t indexB)
	{
		T buffer = this->Get(indexA);
		this->Set(this->Get(indexB), indexA);
		this->Set(buffer, indexB);
	}

	// operators ------------------------------------------------------------
	/*
	Sequence<T>* operator=(const LinkedList<T>* sequence) {
		return linkedlist=sequence;
	}
	*/

	T& operator[](const size_t index) override {
		return linkedlist[index];
	}

	const T& operator[](const size_t index) const {
		return linkedlist[index];
	}

	/*
	inline bool operator==(const Sequence<T>* sequence) {
		return this->Equal(sequence);
	}

	inline bool operator!=(const Sequence<T>* sequence) {
		return !this->Equal(sequence);
	}
	*/

	~LinkedListSequence() {}

private:
	LinkedList<T> linkedlist;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, Sequence<T>* sequence) {
	for (int i = 0; i < sequence->GetLength(); i++) {
		os << sequence->Get(i) << ' ';
	}
	//os << std::endl;
	return os;
}