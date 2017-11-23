#pragma once
//ShiftDownArrowKey.h

#ifndef _SHIFTDOWNARROWKEY_H
#define _SHIFTDOWNARROWKEY_H

#include "KeyAction.h"

class ShiftDownArrowKey :public KeyAction {
public:
	ShiftDownArrowKey(Form *form = 0);
	ShiftDownArrowKey(const ShiftDownArrowKey& source);
	~ShiftDownArrowKey();
	ShiftDownArrowKey& operator=(const ShiftDownArrowKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_SHIFTDOWNARROWKEY_H