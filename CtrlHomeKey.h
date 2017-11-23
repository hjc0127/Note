#pragma once
//CtrlHomeKey.h

#ifndef _CTRLHOMEKEY_H
#define _CTRLHOMEKEY_H

#include "KeyAction.h"

class CtrlHomeKey :public KeyAction {
public:
	CtrlHomeKey(Form *form = 0);
	CtrlHomeKey(const CtrlHomeKey& source);
	~CtrlHomeKey();
	CtrlHomeKey& operator=(const CtrlHomeKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_CTRLHOMEKEY_H