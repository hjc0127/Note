// OnVScrollPageUp.cpp

#include "OnVScrollPageUp.h"

OnVScrollPageUp::OnVScrollPageUp(VerticalScroll *verticalScroll)
	:ScrollAction() {
	this->verticalScroll = verticalScroll;
}

OnVScrollPageUp::OnVScrollPageUp(const OnVScrollPageUp& source)
	:ScrollAction() {
	this->verticalScroll = verticalScroll;
}

OnVScrollPageUp::~OnVScrollPageUp() {
}

OnVScrollPageUp& OnVScrollPageUp::operator=(const OnVScrollPageUp& source) {
	ScrollAction::operator=(source);
	this->verticalScroll = source.verticalScroll;
	return *this;
}

void OnVScrollPageUp::Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	this->verticalScroll->ScrollPreviousPage();
}