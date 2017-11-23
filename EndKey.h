#pragma once
#pragma once
#pragma once
//EndKey.h

#ifndef _ENDKEY_H
#define _ENDKEY_H

#include "KeyAction.h"

class EndKey :public KeyAction {
public:
	EndKey(Form *form = 0);
	EndKey(const EndKey& source);
	~EndKey();
	EndKey& operator=(const EndKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_ENDKEY_H