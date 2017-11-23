//FindingFormAction.cpp

#include "FindingFormAction.h"
#include "Form.h"

FindingFormAction::FindingFormAction(Form *form)
{
	this->form = form;
}

FindingFormAction::FindingFormAction(const FindingFormAction& source) {
	this->form = source.form;
}

FindingFormAction::~FindingFormAction() {

}

FindingFormAction& FindingFormAction::operator=(const FindingFormAction& source) {
	this->form = source.form;

	return *this;
}