// OnVScrollLineDown.cpp

#include "OnVScrollLineDown.h"

OnVScrollLineDown::OnVScrollLineDown(VerticalScroll *verticalScroll)
	:ScrollAction() {
	this->verticalScroll = verticalScroll;
}

OnVScrollLineDown::OnVScrollLineDown(const OnVScrollLineDown& source)
	:ScrollAction() {
	this->verticalScroll = verticalScroll;
}

OnVScrollLineDown::~OnVScrollLineDown() {
}

OnVScrollLineDown& OnVScrollLineDown::operator=(const OnVScrollLineDown& source) {
	ScrollAction::operator=(source);
	this->verticalScroll = source.verticalScroll;
	return *this;
}

void OnVScrollLineDown::Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	this->verticalScroll->ScrollNextLine();
}



