#pragma once
//ShiftCtrlHomeKey.h

#ifndef _SHIFTCTRLHOMEKEY_H
#define _SHIFTCTRLHOMEKEY_H

#include "KeyAction.h"

class ShiftCtrlHomeKey :public KeyAction {
public:
	ShiftCtrlHomeKey(Form *form = 0);
	ShiftCtrlHomeKey(const ShiftCtrlHomeKey& source);
	~ShiftCtrlHomeKey();
	ShiftCtrlHomeKey& operator=(const ShiftCtrlHomeKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_SHIFTCTRLHOMEKEY_H