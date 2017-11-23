#pragma once
//MouseMovingToRight.h

#ifndef _MOUSEMOVINGTORIGHT_H
#define _MOUSEMOVINGTORIGHT_H

#include "MouseAction.h"
using namespace std;

class Form;
class MouseMovingToRight : public MouseAction {
public:
	MouseMovingToRight(Form *form = 0);
	MouseMovingToRight(const MouseMovingToRight& source);
	~MouseMovingToRight();
	MouseMovingToRight& operator=(const MouseMovingToRight& source);
	virtual void OnMouseAction(UINT nFlags, CPoint point);
	virtual void OnMouseAction(int x, int y);
	virtual void OnMouseAction(UINT nSide, LPRECT lpRect);
};

#endif	//_MOUSEMOVINGTORIGHT_H