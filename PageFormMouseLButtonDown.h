//PageFormMouseLButtonDown.h

#ifndef _PAGEFORMMOUSELBUTTONDOWN_H
#define _PAGEFORMMOUSELBUTTONDOWN_H

#include "MouseAction.h"
using namespace std;

class PageFormMouseLButtonDown : public MouseAction {
public:
	PageFormMouseLButtonDown(Form *form = 0);
	PageFormMouseLButtonDown(const PageFormMouseLButtonDown& source);
	~PageFormMouseLButtonDown();
	PageFormMouseLButtonDown& operator=(const PageFormMouseLButtonDown& source);
	virtual void OnMouseAction(UINT nFlags, CPoint point);
	virtual void OnMouseAction(int x, int y);
	virtual void OnMouseAction(UINT nSide, LPRECT lpRect);
};

#endif	//_PAGEFORMMOUSELBUTTONDOWN_H