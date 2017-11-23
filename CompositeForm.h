#pragma once
//CompositeForm.h

#ifndef _COMPOSITEFORM_H
#define _COMPOSITEFORM_H

#include "Form.h"
#include "Array.h"
#include "ArrayIterator.h"

typedef signed long int Long;

class Contents;
class CompositeForm : public Form {
public :
	CompositeForm(Contents *contents = 0, Long capacity = 64);
	virtual ~CompositeForm() = 0;
	CompositeForm(const CompositeForm& source);
	CompositeForm& operator=(const CompositeForm& source);

	virtual Long Add(Form *form);
	virtual Long Remove(Long index);
	virtual Long Delete(Long index);
	Form* GetAt(Long index);
	Form* operator[](Long index);
	virtual ArrayIterator<Form*>* CreateIterator() const = 0;

	Array<Form*> GetForms() const;
	Long GetCapacity() const;
	Long GetLength() const;
protected :
	Array<Form*> forms;
	Long capacity;
	Long length;
};

inline Array<Form*> CompositeForm::GetForms() const {
	return this->forms;
}

inline Long CompositeForm::GetCapacity() const {
	return this->capacity;
}

inline Long CompositeForm::GetLength() const {
	return this->length;
}

#endif	//_COMPOSITEFORM_H