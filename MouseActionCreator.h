#pragma once
//MouseActionCreator.h

#ifndef _MOUSEACTIONCREATOR_H
#define _MOUSEACTIONCREATOR_H

#include <afxwin.h>
#include "OtherNoteForm.h"

class Form;
class TabCtrl;
class MouseAction;
class MouseActionCreator {
public:
	MouseActionCreator();
	MouseActionCreator(const MouseActionCreator& source);
	~MouseActionCreator();
	MouseActionCreator& operator=(const MouseActionCreator& source);
	MouseAction* Create(Form *form, UINT nFlags, CPoint point, Long message);
	MouseAction* Create(Form *form, int x, int y, Long message);
	MouseAction* Create(Form *form, UINT nSide, LPRECT lpRect, Long message);
	MouseAction* Create(TabCtrl *tabCtrl, UINT nFlags, CPoint point, Long message);
};

#endif	//_MOUSEACTIONCREATOR_H