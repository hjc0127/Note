#pragma once
//MouseLButtonDown.h

#ifndef _MOUSELBUTTONDOWN_H
#define _MOUSELBUTTONDOWN_H

#include "MouseAction.h"
using namespace std;

class MouseLButtonDown : public MouseAction {
public:
	MouseLButtonDown(Form *form = 0);
	MouseLButtonDown(const MouseLButtonDown& source);
	~MouseLButtonDown();
	MouseLButtonDown& operator=(const MouseLButtonDown& source);
	virtual void OnMouseAction(UINT nFlags, CPoint point);
	virtual void OnMouseAction(int x, int y);
	virtual void OnMouseAction(UINT nSide, LPRECT lpRect);
};

#endif	//_MOUSELBUTTONDOWN_H
