#pragma once
//MouseOnMove.h

#ifndef _MOUSEONMOVE_H
#define _MOUSEONMOVE_H

#include "MouseAction.h"
using namespace std;

class Form;
class MouseOnMove : public MouseAction {
public:
	MouseOnMove(Form *form = 0);
	MouseOnMove(const MouseOnMove& source);
	~MouseOnMove();
	MouseOnMove& operator=(const MouseOnMove& source);
	virtual void OnMouseAction(UINT nFlags, CPoint point);
	virtual void OnMouseAction(int x, int y);
	virtual void OnMouseAction(UINT nSide, LPRECT lpRect);
};

#endif	//_MOUSEONMOVE_H
