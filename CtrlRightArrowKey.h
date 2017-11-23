#pragma once
//CtrlRightArrowKey.h

#ifndef _CTRLRIGHTARROWKEY_H
#define _CTRLRIGHTARROWKEY_H

#include "KeyAction.h"

class CtrlRightArrowKey :public KeyAction {
public:
	CtrlRightArrowKey(Form *form = 0);
	CtrlRightArrowKey(const CtrlRightArrowKey& source);
	~CtrlRightArrowKey();
	CtrlRightArrowKey& operator=(const CtrlRightArrowKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_CTRLRIGHTARROWKEY_H