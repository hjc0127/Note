#pragma once
//TabKey.h

#ifndef _TABKEY_H
#define _TABKEY_H

#include "KeyAction.h"

class TabKey :public KeyAction {
public:
	TabKey(Form *form = 0);
	TabKey(const TabKey& source);
	~TabKey();
	TabKey& operator=(const TabKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_TABKEY_H