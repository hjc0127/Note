#pragma once
//FindDownward.h

#ifndef _FINDDOWNWARD_H
#define _FINDDOWNWARD_H

#include "FindingFormAction.h"

class FindDownward :public FindingFormAction {
public:
	FindDownward(Form *form = 0);
	FindDownward(const FindDownward& source);
	~FindDownward();
	FindDownward& operator=(const FindDownward& source);
	virtual void OnFindingFormButtonClicked(WPARAM wParam, LPARAM lParam);
	//virtual void OnFindingFormButtonClicked();
};

#endif	//_FINDDOWNWARD_H