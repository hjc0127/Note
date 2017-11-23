#pragma once
//PaintVisitor.h

#ifndef _PAINTVISITOR_H
#define _PAINTVISITOR_H

#include "Visitor.h"

class CDC;
class CPaintDC;
class CRect;
class PaintVisitor :public Visitor {
public:
	//PaintVisitor(CPaintDC *dc = 0, CRect *rect = 0);
	PaintVisitor(CDC *dc = 0, CRect *rect = 0);
	PaintVisitor(const PaintVisitor& source);
	virtual ~PaintVisitor();
	PaintVisitor& operator=(const PaintVisitor& source);
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

inline CPaintDC* PaintVisitor::GetDC() const {
	return const_cast<CPaintDC*>(this->dc);
}

inline CRect* PaintVisitor::GetRect() const {
	return const_cast<CRect*>(this->rect);
}

#endif	//_PAINTVISITOR_H