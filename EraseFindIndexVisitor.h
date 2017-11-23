// EraseFindIndexVisitor.h

#ifndef _ERASEFINDINDEXVISITOR_H
#define _ERASEFINDINDEXVISITOR_H
#include "Visitor.h"
#include <afxwin.h>

class EraseFindIndexVisitor : public Visitor {
public:
	EraseFindIndexVisitor(CDC *dc);
	EraseFindIndexVisitor(const EraseFindIndexVisitor& source);
	virtual ~EraseFindIndexVisitor();
	EraseFindIndexVisitor& operator=(const EraseFindIndexVisitor& source);
	virtual void Visit(Note *note);
	virtual void Visit(Page *page);
	virtual void Visit(Memo *memo);
	virtual void Visit(Line *line);
	virtual void Visit(Character *character);
	virtual void Visit(SingleCharacter *singleCharacter);
	virtual void Visit(DoubleCharacter *doubleCharacter);
private:
	CDC *dc;
};


#endif // _ERASEFINDINDEXVISITOR_H
