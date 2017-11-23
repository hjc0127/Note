#pragma once
//FindUpward.h

#ifndef _FINDUPWARD_H
#define _FINDUPWARD_H

#include "FindingFormAction.h"

class FindUpward :public FindingFormAction {
public:
	FindUpward(Form *form = 0);
	FindUpward(const FindUpward& source);
	~FindUpward();
	FindUpward& operator=(const FindUpward& source);
	virtual void OnFindingFormButtonClicked(WPARAM wParam, LPARAM lParam);
	//virtual void OnFindingFormButtonClicked();
};

#endif	//_FINDUPWARD_H