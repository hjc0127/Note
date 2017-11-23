//KeyAction.cpp

#include "KeyAction.h"
#include "Form.h"

KeyAction::KeyAction(Form *form)
{
	this->form = form;
}

KeyAction::KeyAction(const KeyAction& source) {
	this->form = source.form;
}

KeyAction::~KeyAction() {

}

KeyAction& KeyAction::operator=(const KeyAction& source) {
	this->form = source.form;

	return *this;
}