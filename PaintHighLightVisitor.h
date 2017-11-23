#pragma once
//PaintHighLightVisitor.h

#ifndef _PAINTHIGHLIGHTVISITOR_H
#define _PAINTHIGHLIGHTVISITOR_H

#include "Visitor.h"

typedef signed long int Long;

class CDC;
class HighLight;
class PaintHighLightVisitor :public Visitor {
public:
	PaintHighLightVisitor(CDC *dc, HighLight *selectedBuffer, Long xPosition, Long yPosition);
	PaintHighLightVisitor(const PaintHighLightVisitor& source);
	virtual ~PaintHighLightVisitor();
	PaintHighLightVisitor& operator=(const PaintHighLightVisitor& source);
	virtual void Visit(Note *note);
	virtual void Visit(Page *page);
	virtual void Visit(Memo *memo);
	virtual void Visit(Line *line);
	virtual void Visit(Character *character);
	virtual void Visit(SingleCharacter *singleCharacter);
	virtual void Visit(DoubleCharacter *doubleCharacter);

	CDC* GetDC() const;
	Long GetXPosition() const;
	Long GetYPosition() const;

private:
	CDC *dc;
	Long xPosition;
	Long yPosition;
};

inline CDC* PaintHighLightVisitor::GetDC() const {
	return const_cast<CDC*>(this->dc);
}

inline Long PaintHighLightVisitor::GetXPosition() const {
	return this->xPosition;
}

inline Long PaintHighLightVisitor::GetYPosition() const {
	return this->yPosition;
}

#endif	//_PAINTHIGHLIGHTVISITOR_H
