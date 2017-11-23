// OnHScrollLineLeft.h

#ifndef _ONHSCROLLLINELEFT_H
#define _ONHSCROLLLINELEFT_H

#include "ScrollAction.h"
#include "HorizontalScroll.h"

class OnHScrollLineLeft : public ScrollAction {
public:
	OnHScrollLineLeft(HorizontalScroll *horizontalScroll);
	OnHScrollLineLeft(const OnHScrollLineLeft& source);
	virtual ~OnHScrollLineLeft();
	OnHScrollLineLeft& operator=(const OnHScrollLineLeft& source);
	virtual void Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	HorizontalScroll *horizontalScroll;
};


#endif //_ONHSCROLLLINELEFT_H