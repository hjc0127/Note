#pragma once
//MouseMovingToBottom.h

#ifndef _MOUSEMOVINGTOBOTTOM_H
#define _MOUSEMOVINGTOBOTTOM_H

#include "MouseAction.h"
using namespace std;

class Form;
class MouseMovingToBottom : public MouseAction {
public:
	MouseMovingToBottom(Form *form = 0);
	MouseMovingToBottom(const MouseMovingToBottom& source);
	~MouseMovingToBottom();
	MouseMovingToBottom& operator=(const MouseMovingToBottom& source);
	virtual void OnMouseAction(UINT nFlags, CPoint point);
	virtual void OnMouseAction(int x, int y);
	virtual void OnMouseAction(UINT nSide, LPRECT lpRect);
};

#endif	//_MOUSEMOVINGTOBOTTOM_H