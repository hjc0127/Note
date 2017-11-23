#pragma once
//ShiftCtrlRightArrowKey.h

#ifndef _SHIFTCTRLRIGHTARROWKEY_H
#define _SHIFTCTRLRIGHTARROWKEY_H

#include "KeyAction.h"

class ShiftCtrlRightArrowKey :public KeyAction {
public:
	ShiftCtrlRightArrowKey(Form *form = 0);
	ShiftCtrlRightArrowKey(const ShiftCtrlRightArrowKey& source);
	~ShiftCtrlRightArrowKey();
	ShiftCtrlRightArrowKey& operator=(const ShiftCtrlRightArrowKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_SHIFTCTRLRIGHTARROWKEY_H