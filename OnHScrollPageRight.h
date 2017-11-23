//  OnHScrollPageRight.h

#ifndef _ONHSCROLLPAGERIGHT_H
#define _ONHSCROLLPAGERIGHT_H

#include "HorizontalScroll.h"
#include "ScrollAction.h"

class OnHScrollPageRight : public ScrollAction {
public:
	OnHScrollPageRight(HorizontalScroll *horizontalScroll);
	OnHScrollPageRight(const OnHScrollPageRight& source);
	virtual ~OnHScrollPageRight();
	OnHScrollPageRight& operator=(const OnHScrollPageRight& source);
	virtual void Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	HorizontalScroll *horizontalScroll;
};


#endif //_ONHSCROLLPAGERIGHT_H