//HoverVisitor.cpp

#include "HoverVisitor.h"
#include "Memo.h"
#include "Line.h"
#include "CharacterFaces.h"
#include "MemoForm.h"
#include <afxWin.h>
using namespace std;

HoverVisitor::HoverVisitor(CDC *dc, CRect* rect)
	:Visitor() {
	this->dc = static_cast<CPaintDC*>(dc);
	this->rect = rect;
}

HoverVisitor::HoverVisitor(const HoverVisitor& source)
	: Visitor(source) {
	this->dc = source.dc;
	this->rect = source.rect;
}

HoverVisitor::~HoverVisitor() {

}

HoverVisitor& HoverVisitor::operator=(const HoverVisitor& source) {
	Visitor::operator=(source);
	this->dc = source.dc;
	this->rect = source.rect;

	return *this;
}

void HoverVisitor::Visit(Note *note) {
	
}

void HoverVisitor::Visit(Page *page) {
	
}

void HoverVisitor::Visit(Memo *memo) {
	CPen NewPen;
	NewPen.CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT | PS_JOIN_ROUND, 2, RGB(180, 180, 180));
	CPen *pOldPen = this->dc->SelectObject(&NewPen);
	//this->dc->BeginPath();
		this->dc->MoveTo(this->rect->left, this->rect->top);
		this->dc->LineTo(this->rect->left, this->rect->bottom);
		this->dc->LineTo(this->rect->right, this->rect->bottom);
		this->dc->LineTo(this->rect->right, this->rect->top);
		this->dc->LineTo(this->rect->left, this->rect->top);
	//this->dc->EndPath();
	this->dc->SelectObject(pOldPen);
	//this->dc->FillSolidRect(this->rect, RGB(0, 0, 0));
}

void HoverVisitor::Visit(Line *line) {
	
}

void HoverVisitor::Visit(SingleCharacter *singleCharacter) {

}

void HoverVisitor::Visit(DoubleCharacter *doubleCharacter) {

}

void HoverVisitor::Visit(Character *character) {
	
}