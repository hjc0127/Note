// OnHScrollThumbTrack.cpp

#include "OnHScrollThumbTrack.h"

OnHScrollThumbTrack::OnHScrollThumbTrack(HorizontalScroll *horizontalScroll)
	:ScrollAction() {
	this->horizontalScroll = horizontalScroll;
}

OnHScrollThumbTrack::OnHScrollThumbTrack(const OnHScrollThumbTrack& source)
	:ScrollAction(source) {
	this->horizontalScroll = source.horizontalScroll;
}

OnHScrollThumbTrack::~OnHScrollThumbTrack() {
}

OnHScrollThumbTrack& OnHScrollThumbTrack::operator=(const OnHScrollThumbTrack& source) {
	ScrollAction::operator=(source);
	this->horizontalScroll = source.horizontalScroll;
	return *this;
}

void OnHScrollThumbTrack::Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	this->horizontalScroll->MoveThumb();
}