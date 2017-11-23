#pragma once
//UpArrowKey.h

#ifndef _UPARROWKEY_H
#define _UPARROWKEY_H

#include "KeyAction.h"

class UpArrowKey :public KeyAction {
public:
	UpArrowKey(Form *form = 0);
	UpArrowKey(const UpArrowKey& source);
	~UpArrowKey();
	UpArrowKey& operator=(const UpArrowKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_UPARROWKEY_H