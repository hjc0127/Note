#pragma once
//MouseAction.h

#ifndef _MOUSEACTION_H
#define _MOUSEACTION_H

#include <afxwin.h>
using namespace std;

class MouseAction {
public:
	MouseAction(CWnd *form = 0);
	MouseAction(const MouseAction& source);
	virtual ~MouseAction() = 0;
	MouseAction& operator=(const MouseAction& source);
	virtual void OnMouseAction(UINT nFlags, CPoint point) = 0;
	virtual void OnMouseAction(int x, int y) = 0;
	virtual void OnMouseAction(UINT nSide, LPRECT lpRect) = 0;
protected:
	CWnd *form;
};

#endif	//_MOUSEACTION_H
