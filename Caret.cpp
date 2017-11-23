//Caret.cpp

#include "Caret.h"
#include "MemoForm.h"
#include "SingleCharacter.h"
#include "DoubleCharacter.h"
#include "Contents.h"
#include "Line.h"
#include "Memo.h"
#include "CharacterFaces.h"
#include "CharacterSize.h"

#define CARETWIDTH 2;

Caret::Caret(MemoForm *memoForm) {
	this->memoForm = memoForm;

	CharacterFaces *characterFaces = CharacterFaces::Instance(this->memoForm->GetDC());
	CharacterSize characterSize = characterFaces->GetCharacterSize(97);

	this->width = CARETWIDTH;
	this->height = characterSize.GetHeight();
}

Caret::~Caret() {

}

Caret::Caret(const Caret& source) {
	//
}

Caret& Caret::operator=(const Caret& source) {
	return *this;
}

//void Caret::UpdateCaret() {
//	//1. set margin width, height
//	Long xPosition = this->GetMemoForm()->GetMarginWidth();
//	Long yPosition = this->GetMemoForm()->GetMarginHeight() + this->GetMemoForm()->GetCaptionHeight();
//
//	//2. Get infomation
//	Memo *memo = static_cast<Memo*>(this->memoForm->GetContents());
//	Long row = memo->GetRow();
//	Line *line = memo->GetLine(row);
//	Long column = line->GetColumn();
//
//	//3. Get yPosition
//	Long i = 0;
//	while (i < row) {
//		yPosition += this->height;
//		i++;
//	}
//
//	//4. Get xPosition
//	i = 0;
//	while (i < column) {		
//		xPosition += line->GetCharacter(i)->GetWidth();
//		i++;
//	}
//	
//	//5. Set caret
//	CWnd::SetCaretPos(CPoint(xPosition, yPosition));
//}

bool Caret::ChangeImeCaret() {
	DestroyCaret();
	CharacterFaces *characterFaces = CharacterFaces::Instance(this->memoForm->GetDC());
	this->width = characterFaces->GetCharacterSize(127).GetWidth();
	this->height = characterFaces->GetCharacterSize(127).GetHeight();

	memoForm->CWnd::CreateSolidCaret(this->width, this->height);

	memoForm->CWnd::ShowCaret();

	return true;
}

bool Caret::ChangeCaret() {
	DestroyCaret();

	Memo *memo = static_cast<Memo*>(this->memoForm->GetContents());
	Line *line = memo->GetLine(memo->GetRow());
	Character *character = line->GetCharacter(line->GetColumn() - 1);

	width = CARETWIDTH;

	//1010 에러발생
	//height = character->GetHeight();
	CharacterFaces *characterFaces = CharacterFaces::Instance(this->memoForm->GetDC());
	this->height = characterFaces->GetCharacterSize(127).GetHeight();

	memoForm->CWnd::CreateSolidCaret(width, height);

	memoForm->CWnd::ShowCaret();

	return true;
}

void Caret::ShowCaret() {
	this->memoForm->CWnd::CreateSolidCaret(this->width, this->height);

	//1. set margin width, height
	Long xPosition = this->GetMemoForm()->GetMarginWidth();
	Long yPosition = this->GetMemoForm()->GetMarginHeight() + this->GetMemoForm()->GetCaptionHeight();

	//2. Get infomation
	Memo *memo = static_cast<Memo*>(this->memoForm->GetContents());
	Long row = memo->GetRow();
	Line *line = memo->GetLine(row);
	Long column = line->GetColumn();

	//3. Get yPosition
	Long i = 0;
	while (i < row) {
		yPosition += this->height;
		i++;
	}

	//4. Get xPosition
	i = 0;
	while (i < column) {
		xPosition += line->GetCharacter(i)->GetWidth();
		i++;
	}

	//5. set caret
	this->memoForm->CWnd::SetCaretPos(CPoint(xPosition, yPosition));
	
	//6. show caret
	this->memoForm->CWnd::ShowCaret();
}

void Caret::HideCaret() {
	this->memoForm->CWnd::HideCaret();
	//DestroyCaret();
}

void Caret::Move(Long xPos, Long yPos) {
	this->memoForm->CWnd::SetCaretPos(CPoint(xPos, yPos));
}

Long Caret::GetXPosition() {
	Long xPosition = this->GetMemoForm()->GetMarginWidth();
	Long yPosition = this->GetMemoForm()->GetMarginHeight() + this->GetMemoForm()->GetCaptionHeight();

	Memo *memo = static_cast<Memo*>(this->memoForm->GetContents());
	Long row = memo->GetRow();
	Line *line = memo->GetLine(row);
	Long column = line->GetColumn();

	Long i = 0;
	while (i < row) {
		yPosition += this->height;
		i++;
	}

	i = 0;
	while (i < column) {
		xPosition += line->GetCharacter(i)->GetWidth();
		i++;
	}

	return xPosition;
}

Long Caret::GetYPosition() {
	Long yPosition = this->GetMemoForm()->GetMarginHeight() + this->GetMemoForm()->GetCaptionHeight();

	Memo *memo = static_cast<Memo*>(this->memoForm->GetContents());
	Long row = memo->GetRow();

	Long i = 0;
	while (i < row) {
		yPosition += this->height;
		i++;
	}

	return yPosition;
}

void Caret::UpdateCaret() {

	DestroyCaret();
	//1. set margin width, height
	Long xPosition = this->GetMemoForm()->GetMarginWidth();
	Long yPosition = this->GetMemoForm()->GetMarginHeight() + this->GetMemoForm()->GetCaptionHeight();

	//2. Get infomation
	Memo *memo = static_cast<Memo*>(this->memoForm->GetContents());
	Long row = memo->GetRow();
	Line *line = memo->GetLine(row);
	Long column = line->GetColumn();

	if (column == 0) {
		width = CARETWIDTH;
	}
	else {
		if (dynamic_cast<SingleCharacter*>(line->GetCharacter(column - 1))) {
			width = CARETWIDTH;
		}
		else if (dynamic_cast<DoubleCharacter*>(line->GetCharacter(column - 1))) {
			width = line->GetCharacter(column - 1)->GetWidth();
		}
	}
	if (this->memoForm->GetEndComposition() == FALSE) {
		column--;
	}
	else {
		width = CARETWIDTH;
	}

	//3. Get yPosition
	Long i = 0;
	while (i < row) {
		yPosition += this->height;
		i++;
	}

	//4. Get xPosition
	i = 0;
	while (i < column) {
		xPosition += line->GetCharacter(i)->GetWidth();
		i++;
	}

	//5. Set caret
	CharacterFaces *characterFaces = CharacterFaces::Instance(this->memoForm->GetDC());
	this->height = characterFaces->GetCharacterSize(127).GetHeight();

	memoForm->CWnd::CreateSolidCaret(width, height);
	CWnd::SetCaretPos(CPoint(xPosition, yPosition));
	memoForm->CWnd::ShowCaret();
}