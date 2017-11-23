// OnVScrollThumbTrack.cpp

#include "OnVScrollThumbTrack.h"

OnVScrollThumbTrack::OnVScrollThumbTrack(VerticalScroll *verticalScroll)
	:ScrollAction() {
	this->verticalScroll = verticalScroll;
}

OnVScrollThumbTrack::OnVScrollThumbTrack(const OnVScrollThumbTrack& source)
	:ScrollAction(source) {
	this->verticalScroll = verticalScroll;
}

OnVScrollThumbTrack::~OnVScrollThumbTrack() {
}

OnVScrollThumbTrack& OnVScrollThumbTrack::operator=(const OnVScrollThumbTrack& source) {
	ScrollAction::operator=(source);
	this->verticalScroll = source.verticalScroll;
	return *this;
}

void OnVScrollThumbTrack::Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	this->verticalScroll->MoveThumb();
}
