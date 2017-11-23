// OnHScrollPageLeft.h

#ifndef _ONHSCROLLPAGELEFT_H
#define _ONHSCROLLPAGELEFT_H

#include "HorizontalScroll.h"
#include "ScrollAction.h"

class OnHScrollPageLeft : public ScrollAction {
public:
	OnHScrollPageLeft(HorizontalScroll *horizontalScroll);
	OnHScrollPageLeft(const OnHScrollPageLeft& source);
	virtual ~OnHScrollPageLeft();
	OnHScrollPageLeft& operator=(const OnHScrollPageLeft& source);
	virtual void Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	HorizontalScroll *horizontalScroll;
};


#endif //_ONHSCROLLPAGELEFT_H