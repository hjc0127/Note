#pragma once
//MouseScrollingToRight.h

#ifndef _MOUSESCROLLINGTORIGHT_H
#define _MOUSESCROLLINGTORIGHT_H

#include "MouseAction.h"
using namespace std;

class Form;
class MouseScrollingToRight : public MouseAction {
public:
	MouseScrollingToRight(Form *form = 0);
	MouseScrollingToRight(const MouseScrollingToRight& source);
	~MouseScrollingToRight();
	MouseScrollingToRight& operator=(const MouseScrollingToRight& source);
	virtual void OnMouseAction(UINT nFlags, CPoint point);
	virtual void OnMouseAction(int x, int y);
	virtual void OnMouseAction(UINT nSide, LPRECT lpRect);
};

#endif	//_MOUSESCROLLINGTORIGHT_H