//FocusVisitor.cpp

#include "FocusVisitor.h"
#include "Memo.h"
#include "Line.h"
#include "CharacterFaces.h"
#include "MemoForm.h"
#include <afxWin.h>
using namespace std;

FocusVisitor::FocusVisitor(CDC *dc, CRect* rect)
	:Visitor() {
	this->dc = static_cast<CPaintDC*>(dc);
	this->rect = rect;
}

FocusVisitor::FocusVisitor(const FocusVisitor& source)
	: Visitor(source) {
	this->dc = source.dc;
	this->rect = source.rect;
}

FocusVisitor::~FocusVisitor() {

}

FocusVisitor& FocusVisitor::operator=(const FocusVisitor& source) {
	Visitor::operator=(source);
	this->dc = source.dc;
	this->rect = source.rect;

	return *this;
}

void FocusVisitor::Visit(Note *note) {
	
}

void FocusVisitor::Visit(Page *page) {
	
}

void FocusVisitor::Visit(Memo *memo) {
	CPen NewPen;
	NewPen.CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT | PS_JOIN_ROUND, 2, RGB(100, 100, 100));
	CPen *pOldPen = this->dc->SelectObject(&NewPen);
	this->dc->MoveTo(this->rect->left, this->rect->top);
	this->dc->LineTo(this->rect->left, this->rect->bottom);
	this->dc->LineTo(this->rect->right, this->rect->bottom);
	this->dc->LineTo(this->rect->right, this->rect->top);
	this->dc->LineTo(this->rect->left, this->rect->top);
	this->dc->SelectObject(pOldPen);	
}

void FocusVisitor::Visit(Line *line) {
	
}

void FocusVisitor::Visit(SingleCharacter *singleCharacter) {

}

void FocusVisitor::Visit(DoubleCharacter *doubleCharacter) {

}

void FocusVisitor::Visit(Character *character) {
	
}