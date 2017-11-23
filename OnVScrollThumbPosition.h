// OnVScrollThumbPosition.h

#ifndef _ONVSCROLLTHUMBPOSITION_H
#define _ONVSCROLLTHUMBPOSITION_H

#include "ScrollAction.h"
#include "VerticalScroll.h"

class OnVScrollThumbPosition : public ScrollAction {
public:
	OnVScrollThumbPosition(VerticalScroll *verticalScroll);
	OnVScrollThumbPosition(const OnVScrollThumbPosition& source);
	virtual ~OnVScrollThumbPosition();
	OnVScrollThumbPosition& operator=(const OnVScrollThumbPosition& source);
	virtual void Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	VerticalScroll *verticalScroll;
};



#endif //_ONVSCROLLTHUMBPOSITION_H