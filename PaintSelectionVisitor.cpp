//PaintSelectionVisitor.cpp

#include "PaintSelectionVisitor.h"
#include "Memo.h"
#include "Line.h"
#include "Character.h"
#include "CharacterFaces.h"
#include "Caret.h"
#include "SelectedBuffer.h"
#include "MemoForm.h"
#include <afxWin.h>
using namespace std;

PaintSelectionVisitor::PaintSelectionVisitor(CDC *dc)
	:Visitor() {
	this->dc = dc;
}

PaintSelectionVisitor::PaintSelectionVisitor(const PaintSelectionVisitor& source)
	: Visitor(source) {
	this->dc = source.dc;
//	this->selectedBuffer = source.selectedBuffer;
	this->xPosition = source.xPosition;
	this->yPosition = source.yPosition;
}

PaintSelectionVisitor::~PaintSelectionVisitor() {

}

PaintSelectionVisitor& PaintSelectionVisitor::operator=(const PaintSelectionVisitor& source) {
	Visitor::operator=(source);
	this->dc = source.dc;
//	this->selectedBuffer = source.selectedBuffer;
	this->xPosition = source.xPosition;
	this->yPosition = source.yPosition;
	
	return *this;
}

#include "MakeStringVisitor.h"
void PaintSelectionVisitor::Visit(Note *note) {

}

void PaintSelectionVisitor::Visit(Page *page) {

}


void PaintSelectionVisitor::Visit(Memo *memo) {
	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	CharacterSize characterSize = characterFaces->GetCharacterSize(127);

	Long i = 0;
	Line *line = memo->GetLine(i);
	line->Accept(this);
	i++;
	while (i < memo->GetLength()) {
		this->xPosition = 0 + MEMOFORM_MARGIN_LEFT;//15;
		this->yPosition += characterSize.GetHeight();
		Line *line = memo->GetLine(i);
		line->Accept(this);
		i++;
	}
}

#include "OtherNoteForm.h"
#include "Note.h"
#include "PageForm.h"
#include "Page.h"
void PaintSelectionVisitor::Visit(Line *line) {
	MakeStringVisitor makeStringVisitor;
	line->Accept(&makeStringVisitor);
	
	CharacterFaces *characterFaces = CharacterFaces::Instance(this->dc);	
	int nTabStop = characterFaces->GetCharacterSize(32).GetWidth() * 8;
	this->dc->TabbedTextOut(this->xPosition, this->yPosition, makeStringVisitor.GetCompleteString().c_str(), 1, &nTabStop, MEMOFORM_MARGIN_LEFT);
}

void PaintSelectionVisitor::Visit(SingleCharacter *singleCharacter) {

}

void PaintSelectionVisitor::Visit(DoubleCharacter *doubleCharacter) {

}

void PaintSelectionVisitor::Visit(Character *character) {

}

#include "FindingForm.h"
#include "FindIndex.h"
void PaintSelectionVisitor::Visit(MemoForm *memoForm) {
	//1. check selection condition 1121
	bool isSelecting = false;
	if (memoForm->GetIsFocused() == TRUE) {
		isSelecting = true;
	}
	else {
		OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
		FindingForm *findingForm = otherNoteForm->GetFindingForm();
		if (findingForm != NULL) {
			FindIndex findIndex = findingForm->GetAt(findingForm->GetCurrent());
			if (memoForm == findIndex.GetMemoIndex()) {
				isSelecting = true;
			}
		}
	}

	//2. paint selection
	if (memoForm->GetSelectedBuffer()->GetIsSelecting() == true && isSelecting == true) {
		CharacterFaces *characterFaces = CharacterFaces::Instance(this->dc);
		CFont font;
		font.CreatePointFont(characterFaces->GetFontSize(), characterFaces->GetFontFamily().c_str());
		this->dc->SelectObject(&font);
		this->dc->SetBkMode(OPAQUE);
		this->dc->SetBkColor(RGB(51, 153, 255));
		this->dc->SetTextColor(RGB(255, 255, 255));
		Memo *bufferMemo = memoForm->GetSelectedBuffer()->GetBuffer();
		Line *bufferLine = bufferMemo->GetLine(bufferMemo->GetRow());
		Long xPos = 0;
		Long yPos = 0;
		memoForm->CalculatePosition(&xPos, &yPos);
		this->xPosition = xPos + memoForm->GetMarginWidth();
		this->yPosition = yPos + memoForm->GetMarginHeight() + memoForm->GetCaptionHeight();
		bufferMemo->Accept(this);
	}
}