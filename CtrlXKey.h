#pragma once
//CtrlX.h

#ifndef _CTRLXKEY_H
#define _CTRLXKEY_H

#include "KeyAction.h"

class CtrlXKey :public KeyAction {
public:
	CtrlXKey(Form *form = 0);
	CtrlXKey(const CtrlXKey& source);
	~CtrlXKey();
	CtrlXKey& operator=(const CtrlXKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_CTRLXKEY_H