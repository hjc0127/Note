//PaintVisitor.cpp

#include "PaintVisitor.h"
#include "Memo.h"
#include "Line.h"
#include "CharacterFaces.h"
#include "MemoForm.h"
#include <afxWin.h>
using namespace std;

//PaintVisitor::PaintVisitor()
//	:Visitor() {
//
//}

//PaintVisitor::PaintVisitor(CDC *dc)
//	: Visitor(), dc(dc) {
//
//}

//PaintVisitor::PaintVisitor(CPaintDC *dc, CRect* rect)
PaintVisitor::PaintVisitor(CDC *dc, CRect* rect)
	:Visitor() {
	this->dc = static_cast<CPaintDC*>(dc);
	this->rect = rect;
}

PaintVisitor::PaintVisitor(const PaintVisitor& source)
	: Visitor(source) {
	this->dc = source.dc;
	this->rect = source.rect;
}

PaintVisitor::~PaintVisitor() {

}

PaintVisitor& PaintVisitor::operator=(const PaintVisitor& source) {
	Visitor::operator=(source);
	this->dc = source.dc;
	this->rect = source.rect;

	return *this;
}

void PaintVisitor::Visit(Note *note) {
	
}

#include "MakeStringVisitor.h"
#include "Page.h"
void PaintVisitor::Visit(Page *page) {
	
}

#include "MakeStringVisitor.h"
#include "OtherNoteForm.h"
#include "PageForm.h"
#include "Note.h"
void PaintVisitor::Visit(Memo *memo) {
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

	//this->SetColor();//함수로 빼는게 좋을듯
	if (memoForm->GetColorType() == MEMOFORM_COLOR_PURPLE) {
		//1. client 그리기
		this->dc->FillSolidRect(this->rect, RGB(230, 230, 250));
		//2. capion 그리기
		this->dc->FillSolidRect(this->rect->left, this->rect->top, this->rect->right - this->rect->left, MEMOFORM_CAPTION_HEIGHT, RGB(123, 104, 238));
	}
	else if (memoForm->GetColorType() == MEMOFORM_COLOR_YELLOW){
		//1. client 그리기
		this->dc->FillSolidRect(this->rect, RGB(252, 242, 181));
		//2. capion 그리기
		this->dc->FillSolidRect(this->rect->left, this->rect->top, this->rect->right - this->rect->left, MEMOFORM_CAPTION_HEIGHT, RGB(255, 185, 0));
	}
	else if (memoForm->GetColorType() == MEMOFORM_COLOR_GREEN) {
		//1. client 그리기
		this->dc->FillSolidRect(this->rect, RGB(239, 250, 237));
		//2. capion 그리기
		this->dc->FillSolidRect(this->rect->left, this->rect->top, this->rect->right - this->rect->left, MEMOFORM_CAPTION_HEIGHT, RGB(199, 239, 196));
	}
	else if (memoForm->GetColorType() == MEMOFORM_COLOR_BLUE) {
		//1. client 그리기
		this->dc->FillSolidRect(this->rect, RGB(238, 247, 255));
		//2. capion 그리기
		this->dc->FillSolidRect(this->rect->left, this->rect->top, this->rect->right - this->rect->left, MEMOFORM_CAPTION_HEIGHT, RGB(202, 232, 250));
	}
	else if (memoForm->GetColorType() == MEMOFORM_COLOR_PINK) {
		//1. client 그리기
		this->dc->FillSolidRect(this->rect, RGB(255, 238, 251));
		//2. capion 그리기
		this->dc->FillSolidRect(this->rect->left, this->rect->top, this->rect->right - this->rect->left, MEMOFORM_CAPTION_HEIGHT, RGB(255, 195, 245));
	}
	else if (memoForm->GetColorType() == MEMOFORM_COLOR_GRAY) {
		//1. client 그리기
		this->dc->FillSolidRect(this->rect, RGB(251, 251, 251));
		//2. capion 그리기
		this->dc->FillSolidRect(this->rect->left, this->rect->top, this->rect->right - this->rect->left, MEMOFORM_CAPTION_HEIGHT, RGB(243, 243, 243));
	}

	if (memoForm->GetFocusType() == MEMOFORM_FOCUS_CAPTION) {
		CPen NewPen;
		NewPen.CreatePen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT | PS_JOIN_ROUND, 5, RGB(63, 72, 204));
		CPen *pOldPen = this->dc->SelectObject(&NewPen);
		this->dc->MoveTo(this->rect->left, this->rect->top);
		this->dc->LineTo(this->rect->left, this->rect->bottom - 1);
		this->dc->LineTo(this->rect->right - 1, this->rect->bottom - 1);
		this->dc->LineTo(this->rect->right - 1, this->rect->top);
		this->dc->LineTo(this->rect->left, this->rect->top);
		this->dc->SelectObject(pOldPen);
	}
	
	////1. client 그리기
	//this->dc->FillSolidRect(this->rect, RGB(230, 230, 250));
	////2. capion 그리기
	//this->dc->FillSolidRect(this->rect->left, this->rect->top, this->rect->right - this->rect->left, MEMOFORM_CAPTION_HEIGHT, RGB(123, 104, 238));
	//3. font를 설한다.
	CharacterFaces *characterFaces = CharacterFaces::Instance(this->dc);
	CFont font;
	font.CreatePointFont(characterFaces->GetFontSize(), characterFaces->GetFontFamily().c_str());
	this->dc->SelectObject(&font);
	this->dc->SetBkMode(TRANSPARENT);
	//4. 그려질 영역을 설정한다. 
	CRect clientRect(this->rect->left, this->rect->top + MEMOFORM_CAPTION_HEIGHT, this->rect->right, this->rect->bottom);
	Long lineHeight = clientRect.top + MEMOFORM_MARGIN_TOP;
	//5. 메모폼에 글씨를 쓴다.
	Long i = 0;
	while (i < memo->GetLength()) {
		MakeStringVisitor makeStringVisitor;
		memo->GetLine(i)->Accept(&makeStringVisitor);
		int nTabStop = characterFaces->GetCharacterSize(32).GetWidth() * 8;		
		this->dc->TabbedTextOut(clientRect.left + MEMOFORM_MARGIN_LEFT, lineHeight, makeStringVisitor.GetCompleteString().c_str(), 1, &nTabStop, clientRect.left + MEMOFORM_MARGIN_LEFT);
		lineHeight += characterFaces->GetCharacterSize(97).GetHeight();
		i++;
	}
}

void PaintVisitor::Visit(Line *line) {
	
}

void PaintVisitor::Visit(SingleCharacter *singleCharacter) {

}

void PaintVisitor::Visit(DoubleCharacter *doubleCharacter) {

}

void PaintVisitor::Visit(Character *character) {
	
}