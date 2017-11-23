#pragma once
//OtherNoteFormMouseLButtonDblClk.h

#ifndef _OTHERNOTEFORMMOUSELBUTTONDBLCLK
#define _OTHERNOTEFORMMOUSELBUTTONDBLCLK

#include "MouseAction.h"
using namespace std;
class Form;
class OtherNoteFormMouseLButtonDblClk : public MouseAction {
public:
	OtherNoteFormMouseLButtonDblClk(Form *form = 0);
	OtherNoteFormMouseLButtonDblClk(const OtherNoteFormMouseLButtonDblClk& source);
	~OtherNoteFormMouseLButtonDblClk();
	OtherNoteFormMouseLButtonDblClk& operator=(const OtherNoteFormMouseLButtonDblClk& source);
	virtual void OnMouseAction(UINT nFlags, CPoint point);
	virtual void OnMouseAction(int x, int y);
	virtual void OnMouseAction(UINT nSide, LPRECT lpRect);
};

#endif	//_OTHERNOTEFORMMOUSELBUTTONDBLCLK
