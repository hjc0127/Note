// OnVScrollThumbTrack.h

#ifndef _ONVSCROLLTHUMBTRACK_H
#define _ONVSCROLLTHUMBTRACK_H

#include "ScrollAction.h"
#include "VerticalScroll.h"

class OnVScrollThumbTrack : public ScrollAction {
public:
	OnVScrollThumbTrack(VerticalScroll *verticalScroll);
	OnVScrollThumbTrack(const OnVScrollThumbTrack& source);
	virtual ~OnVScrollThumbTrack();
	OnVScrollThumbTrack& operator=(const OnVScrollThumbTrack& source);
	virtual void Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	VerticalScroll *verticalScroll;
};


#endif //_ONVSCROLLTHUMBTRACK_H