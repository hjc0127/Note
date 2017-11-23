// OnVScrollLineUp.cpp

#include "OnVScrollLineUp.h"

OnVScrollLineUp::OnVScrollLineUp(VerticalScroll *verticalScroll)
	:ScrollAction() {
	this->verticalScroll = verticalScroll;
}

OnVScrollLineUp::OnVScrollLineUp(const OnVScrollLineUp& source)
	:ScrollAction(source) {
	this->verticalScroll = source.verticalScroll;
}

OnVScrollLineUp::~OnVScrollLineUp() {
}

OnVScrollLineUp& OnVScrollLineUp::operator=(const OnVScrollLineUp& source) {
	ScrollAction::operator=(source);
	this->verticalScroll = source.verticalScroll;
	return *this;
}

void OnVScrollLineUp::Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	this->verticalScroll->ScrollPreviousLine();
}