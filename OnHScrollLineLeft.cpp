// OnHScrollLineLeft.cpp

#include "OnHScrollLineLeft.h"

OnHScrollLineLeft::OnHScrollLineLeft(HorizontalScroll *horizontalScroll)
	:ScrollAction() {
	this->horizontalScroll = horizontalScroll;
}

OnHScrollLineLeft::OnHScrollLineLeft(const OnHScrollLineLeft& source)
	:ScrollAction(source) {
	this->horizontalScroll = source.horizontalScroll;
}

OnHScrollLineLeft::~OnHScrollLineLeft() {
}

OnHScrollLineLeft& OnHScrollLineLeft::operator=(const OnHScrollLineLeft& source) {
	ScrollAction::operator=(source);
	this->horizontalScroll = source.horizontalScroll;
	return *this;
}

void OnHScrollLineLeft::Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	this->horizontalScroll->ScrollPreviousLine();
}

