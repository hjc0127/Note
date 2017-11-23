#pragma once
//CtrlCKey.h

#ifndef _CTRLCKEY_H
#define _CTRLCKEY_H

#include "KeyAction.h"

class CtrlCKey :public KeyAction {
public:
	CtrlCKey(Form *form = 0);
	CtrlCKey(const CtrlCKey& source);
	~CtrlCKey();
	CtrlCKey& operator=(const CtrlCKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_CTRLCKEY_H