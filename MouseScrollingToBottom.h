#pragma once
//MouseScrollingToBottom.h

#ifndef _MOUSESCROLLINGTOBOTTOM_H
#define _MOUSESCROLLINGTOBOTTOM_H

#include "MouseAction.h"
using namespace std;

class Form;
class MouseScrollingToBottom : public MouseAction {
public:
	MouseScrollingToBottom(Form *form = 0);
	MouseScrollingToBottom(const MouseScrollingToBottom& source);
	~MouseScrollingToBottom();
	MouseScrollingToBottom& operator=(const MouseScrollingToBottom& source);
	virtual void OnMouseAction(UINT nFlags, CPoint point);
	virtual void OnMouseAction(int x, int y);
	virtual void OnMouseAction(UINT nSide, LPRECT lpRect);
};

#endif	//_MOUSESCROLLINGTOBOTTOM_H