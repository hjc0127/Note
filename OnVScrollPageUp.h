// OnVScrollPageUp.h

#ifndef _ONVSCROLLPAGEUP_H
#define _ONVSCROLLPAGEUP_H

#include "ScrollAction.h"
#include "VerticalScroll.h"

class OnVScrollPageUp : public ScrollAction {
public:
	OnVScrollPageUp(VerticalScroll *verticalScroll);
	OnVScrollPageUp(const OnVScrollPageUp& source);
	virtual ~OnVScrollPageUp();
	OnVScrollPageUp& operator=(const OnVScrollPageUp& source);
	virtual void Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	VerticalScroll *verticalScroll;
};


#endif //_ONVSCROLLPAGEUP_H