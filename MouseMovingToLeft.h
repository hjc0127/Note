#pragma once
//MouseMovingToLeft.h

#ifndef _MOUSEMOVINGTOLEFT_H
#define _MOUSEMOVINGTOLEFT_H

#include "MouseAction.h"
using namespace std;

class Form;
class MouseMovingToLeft : public MouseAction {
public:
	MouseMovingToLeft(Form *form = 0);
	MouseMovingToLeft(const MouseMovingToLeft& source);
	~MouseMovingToLeft();
	MouseMovingToLeft& operator=(const MouseMovingToLeft& source);
	virtual void OnMouseAction(UINT nFlags, CPoint point);
	virtual void OnMouseAction(int x, int y);
	virtual void OnMouseAction(UINT nSide, LPRECT lpRect);
};

#endif	//_MOUSEMOVINGTOLEFT_H