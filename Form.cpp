//Form.cpp

#include "Form.h"
#include "Contents.h"
#include "Composite.h"
#include "CompositeForm.h"
#include "OtherNoteForm.h"


Form::Form(Contents *contents) {
	this->contents = contents;
	//this->parentForm = parentForm;
}

Form::~Form() {
	//if (this->parentForm == NULL) {
	//	if (this->contents != 0) {
	//		delete this->contents;
	//	}
	//}
	//else {
	//	Long i = 0;
	//	while (static_cast<CompositeForm*>(this->GetParentForm())->GetAt(i) != this) {
	//		i++;
	//	}
	//	static_cast<Composite*>(static_cast<CompositeForm*>(this->GetParentForm())->GetContents())->Remove(i);
	//}
}

Form::Form(const Form& source) {
	this->contents = source.contents;
	//this->parentForm = source.parentForm;
}

Form& Form::operator = (const Form& source) {
	this->contents = source.contents;
	//this->parentForm = source.parentForm;

	return *this;
}

void Form::SetContents(Contents *contents) {
	this->contents = contents;
}