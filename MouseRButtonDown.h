#pragma once
//MouseRButtonDown.h

#ifndef _MOUSERBUTTONDOWN_H
#define _MOUSERBUTTONDOWN_H

#include "MouseAction.h"
using namespace std;

class Form;
class MouseRButtonDown : public MouseAction {
public:
	MouseRButtonDown(Form *form = 0);
	MouseRButtonDown(const MouseRButtonDown& source);
	~MouseRButtonDown();
	MouseRButtonDown& operator=(const MouseRButtonDown& source);
	virtual void OnMouseAction(UINT nFlags, CPoint point);
	virtual void OnMouseAction(int x, int y);
	virtual void OnMouseAction(UINT nSide, LPRECT lpRect);
};

#endif	//_MOUSERBUTTONDOWN_H