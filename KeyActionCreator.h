#pragma once
//KeyActionCreator.h

#ifndef _KEYACTIONCREATOR_H
#define _KEYACTIONCREATOR_H

#include "KeyAction.h"
#include "Form.h"

class KeyActionCreator {
public:
	KeyActionCreator();
	KeyActionCreator(const KeyActionCreator& source);
	~KeyActionCreator();
	KeyActionCreator& operator=(const KeyActionCreator& source);
	KeyAction* Create(Form *form, UINT nChar, UINT nRepCnt, UINT nFlags, Long message);
	//KeyAction* Create(OtherNoteForm *otherNoteForm, UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_KEYACTIONCREATOR_H