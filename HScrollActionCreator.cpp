// HScrollActionCreator.cpp

#include "HScrollActionCreator.h"
#include "OnHScrollLineRight.h"
#include "OnHScrollLineLeft.h"
#include "OnHScrollPageRight.h"
#include "OnHScrollPageLeft.h"
#include "OnHScrollThumbTrack.h"
#include "OnHScrollThumbPosition.h"


HScrollActionCreator::HScrollActionCreator() {
}

HScrollActionCreator::HScrollActionCreator(const HScrollActionCreator& source) {
}

HScrollActionCreator::~HScrollActionCreator() {
}

HScrollActionCreator& HScrollActionCreator::operator=(const HScrollActionCreator& source) {
	return *this;
}

ScrollAction* HScrollActionCreator::Create(HorizontalScroll *horizontalScroll, UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	
	ScrollAction *scrollAction = 0;
	if(nSBCode == SB_LINERIGHT) {
		scrollAction = new OnHScrollLineRight(horizontalScroll);
	}
	else if(nSBCode == SB_LINELEFT) {
		scrollAction = new OnHScrollLineLeft(horizontalScroll);
	}
	if(nSBCode == SB_PAGERIGHT) {
		scrollAction = new OnHScrollPageRight(horizontalScroll);
	}
	else if(nSBCode == SB_PAGELEFT) {
		scrollAction = new OnHScrollPageLeft(horizontalScroll);
	}
	else if(nSBCode == SB_THUMBTRACK) {
		scrollAction = new OnHScrollThumbTrack(horizontalScroll);
	}
	else if(nSBCode == SB_THUMBPOSITION) {
		scrollAction = new OnHScrollThumbPosition(horizontalScroll);
	}

	return scrollAction;
}
