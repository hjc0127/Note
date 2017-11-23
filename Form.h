#pragma once

//Form.h

#ifndef _FORM_H
#define _FORM_H

//#include <afxwin.h>
typedef signed long int Long;

class Contents;
class Visitor;
class Form {
public:
	Form(Contents *contents = 0);
	virtual ~Form() = 0;
	Form(const Form& source);
	Form& operator = (const Form& source);

	virtual Form* Clone() const = 0;
	virtual Long Add(Form *form) { return -1; };
	virtual Long Remove(Long index) { return -1; };
	virtual Form* GetAt(Long index) { return 0; }
	virtual void Accept(Visitor *visitor) {};

	Contents* GetContents() const;
	void SetContents(Contents *contents);
	//Form* GetParentForm() const;
protected:
	Contents *contents;
	//Form *parentForm;
};

inline Contents* Form::GetContents() const {
	return const_cast<Contents*>(this->contents);
}


#endif //_FORM_H