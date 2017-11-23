#pragma once
//CtrlLeftArrowKey.h

#ifndef _CTRLLEFTARROWKEY_H
#define _CTRLLEFTARROWKEY_H

#include "KeyAction.h"

class CtrlLeftArrowKey :public KeyAction {
public:
	CtrlLeftArrowKey(Form *form = 0);
	CtrlLeftArrowKey(const CtrlLeftArrowKey& source);
	~CtrlLeftArrowKey();
	CtrlLeftArrowKey& operator=(const CtrlLeftArrowKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_CtrlLeftArrowKey_H