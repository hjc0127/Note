#pragma once
//FindingFormActionCreator.h

#ifndef _FINDINGFORMACTIONCREATOR_H
#define _FINDINGFORMACTIONCREATOR_H

//#include "FindingFormAction.h"
//#include "Form.h"
#include <afxwin.h>

//class FindingForm;
class Form;
class FindingFormAction;
class FindingFormActionCreator {
public:
	FindingFormActionCreator();
	FindingFormActionCreator(const FindingFormActionCreator& source);
	~FindingFormActionCreator();
	FindingFormActionCreator& operator=(const FindingFormActionCreator& source);
	FindingFormAction* Create(Form *form, WPARAM wParam, LPARAM lParam);
	//FindingFormAction* Create(FindingForm *findingForm, WPARAM wParam, LPARAM lParam);
};

#endif	//_FINDINGFORMACTIONCREATOR_H