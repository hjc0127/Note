// HighLightVisitor.h

#ifndef _HIGHLIGHTVISITOR_H
#define _HIGHLIGHTVISITOR_H

#include "Visitor.h"
#include <afxwin.h>

class HighLightVisitor : public Visitor {
public:
	//HighLightVisitor(CDC *dc);
	HighLightVisitor(CDC *dc = 0, CRect *rect = 0);
	HighLightVisitor(const HighLightVisitor& source);
	virtual ~HighLightVisitor();
	HighLightVisitor& operator=(const HighLightVisitor& source);
	virtual void Visit(Note *note);
	virtual void Visit(Page *page);
	virtual void Visit(Memo *memo);
	virtual void Visit(Line *line);
	virtual void Visit(Character *character);
	virtual void Visit(SingleCharacter *singleCharacter);
	virtual void Visit(DoubleCharacter *doubleCharacter);
	CRect* GetRect() const;
private:
	CDC *dc;
	CRect *rect;
};

inline CRect* HighLightVisitor::GetRect() const {
	return const_cast<CRect*>(this->rect);
}

#endif // _HIGHLIGHTVISITOR_H
