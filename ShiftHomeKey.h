#pragma once
//ShiftHomeKey.h

#ifndef _SHIFTHOMEKEY_H
#define _SHIFTHOMEKEY_H

#include "KeyAction.h"

class ShiftHomeKey :public KeyAction {
public:
	ShiftHomeKey(Form *form = 0);
	ShiftHomeKey(const ShiftHomeKey& source);
	~ShiftHomeKey();
	ShiftHomeKey& operator=(const ShiftHomeKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_SHIFTHOMEKEY_H