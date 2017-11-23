#pragma once
//PaintSelectionVisitor.h

#ifndef _PAINTSELECTIONVISITOR_H
#define _PAINTSELECTIONVISITOR_H

#include "Visitor.h"

typedef signed long int Long;

class CDC;
class SelectedBuffer;
class PaintSelectionVisitor :public Visitor {
public:
	PaintSelectionVisitor(CDC *dc);
	PaintSelectionVisitor(const PaintSelectionVisitor& source);
	virtual ~PaintSelectionVisitor();
	PaintSelectionVisitor& operator=(const PaintSelectionVisitor& source);
	virtual void Visit(Note *note);
	virtual void Visit(Page *page);
	virtual void Visit(Memo *memo);
	virtual void Visit(Line *line);
	virtual void Visit(Character *character);
	virtual void Visit(SingleCharacter *singleCharacter);
	virtual void Visit(DoubleCharacter *doubleCharacter);
	virtual void Visit(MemoForm *memoForm);
	
	//CDC* GetDC() const;
//	SelectedBuffer* GetSelectedBuffer() const;
	Long GetXPosition() const;
	Long GetYPosition() const;

private:
	CDC *dc;
//	SelectedBuffer *selectedBuffer;
	Long xPosition;
	Long yPosition;
};

//inline CDC* PaintSelectionVisitor::GetDC() const {
//	return const_cast<CDC*>(this->dc);
//}

//inline SelectedBuffer* PaintSelectionVisitor::GetSelectedBuffer() const {
//	return this->selectedBuffer;
//}

inline Long PaintSelectionVisitor::GetXPosition() const {
	return this->xPosition;
}

inline Long PaintSelectionVisitor::GetYPosition() const {
	return this->yPosition;
}

#endif	//_PAINTSELECTIONVISITOR_H