#pragma once
//DeleteKey.h

#ifndef _DELETEKEY_H
#define _DELETEKEY_H

#include "KeyAction.h"

class DeleteKey : public KeyAction {
public:
	DeleteKey(Form *form = 0);
	DeleteKey(const DeleteKey& source);
	~DeleteKey();
	DeleteKey& operator=(const DeleteKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif //_DELETEKEY_H