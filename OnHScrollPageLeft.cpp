// OnHScrollPageLeft.cpp

#include "OnHScrollPageLeft.h"

OnHScrollPageLeft::OnHScrollPageLeft(HorizontalScroll *horizontalScroll)
	:ScrollAction() {
	this->horizontalScroll = horizontalScroll;
}

OnHScrollPageLeft::OnHScrollPageLeft(const OnHScrollPageLeft& source)
	:ScrollAction(source) {
	this->horizontalScroll = source.horizontalScroll; 
}

OnHScrollPageLeft::~OnHScrollPageLeft() {
}

OnHScrollPageLeft&  OnHScrollPageLeft::operator=(const OnHScrollPageLeft& source) {
	ScrollAction::operator=(source);
	this->horizontalScroll = source.horizontalScroll;
	return *this;
}

void OnHScrollPageLeft::Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	this->horizontalScroll->ScrollPreviousPage();
}