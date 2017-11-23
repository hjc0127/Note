#pragma once
//MouseScrollingToTop.h

#ifndef _MOUSESCROLLINGTOTOP_H
#define _MOUSESCROLLINGTOTOP_H

#include "MouseAction.h"
using namespace std;

class Form;
class MouseScrollingToTop : public MouseAction {
public:
	MouseScrollingToTop(Form *form = 0);
	MouseScrollingToTop(const MouseScrollingToTop& source);
	~MouseScrollingToTop();
	MouseScrollingToTop& operator=(const MouseScrollingToTop& source);
	virtual void OnMouseAction(UINT nFlags, CPoint point);
	virtual void OnMouseAction(int x, int y);
	virtual void OnMouseAction(UINT nSide, LPRECT lpRect);
};

#endif	//_MOUSESCROLLINGTOTOP_H