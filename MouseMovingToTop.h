#pragma once
//MouseMovingToTop.h

#ifndef _MOUSEMOVINGTOTOP_H
#define _MOUSEMOVINGTOTOP_H

#include "MouseAction.h"
using namespace std;	

class Form;
class MouseMovingToTop : public MouseAction {
public:
	MouseMovingToTop(Form *form = 0);
	MouseMovingToTop(const MouseMovingToTop& source);
	~MouseMovingToTop();
	MouseMovingToTop& operator=(const MouseMovingToTop& source);
	virtual void OnMouseAction(UINT nFlags, CPoint point);
	virtual void OnMouseAction(int x, int y);
	virtual void OnMouseAction(UINT nSide, LPRECT lpRect);
};

#endif	//_MOUSEMOVINGTOTOP_H