// OnHScrollLineRight.h

#ifndef _ONHSCROLLLINERIGHT_H
#define _ONHSCROLLLINERIGHT_H

#include "ScrollAction.h"
#include "HorizontalScroll.h"

class OnHScrollLineRight : public ScrollAction {
public:
	OnHScrollLineRight(HorizontalScroll *horizontalScroll);
	OnHScrollLineRight(const OnHScrollLineRight& source);
	virtual ~OnHScrollLineRight();
	OnHScrollLineRight& operator=(const OnHScrollLineRight& source);
	virtual void Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	HorizontalScroll *horizontalScroll;
};


#endif //_ONHSCROLLLINERIGHT_H