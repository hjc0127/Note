//Composite.cpp

#include "Composite.h"

Composite::Composite(Long capacity)
	:contents(capacity) {
	this->capacity = capacity;
	this->length = 0;
}

Composite::Composite(const Composite& source)
	: contents(source.capacity) {
	Long i = 0;
	while (i < source.length) {
		this->contents.Store(i, (const_cast<Composite&>(source)).contents.GetAt(i)->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}

Composite::~Composite() {
	Long i = 0;
	while (i < this->length) {
		if (this->contents.GetAt(i) != 0) {
			delete this->contents.GetAt(i);
		}
		i++;
	}
}

Composite& Composite::operator=(const Composite& source) {
	Long i = 0;
	while (i < this->length) {
		if (this->contents.GetAt(i) != 0) {
			delete this->contents.GetAt(i);
		}
		i++;
	}

	this->contents = source.contents;
	i = 0;
	while (i < source.length) {
		this->contents.Modify(i, (const_cast<Composite&>(source)).contents.GetAt(i)->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	return *this;
}

Long Composite::Add(Contents *contentsLink) {
	Long index;
	if (this->capacity > this->length) {
		index = this->contents.Store(this->length, contentsLink);
	}
	else {
		index = this->contents.AppendFromRear(contentsLink);
		this->capacity++;
	}
	this->length++;

	return index;
}

Long Composite::Insert(Long index, Contents *contents) {
	index = this->contents.Insert(index, contents);
	this->capacity++;
	this->length++;

	return index;
}

Long Composite::Remove(Long index) {
	if (this->contents[index] != 0) {
		delete this->contents[index];
	}
	index = this->contents.Delete(index);
	this->capacity--;
	this->length--;

	return index;
}

Long Composite::Delete(Long index) {
	index = this->contents.Delete(index);
	this->capacity--;
	this->length--;

	return index;
}

Contents* Composite::GetAt(Long index) {
	return this->contents.GetAt(index);
}

Contents* Composite::operator[](Long index) {
	return this->contents[index];
}

//Contents* Composite::operator+(Long index) {
//	return this->contents + index;
//}

//ArrayIterator<Contents*>* Composite::CreateIterator() const {
//	return const_cast<ArrayIterator<Contents*>*>(new ArrayIterator<Contents*>(&this->contents));
//}