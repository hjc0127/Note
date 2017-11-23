// OnHScrollLineRight.cpp

#include "OnHScrollLineRight.h"

OnHScrollLineRight::OnHScrollLineRight(HorizontalScroll *horizontalScroll)
	:ScrollAction() {
	this->horizontalScroll = horizontalScroll;
}

OnHScrollLineRight::OnHScrollLineRight(const OnHScrollLineRight& source)
	:ScrollAction(source) {
	this->horizontalScroll = source.horizontalScroll;
}

OnHScrollLineRight::~OnHScrollLineRight() {
}

OnHScrollLineRight& OnHScrollLineRight::operator=(const OnHScrollLineRight& source) {
	ScrollAction::operator=(source);
	this->horizontalScroll = source.horizontalScroll;
	return *this;
}

void OnHScrollLineRight::Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	this->horizontalScroll->ScrollNextLine();
}