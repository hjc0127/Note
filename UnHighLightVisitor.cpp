// UnHighLightVisitor.cpp

#include "UnHighLightVisitor.h"
#include "Memo.h"
#include "Line.h"
#include "Character.h"
#include "CharacterFaces.h"
#include "SingleCharacter.h"
#include "DoubleCharacter.h"
#include "MemoForm.h"

UnHighLightVisitor::UnHighLightVisitor(CDC *dc)
	:Visitor() {
	this->dc = dc;
}

UnHighLightVisitor::UnHighLightVisitor(const UnHighLightVisitor& source)
	: Visitor(source) {
}

UnHighLightVisitor::~UnHighLightVisitor() {

}

UnHighLightVisitor& UnHighLightVisitor::operator=(const UnHighLightVisitor& source) {
	Visitor::operator=(source);

	return *this;
}

void UnHighLightVisitor::Visit(Note *note) {

}

void UnHighLightVisitor::Visit(Page *page) {

}

#include "OtherNoteForm.h"
#include "Note.h"
#include "PageForm.h"
void UnHighLightVisitor::Visit(Memo *memo) {
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
	
	//1109
	//this->dc->SetBkColor(RGB(230, 230, 250));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CWnd::FindWindow("OtherNote", NULL));
	Note *note = (Note*)(otherNoteForm->GetContents());
	PageForm *pageForm = otherNoteForm->GetPageForm(note->GetCurrent());

	Long j = 0;
	MemoForm *memoForm = pageForm->GetMemoForm(j);
	while (j < pageForm->GetLength() && pageForm->GetMemoForm(j)->GetContents() != memo) {
		j++;
		memoForm = pageForm->GetMemoForm(j);
	}
	memoForm = pageForm->GetMemoForm(j);
	if (memoForm->GetColorType() == MEMOFORM_COLOR_PURPLE) {
		this->dc->SetBkColor(RGB(230, 230, 250));
	}
	else if (memoForm->GetColorType() == MEMOFORM_COLOR_YELLOW) {
		this->dc->SetBkColor(RGB(252, 242, 181));
	}
	else if (memoForm->GetColorType() == MEMOFORM_COLOR_GREEN) {
		this->dc->SetBkColor(RGB(239, 250, 237));
	}
	else if (memoForm->GetColorType() == MEMOFORM_COLOR_BLUE) {
		this->dc->SetBkColor(RGB(238, 247, 255));
	}
	else if (memoForm->GetColorType() == MEMOFORM_COLOR_PINK) {
		this->dc->SetBkColor(RGB(255, 238, 251));
	}
	else if (memoForm->GetColorType() == MEMOFORM_COLOR_GRAY) {
		this->dc->SetBkColor(RGB(251, 251, 251));
	}
	//

	this->dc->SetTextColor(RGB(0, 0, 0));

	if (line->GetLength() > 0) {
		Long xPos;// = 0;
		Long yPos = MEMOFORM_MARGIN_TOP + MEMOFORM_CAPTION_HEIGHT;//20;
		Long i = 0;
		Long begin_xPos;
		bool highLight = false;
		bool isDraw = false;

		while (i < memo->GetLength()) {
			line = memo->GetLine(i);
			Long j = 0;
			xPos = MEMOFORM_MARGIN_LEFT;// 0;
			begin_xPos = -1;

			CString str;

			while (j < line->GetLength()) {
				if (line->GetCharacter(j)->GetHighLight() == false) {
					if (begin_xPos == -1) {
						begin_xPos = xPos;
						highLight = true;
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
					if (highLight == true) {
						highLight = false;
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

void UnHighLightVisitor::Visit(Line *line) {

}
void UnHighLightVisitor::Visit(Character *character) {

}
void UnHighLightVisitor::Visit(SingleCharacter *singleCharacter) {

}
void UnHighLightVisitor::Visit(DoubleCharacter *doubleCharacter) {

}

