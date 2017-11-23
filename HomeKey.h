#pragma once
#pragma once
//HomeKey.h

#ifndef _HOMEKEY_H
#define _HOMEKEY_H

#include "KeyAction.h"

class HomeKey :public KeyAction {
public:
	HomeKey(Form *form = 0);
	HomeKey(const HomeKey& source);
	~HomeKey();
	HomeKey& operator=(const HomeKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_HOMEKEY_H