#pragma once
//FindOnNewStr.h

#ifndef _FINDONNEWSTR_H
#define _FINDONNEWSTR_H
//#define ARGB(a,r,g,b)	((COLORREF)(((BYTE)(b) | ((WORD)((BYTE)(g))<<8)) | (((DWORD)(BYTE)(r))<<16) | (((DWORD)(BYTE)(a))<<24)))

#include "FindingFormAction.h"

class FindOnNewStr :public FindingFormAction {
public:
	FindOnNewStr(Form *form = 0);
	FindOnNewStr(const FindOnNewStr& source);
	virtual ~FindOnNewStr();
	FindOnNewStr& operator=(const FindOnNewStr& source);
	virtual void OnFindingFormButtonClicked(WPARAM wParam, LPARAM lParam);
	//virtual void OnFindingFormButtonClicked();
};

#endif	//_FINDONNEWSTR_H