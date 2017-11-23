// Scroll.cpp

#include "Scroll.h"
#include "OtherNoteForm.h"
#include "PageForm.h"

Scroll::Scroll(OtherNoteForm *otherNoteForm) {
	this->otherNoteForm = otherNoteForm;
	this->scrollBar = new CScrollBar;
	this->maxLineSize = 0;
	this->current = 0;
}

Scroll::Scroll(const Scroll& source) {
	this->otherNoteForm = source.otherNoteForm;
	this->scrollBar = source.scrollBar;
	this->maxLineSize = source.maxLineSize;
	this->current = source.current;
}

Scroll::~Scroll() {
	if(this->scrollBar != 0) {
		delete this->scrollBar;
	}
}

Scroll& Scroll::operator=(const Scroll& source) {
	if(this->scrollBar != 0) {
		delete this->scrollBar;
	}
	this->scrollBar = source.scrollBar;
	this->otherNoteForm = source.otherNoteForm;
	this->current = source.current;
	return *this;
}

void Scroll::SetScrollVisible() {
	this->scrollBar->EnableScrollBar(ESB_ENABLE_BOTH);
}

void Scroll::SetScrollUnVisible() {
	this->scrollBar->EnableScrollBar(ESB_DISABLE_BOTH);
}