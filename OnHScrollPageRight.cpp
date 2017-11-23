// OnHScrollPageRight.cpp

#include "OnHScrollPageRight.h"

OnHScrollPageRight::OnHScrollPageRight(HorizontalScroll *horizontalScroll)
	:ScrollAction() {
	this->horizontalScroll = horizontalScroll;
}

OnHScrollPageRight::OnHScrollPageRight(const OnHScrollPageRight& source)
	:ScrollAction(source) {
	this->horizontalScroll = source.horizontalScroll;
}

OnHScrollPageRight::~OnHScrollPageRight() {
}

OnHScrollPageRight& OnHScrollPageRight::operator=(const OnHScrollPageRight& source) {
	ScrollAction::operator=(source);
	this->horizontalScroll = source.horizontalScroll;
	return *this;
}

void OnHScrollPageRight::Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	this->horizontalScroll->ScrollNextPage();
}