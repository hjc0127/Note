// PaintFindIndexVisitor.h

#ifndef _PAINTFINDINDEXVISITOR_H
#define _PAINTFINDINDEXVISITOR_H
#include "Visitor.h"
#include <afxwin.h>

class PaintFindIndexVisitor : public Visitor {
public:
	PaintFindIndexVisitor(CDC *dc);
	PaintFindIndexVisitor(const PaintFindIndexVisitor& source);
	virtual ~PaintFindIndexVisitor();
	PaintFindIndexVisitor& operator=(const PaintFindIndexVisitor& source);
	virtual void Visit(Note *note);
	virtual void Visit(Page *page);
	virtual void Visit(Memo *memo);
	virtual void Visit(Line *line);
	virtual void Visit(Character *character);
	virtual void Visit(SingleCharacter *singleCharacter);
	virtual void Visit(DoubleCharacter *doubleCharacter);
	virtual void Visit(OtherNoteForm *otherNoteForm);
private:
	CDC *dc;
};


#endif // _PAINTFINDINDEXVISITOR_H

