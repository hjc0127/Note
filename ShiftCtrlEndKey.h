#pragma once
//ShiftCtrlEndKey.h

#ifndef _SHIFTCTRLENDKEY_H
#define _SHIFTCTRLENDKEY_H

#include "KeyAction.h"

class ShiftCtrlEndKey :public KeyAction {
public:
	ShiftCtrlEndKey(Form *form = 0);
	ShiftCtrlEndKey(const ShiftCtrlEndKey& source);
	~ShiftCtrlEndKey();
	ShiftCtrlEndKey& operator=(const ShiftCtrlEndKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_SHIFTCTRLENDKEY_H