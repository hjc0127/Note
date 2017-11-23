//TabCtrlMouseRButtonDown.h

#ifndef _TabCtrlMouseRButtonDown_H
#define _TabCtrlMouseRButtonDown_H

#include "MouseAction.h"

using namespace std;

class TabCtrl;
class TabCtrlMouseRButtonDown : public MouseAction {
public:
	TabCtrlMouseRButtonDown(TabCtrl *form = 0);
	TabCtrlMouseRButtonDown(const TabCtrlMouseRButtonDown& source);
	~TabCtrlMouseRButtonDown();
	TabCtrlMouseRButtonDown& operator=(const TabCtrlMouseRButtonDown& source);
	virtual void OnMouseAction(UINT nFlags, CPoint point);
	virtual void OnMouseAction(int x, int y);
	virtual void OnMouseAction(UINT nSide, LPRECT lpRect);
};

#endif	//_TabCtrlMouseRButtonDown_H