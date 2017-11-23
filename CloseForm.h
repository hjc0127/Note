#pragma once
//CloseForm.h

#ifndef _CLOSEFORM_H
#define _CLOSEFORM_H

#include "FindingFormAction.h"

class CloseForm :public FindingFormAction {
public:
	CloseForm(Form *form = 0);
	CloseForm(const CloseForm& source);
	~CloseForm();
	CloseForm& operator=(const CloseForm& source);
	virtual void OnFindingFormButtonClicked(WPARAM wParam, LPARAM lParam);
	//virtual void OnFindingFormButtonClicked();
};

#endif	//_CLOSEFORM_H