#pragma once
//RightArrowKey.h

#ifndef _RIGHTARROWKEY_H
#define _RIGHTARROWKEY_H

#include "KeyAction.h"

class RightArrowKey :public KeyAction {
public:
	RightArrowKey(Form *form = 0);
	RightArrowKey(const RightArrowKey& source);
	~RightArrowKey();
	RightArrowKey& operator=(const RightArrowKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_RIGHTARROWKEY_H