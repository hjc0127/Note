// UnHighLightVisitor.h

#ifndef _UNHIGHLIGHTVISITOR_H
#define _UNHIGHLIGHTVISITOR_H

#include "Visitor.h"
#include <afxwin.h>

class UnHighLightVisitor : public Visitor {
public:
	UnHighLightVisitor(CDC *dc);
	UnHighLightVisitor(const UnHighLightVisitor& source);
	virtual ~UnHighLightVisitor();
	UnHighLightVisitor& operator=(const UnHighLightVisitor& source);
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


#endif // _UNHIGHLIGHTVISITOR_H
