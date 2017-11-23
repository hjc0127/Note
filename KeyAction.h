#pragma once
//KeyAction.h

#ifndef _KEYACTION_H
#define _KEYACTION_H

#include <afxwin.h>
using namespace std;

//class OtherNoteForm;
class Form;
class KeyAction {
public:
	KeyAction(Form *form = 0);
	KeyAction(const KeyAction& source);
	virtual ~KeyAction() = 0;
	KeyAction& operator=(const KeyAction& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) = 0;
protected:
	Form *form;
};

#endif	//_KEYACTION_H