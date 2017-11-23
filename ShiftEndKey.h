#pragma once
#pragma once
//ShiftEndKey.h

#ifndef _SHIFTENDKEY_H
#define _SHIFTENDKEY_H

#include "KeyAction.h"

class ShiftEndKey :public KeyAction {
public:
	ShiftEndKey(Form *form = 0);
	ShiftEndKey(const ShiftEndKey& source);
	~ShiftEndKey();
	ShiftEndKey& operator=(const ShiftEndKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_SHIFTENDKEY_H