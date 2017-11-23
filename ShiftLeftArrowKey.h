#pragma once
//ShiftLeftArrowKey.h

#ifndef _SHIFTLEFTARROWKEY_H
#define _SHIFTLEFTARROWKEY_H

#include "KeyAction.h"

class ShiftLeftArrowKey :public KeyAction {
public:
	ShiftLeftArrowKey(Form *form = 0);
	ShiftLeftArrowKey(const ShiftLeftArrowKey& source);
	~ShiftLeftArrowKey();
	ShiftLeftArrowKey& operator=(const ShiftLeftArrowKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_SHIFTLEFTARROWKEY_H