// OnVScrollPageDown.h

#ifndef _ONVSCROLLPAGEDOWN_H
#define _ONVSCROLLPAGEDOWN_H

#include "ScrollAction.h"
#include "VerticalScroll.h"


class OnVScrollPageDown : public ScrollAction {
public:
	OnVScrollPageDown(VerticalScroll *verticalScroll);
	OnVScrollPageDown(const OnVScrollPageDown& source);
	virtual ~OnVScrollPageDown();
	OnVScrollPageDown& operator=(const OnVScrollPageDown& source);
	virtual void Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	VerticalScroll *verticalScroll;
};


#endif //_ONVSCROLLPAGEDOWN_H