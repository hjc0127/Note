//TabCtrlMouseLButtonDoubleClicked.h

#ifndef _TABCTRLMOUSELBUTTONDOUBLECLICKED_H

#define _TABCTRLMOUSELBUTTONDOUBLECLICKED_H

#include "MouseAction.h"
using namespace std;

class TabCtrl;
class TabCtrlMouseLButtonDoubleClicked : public MouseAction {
public:
	TabCtrlMouseLButtonDoubleClicked(TabCtrl *form = 0);
	TabCtrlMouseLButtonDoubleClicked(const TabCtrlMouseLButtonDoubleClicked& source);
	~TabCtrlMouseLButtonDoubleClicked();
	TabCtrlMouseLButtonDoubleClicked& operator=(const TabCtrlMouseLButtonDoubleClicked& source);
	virtual void OnMouseAction(UINT nFlags, CPoint point);
	virtual void OnMouseAction(int x, int y);
	virtual void OnMouseAction(UINT nSide, LPRECT lpRect);
};

#endif	//_TABCTRLMOUSELBUTTONDOUBLECLICKED_H