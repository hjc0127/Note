// OnVScrollLineDown.h

#ifndef _ONVSCROLLLINEDOWN_H
#define _ONVSCROLLLINEDOWN_H

#include "ScrollAction.h"
#include "VerticalScroll.h"

class OnVScrollLineDown : public ScrollAction {
public:
	OnVScrollLineDown(VerticalScroll *verticalScroll);
	OnVScrollLineDown(const OnVScrollLineDown& source);
	virtual ~OnVScrollLineDown();
	OnVScrollLineDown& operator=(const OnVScrollLineDown& source);
	void Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	VerticalScroll *verticalScroll;
};

#endif //_ONVSCROLLLINEDOWN_H