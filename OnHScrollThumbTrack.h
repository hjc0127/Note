// OnHScrollThumbTrack.h

#ifndef _ONHSCROLLTHUMBTRACK_H
#define _ONHSCROLLTHUMBTRACK_H

#include "ScrollAction.h"
#include "HorizontalScroll.h"

class OnHScrollThumbTrack : public ScrollAction {
public:
	OnHScrollThumbTrack(HorizontalScroll *horizontalScroll);
	OnHScrollThumbTrack(const OnHScrollThumbTrack& source);
	virtual ~OnHScrollThumbTrack();
	OnHScrollThumbTrack& operator=(const OnHScrollThumbTrack& source);
	void Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	HorizontalScroll *horizontalScroll;
};

#endif //_ONHSCROLLTHUMBTRACK_H
