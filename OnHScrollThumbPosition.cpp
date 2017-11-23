// OnHscrollThumbPosition.cpp

#include "OnHScrollThumbPosition.h"

OnHScrollThumbPosition::OnHScrollThumbPosition(HorizontalScroll *horizontalScroll)
	:ScrollAction() {
	this->horizontalScroll = horizontalScroll;
}

OnHScrollThumbPosition::OnHScrollThumbPosition(const OnHScrollThumbPosition& source)
	:ScrollAction(source) {
	this->horizontalScroll = source.horizontalScroll;
}

OnHScrollThumbPosition::~OnHScrollThumbPosition() {
}

OnHScrollThumbPosition& OnHScrollThumbPosition::operator=(const OnHScrollThumbPosition& source) {
	ScrollAction::operator=(source);
	this->horizontalScroll = source.horizontalScroll;
	return *this;
}

void OnHScrollThumbPosition::Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	this->horizontalScroll->MoveThumb();
}