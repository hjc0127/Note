//CharacterKey.h

#ifndef _CharacterKey_H
#define _CharacterKey_H

#include "KeyAction.h"

class CharacterKey :public KeyAction {
public:
	CharacterKey(Form *form = 0);
	CharacterKey(const CharacterKey& source);
	~CharacterKey();
	CharacterKey& operator=(const CharacterKey& source);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#endif	//_CharacterKey_H