//TabCtrlMouseLButtonDown.h

#ifndef _TABCTRLMOUSELBUTTONDOWN_H
#define _TABCTRLMOUSELBUTTONDOWN_H

#include "MouseAction.h"
using namespace std;

class TabCtrl;
class TabCtrlMouseLButtonDown : public MouseAction {
public:
	TabCtrlMouseLButtonDown(TabCtrl *form = 0);
	TabCtrlMouseLButtonDown(const TabCtrlMouseLButtonDown& source);
	~TabCtrlMouseLButtonDown();
	TabCtrlMouseLButtonDown& operator=(const TabCtrlMouseLButtonDown& source);
	virtual void OnMouseAction(UINT nFlags, CPoint point);
	virtual void OnMouseAction(int x, int y);
	virtual void OnMouseAction(UINT nSide, LPRECT lpRect);
};

#endif	//_TABCTRLMOUSELBUTTONDOWN_H
