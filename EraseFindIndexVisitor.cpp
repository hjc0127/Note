// EraseFindIndexVisitor.cpp

#include "EraseFindIndexVisitor.h"
#include "Note.h"
#include "Page.h"
#include "Memo.h"
#include "Line.h"
#include "Character.h"
#include "CharacterFaces.h"
#include "SingleCharacter.h"
#include "DoubleCharacter.h"
#include "MemoForm.h"

EraseFindIndexVisitor::EraseFindIndexVisitor(CDC *dc)
	:Visitor() {
	this->dc = dc;
}

EraseFindIndexVisitor::EraseFindIndexVisitor(const EraseFindIndexVisitor& source)
	: Visitor(source) {
}

EraseFindIndexVisitor::~EraseFindIndexVisitor() {

}

EraseFindIndexVisitor& EraseFindIndexVisitor::operator=(const EraseFindIndexVisitor& source) {
	Visitor::operator=(source);

	return *this;
}

void EraseFindIndexVisitor::Visit(Note *note) {
	ArrayIterator<Contents*> *pageIterator = note->CreateIterator();
	pageIterator->First();
	while (!pageIterator->IsDone()) {
		Page *page = static_cast<Page*>(pageIterator->CurrentItem());
		page->Accept(this);
		pageIterator->Next();
	}
	if (pageIterator != 0) {
		delete pageIterator;
	}
}

void EraseFindIndexVisitor::Visit(Page *page) {
	ArrayIterator<Contents*> *memoIterator = page->CreateIterator();
	memoIterator->First();
	while (!memoIterator->IsDone()) {
		Memo *memo = static_cast<Memo*>(memoIterator->CurrentItem());
		memo->Accept(this);
		memoIterator->Next();
	}
	if (memoIterator != 0) {
		delete memoIterator;
	}
}

void EraseFindIndexVisitor::Visit(Memo *memo) {
	//Memo *memo = static_cast<Memo*>(this->GetContents());
	Line *line = memo->GetLine(0);
	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	CharacterSize characterSize = characterFaces->GetCharacterSize(97);
	Long characterHeight = characterSize.GetHeight();

	//우리폰트에 맞게 다시 설정해줌
	CFont font;
	font.CreatePointFont(characterFaces->GetFontSize(), characterFaces->GetFontFamily().c_str());

	this->dc->SelectObject(&font);
	this->dc->SetBkMode(OPAQUE);
	this->dc->SetBkColor(RGB(230, 230, 250));
	this->dc->SetTextColor(RGB(0, 0, 0));

	if (line->GetLength() > 0) {
		Long xPos;// = 0;
		Long yPos = MEMOFORM_MARGIN_TOP + MEMOFORM_CAPTION_HEIGHT;//20;
		Long i = 0;
		Long begin_xPos;
		bool isFindIndexPainted = false;
		bool isDraw = false;

		while (i < memo->GetLength()) {
			line = memo->GetLine(i);
			Long j = 0;
			xPos = MEMOFORM_MARGIN_LEFT;// 0;
			begin_xPos = -1;

			CString str;

			while (j < line->GetLength()) {
				if (line->GetCharacter(j)->GetIsFindIndexPainted() == false) {
					if (begin_xPos == -1) {
						begin_xPos = xPos;
						isFindIndexPainted = true;
					}
					if (dynamic_cast<SingleCharacter*>(line->GetCharacter(j))) {
						str += CString(dynamic_cast<SingleCharacter*>(line->GetCharacter(j))->GetValue());
					}
					else {
						string composition;
						composition += dynamic_cast<DoubleCharacter*>(line->GetCharacter(j))->GetValue()[0];
						composition += dynamic_cast<DoubleCharacter*>(line->GetCharacter(j))->GetValue()[1];
						str += composition.c_str();
					}
				}
				else {
					if (isFindIndexPainted == true) {
						isFindIndexPainted = false;
						isDraw = true;
					}
				}
				if (isDraw == true || j == line->GetLength() - 1) {
					this->dc->TextOutA(begin_xPos, yPos, str);
					str = "";
					begin_xPos = -1;
					isDraw = false;
				}
				xPos += line->GetCharacter(j)->GetWidth();
				j++;
			}
			yPos += characterHeight;
			i++;
		}
	}
}

void EraseFindIndexVisitor::Visit(Line *line) {

}
void EraseFindIndexVisitor::Visit(Character *character) {

}
void EraseFindIndexVisitor::Visit(SingleCharacter *singleCharacter) {

}
void EraseFindIndexVisitor::Visit(DoubleCharacter *doubleCharacter) {

}

