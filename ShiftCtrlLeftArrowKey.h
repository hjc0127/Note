#pragma once
//ShiftCtrlLeftArrowKey.h

#ifndef _SHIFTCTRLLEFTARROWKEY_H
#define _SHIFTCTRLLEFTARROWKEY_H

#include "KeyAction.h"

class ShiftCtrlLeftArrowKey :public KeyAction {
public:
	ShiftCtrlLeftArrowKey(Form *form = 0);
	ShiftCtrlLeftArrowKey(const ShiftCtrlLeftArrowKey& source);
	~ShiftCtrlLeftArrowKey();
	ShiftCtrlLeftArrowKey& operator=(const ShiftCtrlLeftArrowKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_SHIFTCTRLLEFTARROWKEY_H