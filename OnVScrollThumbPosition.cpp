// OnVScrollThumbPosition.cpp

#include "OnVScrollThumbPosition.h"

OnVScrollThumbPosition::OnVScrollThumbPosition(VerticalScroll *verticalScroll)
	:ScrollAction() {
	this->verticalScroll = verticalScroll;
}

OnVScrollThumbPosition::OnVScrollThumbPosition(const OnVScrollThumbPosition& source)
	:ScrollAction(source) {
	this->verticalScroll = source.verticalScroll;
}

OnVScrollThumbPosition::~OnVScrollThumbPosition() {
}

OnVScrollThumbPosition& OnVScrollThumbPosition::operator=(const OnVScrollThumbPosition& source) {
	ScrollAction::operator=(source);
	this->verticalScroll = source.verticalScroll;
	return *this;
}


void OnVScrollThumbPosition::Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	this->verticalScroll->MoveThumb();
}