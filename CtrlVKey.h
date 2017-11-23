#pragma once
//CtrlVKey.h

#ifndef _CTRLVKEY_H
#define _CTRLVKEY_H

#include "KeyAction.h"

class CtrlVKey :public KeyAction {
public:
	CtrlVKey(Form *form = 0);
	CtrlVKey(const CtrlVKey& source);
	~CtrlVKey();
	CtrlVKey& operator=(const CtrlVKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_CTRLVKEY_H