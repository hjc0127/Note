#pragma once
//MouseScrollingToLeft.h

#ifndef _MOUSESCROLLINGTOLEFT_H
#define _MOUSESCROLLINGTOLEFT_H

#include "MouseAction.h"
using namespace std;

class Form;
class MouseScrollingToLeft : public MouseAction {
public:
	MouseScrollingToLeft(Form *form = 0);
	MouseScrollingToLeft(const MouseScrollingToLeft& source);
	~MouseScrollingToLeft();
	MouseScrollingToLeft& operator=(const MouseScrollingToLeft& source);
	virtual void OnMouseAction(UINT nFlags, CPoint point);
	virtual void OnMouseAction(int x, int y);
	virtual void OnMouseAction(UINT nSide, LPRECT lpRect);
};

#endif	//_MOUSESCROLLINGTOLEFT_H