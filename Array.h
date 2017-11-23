#pragma once
//Array.h

//Guard 선언
#ifndef _ARRAY_H
#define _ARRAY_H

//자료형 선언
typedef signed long int Long;

template <typename T>
class Array{
public:
	Array(Long capacity = 100);
	Array(const Array& source);
	~Array();
	Long Store(Long index, T object);
	Long Insert(Long index, T object);
	Long AppendFromFront(T object);
	Long AppendFromRear(T object);
	Long Delete(Long index);
	Long DeleteFromFront();
	Long DeleteFromRear();
	void Clear();
	Long Modify(Long index, T object);
	Long LinearSearchUnique(void *key, int(*compare)(void *, void *));
	void LinearSearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void *, void *));
	Long BinarySearchUnique(void *key, int(*compare)(void *, void *));
	void BinarySearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void *, void *));
	void SelectionSort(int(*compare)(void *, void *));
	void BubbleSort(int(*compare)(void *, void *));
	void InsertionSort(int(*compare)(void *, void *));
	void MergeSort(const Array& one, const Array& other, int(*compare)(void *, void *));
	T& GetAt(Long index);
	Array& operator=(const Array& source);
	T& operator[](Long index);
	T* operator+(Long index);
	Long GetCapacity() const;
	Long GetLength() const;
private:
	T(*front);
	Long capacity;
	Long length;
};

template <typename T>
inline Long Array<T>::GetCapacity() const {
	return this->capacity;
}

template <typename T>
inline Long Array<T>::GetLength() const {
	return this->length;
}

template <typename T>
Array<T>::Array(Long capacity) {
	this->front = new T[capacity];
	this->capacity = capacity;
	this->length = 0;
}

template <typename T>
Array<T>::Array(const Array& source) {
	this->front = new T[source.capacity];
	
	Long i = 0;
	while (i < source.length) {
		this->front[i] = source.front[i];
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;
}

template <typename T>
Array<T>::~Array() {
	if (this->front != 0) {
		delete[] this->front;
	}
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& source) {
	if (this->front != 0) {
		delete[] this->front;
	}

	this->front = new T[source.capacity];

	Long i = 0;
	while (i < source.length) {
		this->front[i] = source.front[i];
		i++;
	}

	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

template <typename T>
Long Array<T>::Store(Long index, T object) {
	this->front[index] = object;
	this->length++;

	return index;
}

template <typename T>
Long Array<T>::Insert(Long index, T object) {
	T(*temp);
	temp = new T[this->capacity + 1];

	Long i = 0;
	while (i < index) {
		temp[i] = this->front[i];
		i++;
	}
	while (i < this->length) {
		temp[i + 1] = this->front[i];
		i++;
	}

	if (this->front != 0) {
		delete[] this->front;
	}

	this->front = temp;

	this->capacity++;
	this->front[index] = object;
	this->length++;

	return index;
}

template <typename T>
Long Array<T>::AppendFromFront(T object) {
	Long index = 0;
	T(*temp);

	temp = new T[this->capacity + 1];

	Long i = 0;
	while (i < this->length) {
		temp[i + 1] = this->front[i];
		i++;
	}

	if (this->front != 0) {
		delete[] this->front;
	}

	this->front = temp;

	this->capacity++;
	this->front[index] = object;
	this->length++;

	return index;
}

template <typename T>
Long Array<T>::AppendFromRear(T object) {
	Long index;
	T(*temp);

	temp = new T[this->capacity + 1];

	Long i = 0;
	while (i < this->length) {
		temp[i] = this->front[i];
		i++;
	}
	
	if (this->front != 0) {
		delete[] this->front;
	}

	this->front = temp;

	this->capacity++;
	index = this->capacity - 1;
	this->front[index] = object;
	this->length++;

	return index;
}

template <typename T>
Long Array<T>::Delete(Long index) {
	T(*temp)=0;

	if (this->capacity > 1) {
		temp = new T[this->capacity - 1];
	}

	Long j = 0;
	Long i = 0;
	while (i < index) {
		temp[j] = this->front[i];
		j++;
		i++;
	}
	i = index + 1;
	while (i < this->length) {
		temp[j] = this->front[i];
		j++;
		i++;
	}

	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}

	if (this->capacity > 1) {
		this->front = temp;
	}

	this->length--;
	this->capacity--;
	index = -1;

	return index;
}

template <typename T>
Long Array<T>::DeleteFromFront() {
	T(*temp);

	if (this->capacity > 1) {
		temp = new T[this->capacity - 1];
	}

	Long i = 1;
	while (i < this->length) {
		temp[i - 1] = this->front[i];
		i++;
	}

	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}

	if (this->capacity > 1) {
		this->front = temp;
	}

	this->length--;
	this->capacity--;
	Long index = -1;

	return index;
}

