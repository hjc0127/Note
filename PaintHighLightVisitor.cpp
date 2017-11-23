//PaintHighLightVisitor.cpp

#include "PaintHighLightVisitor.h"
#include "Memo.h"
#include "Line.h"
#include "Character.h"
#include "CharacterFaces.h"
#include "Caret.h"
#include "HighLight.h"
#include <afxWin.h>
using namespace std;

PaintHighLightVisitor::PaintHighLightVisitor(CDC *dc, HighLight *highLight, Long xPosition, Long yPosition)
	:Visitor() {
	this->dc = dc;
	this->xPosition = xPosition;
	this->yPosition = yPosition;
}

PaintHighLightVisitor::PaintHighLightVisitor(const PaintHighLightVisitor& source)
	: Visitor(source) {
	this->dc = source.dc;
	this->xPosition = source.xPosition;
	this->yPosition = source.yPosition;
}

PaintHighLightVisitor::~PaintHighLightVisitor() {

}

PaintHighLightVisitor& PaintHighLightVisitor::operator=(const PaintHighLightVisitor& source) {
	Visitor::operator=(source);
	this->dc = source.dc;
	this->xPosition = source.xPosition;
	this->yPosition = source.yPosition;

	return *this;
}

#include "MakeStringVisitor.h"
void PaintHighLightVisitor::Visit(Note *note) {

}

void PaintHighLightVisitor::Visit(Page *page) {

}


void PaintHighLightVisitor::Visit(Memo *memo) {
	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	CharacterSize characterSize = characterFaces->GetCharacterSize(127);

	Long i = 0;
	Line *line = memo->GetLine(i);
	line->Accept(this);
	i++;
	while (i < memo->GetLength()) {
		this->xPosition = 0;
		this->yPosition += characterSize.GetHeight();
		Line *line = memo->GetLine(i);
		line->Accept(this);
		i++;
	}
}

void PaintHighLightVisitor::Visit(Line *line) {
	MakeStringVisitor makeStringVisitor;
	line->Accept(&makeStringVisitor);

	this->dc->TabbedTextOut(this->xPosition, this->yPosition, makeStringVisitor.GetCompleteString().c_str(), 8, 0, 0);
}

void PaintHighLightVisitor::Visit(SingleCharacter *singleCharacter) {

}

void PaintHighLightVisitor::Visit(DoubleCharacter *doubleCharacter) {

}

void PaintHighLightVisitor::Visit(Character *character) {

}