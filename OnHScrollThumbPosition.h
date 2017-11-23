// OnHScrollThumbPosition.h

#ifndef _ONHSCROLLTHUMBPOSITION_H
#define _ONHSCROLLTHUMBPOSITION_H

#include "ScrollAction.h"
#include "HorizontalScroll.h"


class OnHScrollThumbPosition : public ScrollAction {
public:
	OnHScrollThumbPosition(HorizontalScroll *horizontalScroll);
	OnHScrollThumbPosition(const OnHScrollThumbPosition& source);
	virtual ~OnHScrollThumbPosition();
	OnHScrollThumbPosition& operator=(const OnHScrollThumbPosition& source);
	void Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	HorizontalScroll *horizontalScroll;
};

#endif //_ONHSCROLLTHUMBPOSITION_H