#pragma once
//ShiftRightArrowKey.h

#ifndef _SHIFTRIGHTARROWKEY_H
#define _SHIFTRIGHTARROWKEY_H

#include "KeyAction.h"

class ShiftRightArrowKey :public KeyAction {
public:
	ShiftRightArrowKey(Form *form = 0);
	ShiftRightArrowKey(const ShiftRightArrowKey& source);
	~ShiftRightArrowKey();
	ShiftRightArrowKey& operator=(const ShiftRightArrowKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_SHIFTRIGHTARROWKEY_H