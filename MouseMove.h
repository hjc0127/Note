#pragma once
//MouseMove.h

#ifndef _MOUSEMOVE_H
#define _MOUSEMOVE_H

#include "MouseAction.h"
using namespace std;

class Form;
class MouseMove : public MouseAction {
public:
	MouseMove(Form *form = 0);
	MouseMove(const MouseMove& source);
	~MouseMove();
	MouseMove& operator=(const MouseMove& source);
	virtual void OnMouseAction(UINT nFlags, CPoint point);
	virtual void OnMouseAction(int x, int y);
	virtual void OnMouseAction(UINT nSide, LPRECT lpRect);
};

#endif	//_MOUSEMOVE_H