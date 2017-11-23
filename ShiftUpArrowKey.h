#pragma once
//ShiftUpArrowKey.h

#ifndef _SHIFTUPARROWKEY_H
#define _SHIFTUPARROWKEY_H

#include "KeyAction.h"

class ShiftUpArrowKey :public KeyAction {
public:
	ShiftUpArrowKey(Form *form = 0);
	ShiftUpArrowKey(const ShiftUpArrowKey& source);
	~ShiftUpArrowKey();
	ShiftUpArrowKey& operator=(const ShiftUpArrowKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_SHIFTUPARROWKEY_H