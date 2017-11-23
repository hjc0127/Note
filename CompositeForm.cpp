//CompositeForm.cpp

#include "CompositeForm.h"
#include "Contents.h"

CompositeForm::CompositeForm(Contents *contents, Long capacity) 
	:Form(contents), forms(capacity){
	this->capacity = capacity;
	this->length = 0;
}

CompositeForm::~CompositeForm() {
	Long i = 0;
	while (i < this->length) {
		if (this->forms.GetAt(i) != 0) {
			delete this->forms.GetAt(i);
		}
		i++;
	}
}

CompositeForm::CompositeForm(const CompositeForm& source)
	:Form(source.contents), forms(source.capacity) {
	this->capacity = source.capacity;
	this->length = source.length;
}

CompositeForm& CompositeForm::operator=(const CompositeForm& source) {
	Long i = 0;
	while (i < this->length) {
		if (this->forms.GetAt(i) != 0) {
			delete this->forms.GetAt(i);
		}
		i++;
	}

	this->forms = source.forms;
	i = 0;
	while (i < source.length) {
		this->forms.Modify(i, (const_cast<CompositeForm&>(source)).forms.GetAt(i)->Clone());
		i++;
	}
	//this->parentForm = source.parentForm;
	this->capacity = source.capacity;
	this->length = source.length;

	return *this;
}

Long CompositeForm::Add(Form *form) {
	Long index;
	if (this->length < this->capacity) {
		index = this->forms.Store(this->length, form);
	}
	else {
		index = this->forms.AppendFromRear(form);
		this->capacity++;
	}
	this->length++;

	return index;
}

Long CompositeForm::Remove(Long index) {
	if (this->forms.GetAt(index) != 0) {
		delete this->forms.GetAt(index);
	}
	index = this->forms.Delete(index);
	this->capacity--;
	this->length--;

	return index;
}

Form* CompositeForm::GetAt(Long index) {
	return this->forms.GetAt(index);
}

Form* CompositeForm::operator[](Long index) {
	return this->forms[index];
}

Long CompositeForm::Delete(Long index) {
	index = this->forms.Delete(index);
	this->capacity--;
	this->length--;

	return index;
}