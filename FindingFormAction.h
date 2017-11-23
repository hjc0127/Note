#pragma once
//FindingFormAction.h

#ifndef _FINDINGFORMACTION_H
#define _FINDINGFORMACTION_H

#include <afxwin.h>
using namespace std;

//class OtherNoteForm;
class Form;
class FindingFormAction {
public:
	FindingFormAction(Form *form = 0);
	FindingFormAction(const FindingFormAction& source);
	virtual ~FindingFormAction() = 0;
	FindingFormAction& operator=(const FindingFormAction& source);
	virtual void OnFindingFormButtonClicked(WPARAM wParam, LPARAM lParam) = 0;
	//virtual void OnFindingFormButtonClicked() = 0;
protected:
	Form *form;
};

#endif	//_FINDINGFORMACTION_H