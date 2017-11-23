//MouseAction.cpp

#include "MouseAction.h"

MouseAction::MouseAction(CWnd *form)
{
	this->form = form;
}

MouseAction::MouseAction(const MouseAction& source) {
	this->form = source.form;
}

MouseAction::~MouseAction() {

}

MouseAction& MouseAction::operator=(const MouseAction& source) {
	this->form = source.form;

	return *this;
}