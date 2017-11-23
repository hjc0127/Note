// OnVScrollLineUp.h

#ifndef _ONVSCROLLLINEUP_H
#define _ONVSCROLLLINEUP_H

#include "ScrollAction.h"
#include "VerticalScroll.h"

class OnVScrollLineUp : public ScrollAction {
public:
	OnVScrollLineUp(VerticalScroll *verticalScroll);
	OnVScrollLineUp(const OnVScrollLineUp& source);
	virtual ~OnVScrollLineUp();
	OnVScrollLineUp& operator=(const OnVScrollLineUp& source);
	void Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	VerticalScroll *verticalScroll;
};

#endif //_ONVSCROLLLINEUP_H