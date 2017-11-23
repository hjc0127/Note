#pragma once
//ReturnKey.h

#ifndef _RETURNKEY_H
#define _RETURNKEY_H

#include "KeyAction.h"

class ReturnKey :public KeyAction {
public:
	ReturnKey(Form *form = 0);
	ReturnKey(const ReturnKey& source);
	~ReturnKey();
	ReturnKey& operator=(const ReturnKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_RETURNKEY_H