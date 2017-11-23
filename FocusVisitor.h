#pragma once
//FocusVisitor.h

#ifndef _FOCUSVISITOR_H
#define _FOCUSVISITOR_H

#include "Visitor.h"

class CDC;
class CPaintDC;
class CRect;
class FocusVisitor :public Visitor {
public:
	FocusVisitor(CDC *dc = 0, CRect *rect = 0);
	FocusVisitor(const FocusVisitor& source);
	virtual ~FocusVisitor();
	FocusVisitor& operator=(const FocusVisitor& source);
	virtual void Visit(Note *note);
	virtual void Visit(Page *page);
	virtual void Visit(Memo *memo);
	virtual void Visit(Line *line);
	virtual void Visit(Character *character);
	virtual void Visit(SingleCharacter *singleCharacter);
	virtual void Visit(DoubleCharacter *doubleCharacter);
	CPaintDC* GetDC() const;
	CRect* GetRect() const;
private:
	CPaintDC *dc;
	CRect *rect;
};

inline CPaintDC* FocusVisitor::GetDC() const {
	return const_cast<CPaintDC*>(this->dc);
}

inline CRect* FocusVisitor::GetRect() const {
	return const_cast<CRect*>(this->rect);
}

#endif	//_FOCUSVISITOR_H