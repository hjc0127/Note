#pragma once
// ArrayIterator.h

#ifndef _ARRAYITERATOR_H
#define _ARRATITERATOR_H

#include "Iterator.h"
#include "Array.h"

template <class Item>
class ArrayIterator : public Iterator<Item> {
public:
	ArrayIterator(const Array<Item>* aArray);
	ArrayIterator(const ArrayIterator& source);
	virtual ~ArrayIterator();
	ArrayIterator& operator=(const ArrayIterator& source);
	virtual void First();
	virtual void Next();
	virtual bool IsDone() const;
	virtual Item CurrentItem() const;
	virtual Item GetItem(Long index) const;
	Long GetCurrent();
private:
	const Array<Item> *_array;
	Long _current;
};

template <class Item>
ArrayIterator<Item>::ArrayIterator(const Array<Item> *aArray)
	:Iterator(), _array(aArray), _current(0) {

}

template <class Item>
ArrayIterator<Item>::ArrayIterator(const ArrayIterator& source)
	:Iterator(source) {
	this->_array = source._array;
	this->_current = source._current;
}

template <class Item>
ArrayIterator<Item>::~ArrayIterator() {

}

template <class Item>
ArrayIterator<Item>& ArrayIterator<Item>::operator=(const ArrayIterator& source) {
	Iterator::operator=(source);
	this->_array = source._array;
	this->_current = source._current;

	return *this;
}

template <class Item>
void ArrayIterator<Item>::First() {
	this->_current = 0;
}

template <class Item>
void ArrayIterator<Item>::Next() {
	this->_current++;
}

template <class Item>
bool ArrayIterator<Item>::IsDone() const {
	return this->_current >= _array->GetLength();
}

template <class Item>
Item ArrayIterator<Item>::CurrentItem() const {
	//if (IsDone()) {
	//	throw IteratorOutOfBounds;
	//}

	return const_cast<Array<Item>*>(this->_array)->GetAt(this->_current);
}

template <class Item>
inline Long ArrayIterator<Item>::GetCurrent() {
	return this->_current;
}

template <class Item>
Item ArrayIterator<Item>::GetItem(Long index) const {
	return const_cast<Array<Item>*>(this->_array)->GetAt(index);
}

#endif // ARRAYITERATOR_H