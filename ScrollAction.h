// ScrollAction.h

#ifndef _SCROLLACTION_H
#define _SCROLLACTION_H

#include <afxwin.h>

class ScrollAction {
public:
	ScrollAction();
	ScrollAction(const ScrollAction& source);
	virtual ~ScrollAction() = 0;
	ScrollAction& operator=(const ScrollAction& source);
	virtual void Action(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) = 0;
};


#endif //_SCROLLACTION_H