#pragma once
#include "Sequence.h"

// record structure
template <typename T>
struct Item {
	T item;
	int priority;
};
//template <typename T>
//using ItemList = LinkedListSequence<T>;

template<typename T>
class PriorityQueue
{
public:
	// constructors --------------------------------------------------------
	PriorityQueue() {
		this->list = new LinkedListSequence<Item<T>>;
	}

	// functions -----------------------------------------------------------
	void Enqueue(T item, int priority) {
		Item<T> newItem = Item<T>();
		newItem.item = item;
		newItem.priority = priority;
		if (list->GetLength() == 0) {
			list->Append(newItem);
			return;
		}
		for (int i = 0; i < list->GetLength(); i++) {
			Item<T> currentItem = list->Get(i);
			if (priority <= currentItem.priority) {
				list->InsertAt(newItem, i);
				return;
			}
		}
		list->Append(newItem);
		return;
	}

	T Dequeue() {
		T temp = (list->GetFirst()).item;
		list->RemoveAt(0);
		return temp;
	}

	T Peek(const size_t index) {
		return (this->list->Get(index)).item;
	}

	T PeekFirst() {
		return (list->GetFirst()).item;
	}

	T PeekLast() {
		return (list->GetLast()).item;
	}

	bool IsEmpty() {
		return list->GetLength() == 0;
	}

	// operators -----------------------------------------------------------
	Item<T> operator[](const size_t index) {
		return this->Peek(index);
	}

	const Item<T> operator[](const size_t index) const {
		return this->Peek(index);
	}

	~PriorityQueue() {
		delete this->list;
	}

private:
	LinkedListSequence<Item<T>>* list;
};
