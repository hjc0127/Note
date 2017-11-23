// VScrollActionCreator.h

#ifndef _VSCROLLACTIONCREATOR_H
#define _VSCROLLACTIONCREATOR_H

#include "Scroll.h"
#include "ScrollAction.h"
#include "VerticalScroll.h"

class VScrollActionCreator {
public:
	VScrollActionCreator();
	VScrollActionCreator(const VScrollActionCreator& source);
	~VScrollActionCreator();
	VScrollActionCreator& operator=(const VScrollActionCreator& source);
	ScrollAction* Create(VerticalScroll* verticalScroll, UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};


#endif //_VSCROLLACTIONCREATOR_H