template <typename T>
Long Array<T>::DeleteFromRear() {
	T(*temp);

	if (this->capacity > 1) {
		temp = new T[this->capacity - 1];
	}

	Long i = 0;
	while (i < this->capacity - 1) {
		temp[i] = this->front[i];
		i++;
	}

	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}

	if (this->capacity > 1) {
		this->front = temp;
	}

	this->length--;
	this->capacity--;
	Long index = -1;

	return index;
}

template <typename T>
void Array<T>::Clear() {
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}

	this->length = 0;
	this->capacity = 0;
}

template <typename T>
Long Array<T>::Modify(Long index, T object) {
	this->front[index] = object;

	return index;
}

template <typename T>
Long Array<T>::LinearSearchUnique(void *key, int(*compare)(void *, void *)) {
	Long index = -1;
	
	Long i = 0;
	while (i < this->length && compare(this->front + i, key) != 0) {
		i++;
	}

	if (i < this->length) {
		index = i;
	}

	return index;
}

template <typename T>
void Array<T>::LinearSearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void *, void *)) {
	Long index = 0;

	*count = 0;
	*indexes = new Long[this->length];
	
	Long i = 0;
	while (i < this->length) {
		if (compare(this->front + i, key) == 0) {
			(*indexes)[index] = i;
			index++;
			(*count)++;
		}
		i++;
	}
}

template <typename T>
Long Array<T>::BinarySearchUnique(void *key, int(*compare)(void *, void *)) {
	Long index = -1;
	Long begin = 0;
	Long end = this->length - 1;
	
	Long middle = (begin + end) / 2;
	while (begin <= end && compare(this->front + middle, key) != 0) {
		if (compare(this->front + middle, key) < 0) {
			begin = middle + 1;
		}
		else {
			end = middle - 1;
		}
		middle = (begin + end) / 2;
	}

	if (begin <= end) {
		index = middle;
	}

	return index;
}

template <typename T>
void Array<T>::BinarySearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void *, void *)) {
	*indexes = 0;
	*count = 0;
	Long index = -1;
	Long i = 0;

	Long begin = 0;
	Long end = this->length - 1;
	Long middle = (begin + end) / 2;
	while (begin <= end && compare(this->front + middle, key) != 0) {
		if (compare(this->front + middle, key) < 0) {
			begin = middle + 1;
		}
		else {
			end = middle - 1;
		}
		middle = (begin + end) / 2;
	}

	if (middle >= begin && middle <= end) {
		*indexes = new T[this->length];
		index = middle;
	}

	while (index >= begin && compare(this->front + index, key) == 0) {
		index--;
	}
	index++;

	while (index <= end && compare(this->front + index, key) == 0) {
		(*indexes)[i] = index;
		(*count)++;
		i++;
		index++;
	}
}

