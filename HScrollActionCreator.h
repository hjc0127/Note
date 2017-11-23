//HScrollActionCreator.h

#ifndef _HSCROLLACTIONCREATOR_H
#define _HSCROLLACTIONCREATOR_H

#include "Scroll.h"
#include "ScrollAction.h"
#include "HorizontalScroll.h"

class HScrollActionCreator {
public:
	HScrollActionCreator();
	HScrollActionCreator(const HScrollActionCreator& source);
	~HScrollActionCreator();
	HScrollActionCreator& operator=(const HScrollActionCreator& source);
	ScrollAction* Create(HorizontalScroll* horizontalScroll, UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};


#endif //_HSCROLLACTIONCREATOR_H