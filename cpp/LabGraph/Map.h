#pragma once
#include "Sequence.h"

// record structure
template<typename T>
struct Item {
	T value;
};

template<typename T>
class Map
{
public:
	// constructors --------------------------------------------------------
	Map() {
		this->list = new LinkedListSequence<Item<T>>;
	}

	// functions -----------------------------------------------------------
	void Add(T item, int index) {

	}

	StringList* GetList() {
		return this->list;
	}

	size_t GetLength() {
		return this->list->GetLength();
	}

	Item GetRecord(const size_t index) {
		return (*(this->list))[index];
	}

	String GetWord(const size_t index) {
		return (*(this->list))[index].value;
	}

	int GetWordCount(const size_t index) {
		return (*(this->list))[index].count;
	}

	ArraySequence<int> GetWordEntries(const size_t index) {
		return (*(this->list))[index].entries;
	}

	// operators -----------------------------------------------------------
	T operator[](const size_t index) {
		return this->GetWord(index);
	}

	const T operator[](const size_t index) const {
		return this->Get(index);
	}

	~Map() { 
		delete this->list;
	}
private:
	LinkedListSequence<Item<T>>* list;
};