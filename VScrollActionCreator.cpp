// VScrollActionCreator.cpp

#include "VScrollActionCreator.h"
#include "OnVScrollLineDown.h"
#include "OnVScrollLineUp.h"
#include "OnVScrollPageDown.h"
#include "OnVScrollPageUp.h"
#include "OnVScrollThumbTrack.h"
#include "OnVScrollThumbPosition.h"

VScrollActionCreator::VScrollActionCreator() {
}

VScrollActionCreator::VScrollActionCreator(const VScrollActionCreator& source) {
}

VScrollActionCreator::~VScrollActionCreator() {
}

VScrollActionCreator& VScrollActionCreator::operator=(const VScrollActionCreator& source) {
	return *this;
}

ScrollAction* VScrollActionCreator::Create(VerticalScroll *verticalScroll, UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	
	ScrollAction *scrollAction = 0;
	if(nSBCode == SB_LINEDOWN) {
		scrollAction = new OnVScrollLineDown(verticalScroll);
	}
	else if(nSBCode == SB_LINEUP) {
		scrollAction = new OnVScrollLineUp(verticalScroll);
	}
	else if(nSBCode == SB_PAGEDOWN) {
		scrollAction = new OnVScrollPageDown(verticalScroll);
	}
	else if(nSBCode == SB_PAGEUP) {
		scrollAction = new OnVScrollPageUp(verticalScroll);
	}
	else if(nSBCode == SB_THUMBTRACK) {
		scrollAction = new OnVScrollThumbTrack(verticalScroll);
	}
	else if(nSBCode == SB_THUMBPOSITION) {
		scrollAction = new OnVScrollThumbPosition(verticalScroll);
	}

	return scrollAction;
}