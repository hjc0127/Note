#pragma once
//DownArrowKey.h

#ifndef _DOWNARROWKEY_H
#define _DOWNARROWKEY_H

#include "KeyAction.h"

class DownArrowKey :public KeyAction {
public:
	DownArrowKey(Form *form = 0);
	DownArrowKey(const DownArrowKey& source);
	~DownArrowKey();
	DownArrowKey& operator=(const DownArrowKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_DOWNARROWKEY_H