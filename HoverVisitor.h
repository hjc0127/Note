#pragma once
//HoverVisitor.h

#ifndef _HOVERVISITOR_H
#define _HOVERVISITOR_H

#include "Visitor.h"

class CDC;
class CPaintDC;
class CRect;
class HoverVisitor :public Visitor {
public:
	HoverVisitor(CDC *dc = 0, CRect *rect = 0);
	HoverVisitor(const HoverVisitor& source);
	virtual ~HoverVisitor();
	HoverVisitor& operator=(const HoverVisitor& source);
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

inline CPaintDC* HoverVisitor::GetDC() const {
	return const_cast<CPaintDC*>(this->dc);
}

inline CRect* HoverVisitor::GetRect() const {
	return const_cast<CRect*>(this->rect);
}

#endif	//_HOVERVISITOR_H