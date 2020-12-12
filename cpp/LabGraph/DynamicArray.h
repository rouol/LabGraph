#pragma once
#define DEFAULT_BUFFER_SIZE 16


template<typename T>
class DynamicArray
{
public:
	//constructors
	DynamicArray(size_t size = 0);
	DynamicArray(size_t size, const T& default_element);
	DynamicArray(const T* const arr, size_t count, size_t start = 0);
	DynamicArray(const DynamicArray<T>& arr);
	//functions
	T& Get(size_t index) const;
	void Set(const T& value, size_t index);
	void Resize(size_t newSize);
	size_t Size() const;
	size_t Capacity() const;
	size_t RCapacity() const;
	bool Equal(const DynamicArray<T>& dynarr) {
		if (this == &dynarr)
			return true;
		if (this->count == dynarr.count)
		{
			for (size_t i = 0; i < this->count; i++)
				if (this->data[i] != dynarr.data[i]) {
					return false;
				}
			return true;
		}
		return false;
	}
	void RemoveAt(size_t index);
	//operators
	DynamicArray<T>& operator=(const DynamicArray<T>& arr);
	T& operator[](const size_t index);
	const T& operator[](const size_t index) const;
	inline bool operator==(const DynamicArray<T>& dynarr) { return Equal(dynarr); }
	inline bool operator!=(const DynamicArray<T>& dynarr) { return !(*this == dynarr); }
	~DynamicArray() { delete[] this->data; }
private:
	T* data;
	size_t LCap;
	size_t RCap;
	size_t count;
};

// constructors ------------------------------------------------------------------------------
// by size
template<typename T>
DynamicArray<T>::DynamicArray(size_t size)
{
	this->LCap = this->RCap = DEFAULT_BUFFER_SIZE;
	this->count = size;
	try
	{
		this->data = new T[this->Capacity()];
	}
	catch (const std::bad_alloc& exc)
	{
		throw exc.what();
	}
}

//by size, fill in with def
template<typename T>
DynamicArray<T>::DynamicArray(size_t size, const T& default_element) : DynamicArray(size)
{
	for (size_t i = 0; i < this->count; i++)
		this->data[i + this->LCap] = default_element;
}

//from const arr
template<typename T>
DynamicArray<T>::DynamicArray(const T* const arr, size_t count, size_t start) : DynamicArray(count)
{
	for (size_t i = 0; i < this->count; i++)
	{
		this->data[i + this->LCap] = arr[i + start];
	}
}

//copy
template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& arr) : DynamicArray(arr.count)
{
	for (size_t i = 0; i < this->count; i++)
	{
		this->data[i + this->LCap] = arr.data[i + arr.LCap];
	}
}

// functions ---------------------------------------------------------------------------------
//get element by index
template<typename T>
T& DynamicArray<T>::Get(size_t index) const
{
	return index < this->count ? this->data[index + this->LCap] : throw std::exception("IndexOutOfRangeException");
}

//set element by index
template<typename T>
void DynamicArray<T>::Set(const T& value, size_t index)
{
	if (index < this->count) {
		this->data[index + this->LCap] = value;
	}
	else {
		throw std::exception("IndexOutOfRangeException");
	}
	//index < this->count ? this->data[index + this->LCap] = value : throw std::exception("IndexOutOfRangeException");
}

//resize dynarr
template<typename T>
void DynamicArray<T>::Resize(size_t newSize)
{
	if (newSize > (this->count + this->RCap))
	{
		T* newdynarr;
		try
		{
			newdynarr = new T[newSize + DEFAULT_BUFFER_SIZE + DEFAULT_BUFFER_SIZE];
		}
		catch (const std::bad_alloc& exc)
		{
			throw exc.what();
		}
		for (size_t i = 0; i < this->count; i++)
			newdynarr[i + DEFAULT_BUFFER_SIZE] = this->data[i + this->LCap];
		delete[] this->data;
		this->data = newdynarr;
		this->LCap = DEFAULT_BUFFER_SIZE;
		this->RCap = DEFAULT_BUFFER_SIZE;
	}
	else
	{
		this->RCap += this->count - newSize;
	}
	this->count = newSize;
}

//get size
template<typename T>
size_t DynamicArray<T>::Size() const
{
	return this->count;
}

//get cap
template<typename T>
size_t DynamicArray<T>::Capacity() const
{
	return this->count + this->LCap + this->RCap;
}

//get right cap
template<typename T>
size_t DynamicArray<T>::RCapacity() const
{
	return this->RCap;
}

//removeat element by index
template<typename T>
void DynamicArray<T>::RemoveAt(size_t index)
{
	return;
}


// operators ----------------------------------------------------------------------------------
//let use =
template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& arr)
{
	if (this == &arr)
		return *this;
	if (this->Capacity() < arr.count)
	{
		delete[] this->data;
		try
		{
			this->data = new T[arr.count + this->RCap + this->LCap];
		}
		catch (const std::bad_alloc& exc)
		{
			throw exc.what();
		}
	}
	else
	{
		size_t newLCap = (this->Capacity() - arr.count) / 2;
		size_t newRCap = this->Capacity() - arr.count - newLCap;

		this->LCap = newLCap;
		this->RCap = newRCap;
		//for (size_t i = 0; i < this->Capacity(); i++)
		//	this->data[i] = std::nullopt;
	}
	for (size_t i = 0; i < arr.count; i++)
		this->data[i + this->LCap] = arr.data[i + arr.LCap];
	this->count = arr.count;
	return *this;
}

//let use []
template<typename T>
T& DynamicArray<T>::operator[](const size_t index)
{
	if (index >= this->count)
		throw std::exception("IndexOutOfRangeException");
	else return this->data[index + this->LCap];
}

template<typename T>
const T& DynamicArray<T>::operator[](const size_t index) const
{
	if (index >= this->count)
		throw std::exception("IndexOutOfRangeException");
	else return this->data[index + this->LCap];
}