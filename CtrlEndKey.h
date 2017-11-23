#pragma once
//CtrlEndKey.h

#ifndef _CTRLENDKEY_H
#define _CTRLENDKEY_H

#include "KeyAction.h"

class CtrlEndKey :public KeyAction {
public:
	CtrlEndKey(Form *form = 0);
	CtrlEndKey(const CtrlEndKey& source);
	~CtrlEndKey();
	CtrlEndKey& operator=(const CtrlEndKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_CTRLENDKEY_H