//template <typename T>
//void Array<T>::BinarySearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void *, void*)) {
//	*indexes = 0;
//	*count = 0;
//
//	Long begin = 0;
//	Long end = this->length - 1;
//	Long middle = (begin + end) / 2;
//	while (begin <= end && compare(this->front + middle, key) != 0) {
//		if (compare(this->front + middle, key) < 0) {
//			begin = middle + 1;
//		}
//		else {
//			end = middle - 1;
//		}
//		middle = (begin + end) / 2;
//	}
//
//	Long index = middle;
//	Long i = index + 1;
//	while (i >= begin && compare(this->front + i, key) == 0) {
//		i--;
//	}
//
//	Long keyBegin = i + 1;
//
//	i = keyBegin;
//	while (i <= end && compare(this->front + i, key) == 0) {
//		(*count)++;
//		i++;
//	}
//
//	Long keyEnd = i - 1;
//
//	if (*count > 0) {
//		*indexes = new Long[this->length];
//	}
//
//	i = keyBegin;
//	while (i <= keyEnd && compare(this->front + i, key) == 0) {
//		(*indexes)[j] = i;
//		j++;
//		i++;
//	}
//}

template <typename T>
void Array<T>::SelectionSort(int(*compare)(void *, void *)) {
	T temp;
	Long i = 0;
	Long j;

	while (i < this->length - 1) {
		j = i + 1;
		while (j < this->length) {
			if (compare(this->front + i, this->front + j) > 0) {
				temp = this->front[j];
				this->front[j] = this->front[i];
				this->front[i] = temp;
			}
			j++;
		}
		i++;
	}
}

template <typename T>
void Array<T>::BubbleSort(int(*compare)(void *, void *)) {
	T temp;
	Long i = 0;
	Long j;
	while (i < this->length - 1) {
		j = 0;
		while (j < this->length - 1 - i) {
			if (compare(this->front + j, this->front + j + 1) > 0) {
				temp = this->front[j];
				this->front[j] = this->front[j + 1];
				this->front[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

template <typename T>
void Array<T>::InsertionSort(int(*compare)(void *, void *)) {
	T temp;

	Long i = 1;
	Long j;
	while (i < this->length) {
		temp = this->front[i];
		j = i - 1;
		while (j >= 0 && compare(this->front + j, this->front + i) > 0) {
			this->front[j + 1] = this->front[j];
			j--;
		}

		this->front[j + 1] = temp;
		i++;
	}
}

//template <typename T>
//void Array<T>::InsertionSort(int(*compare)(void *, void *)) {
//	T temp;
//	
//	Long j;
//	Long i = 1;
//	while (i < this->length) {
//		temp = this->front[i];
//		j = i - 1;
//		while (j >= 0 && compare(this->front + i, this->front + j) < 0) {
//			j--;
//		}
//		k = i;
//		j++;
//		while (k > j) {
//			this->front[k] = this->front[k - 1];
//			k--;
//		}
//		this->front[i] = temp;
//		i++;
//	}
//}

template <typename T>
void Array<T>::MergeSort(const Array& one, const Array& other, int(*compare)(void *, void *)) {
	if (this->front != 0) {
		delete[] this->front;
	}

	this->front = new T[one.length + other.length];
	this->capacity = one.length + other.length;

	Long i = 0;
	Long j = 0;
	Long k = 0;
	while (i < one.length && j < other.length) {
		if (compare(one.front + i, other.front + j)<0) {
			this->front[k] = one.front[i];
			i++;
		}
		else {
			this->front[k] = other.front[j];
			j++;
		}
		k++;
	}

	while (i < one.length) {
		this->front[k] = one.front[i];
		k++;
		i++;
	}

	while (j < other.length) {
		this->front[k] = other.front[j];
		k++;
		j++;
	}

	this->length = one.length + other.length;
}

template <typename T>
T& Array<T>::GetAt(Long index) {
	return this->front[index];
}

template <typename T>
T& Array<T>::operator[](Long index) {
	return this->front[index];
}

template <typename T>
T* Array<T>::operator+(Long index) {
	return this->front + index;
}

#endif	//_ARRAY_H