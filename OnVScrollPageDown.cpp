// OnVScrollPageDown.cpp

#include "OnVScrollPageDown.h"

OnVScrollPageDown::OnVScrollPageDown(VerticalScroll *verticalScroll)
	:ScrollAction() {
	this->verticalScroll = verticalScroll;
}

OnVScrollPageDown::OnVScrollPageDown(const OnVScrollPageDown& source)
	:ScrollAction(source) {
	this->verticalScroll = source.verticalScroll;
}

OnVScrollPageDown::~OnVScrollPageDown() {
}

OnVScrollPageDown& OnVScrollPageDown::operator=(const OnVScrollPageDown& source) {
	ScrollAction::operator=(source);
	this->verticalScroll = source.verticalScroll;
	return *this;
}

void OnVScrollPageDown::Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	this->verticalScroll->ScrollNextPage();
}