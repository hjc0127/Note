//OtherNoteFormMouseLButtonDblClk.cpp

#include "Form.h"
#include "OtherNoteFormMouseLButtonDblClk.h"
#include "Note.h"
#include "OtherNoteForm.h"
#include "PageForm.h"
#include "Page.h"
#include "MemoForm.h"
#include "Memo.h"
#include "Caret.h"
#include "SelectedBuffer.h"
#include "Line.h"
#include "HorizontalScroll.h"
#include "VerticalScroll.h"

OtherNoteFormMouseLButtonDblClk::OtherNoteFormMouseLButtonDblClk(Form *form)
	:MouseAction(static_cast<MemoForm*>(form)) {
	//this->form = form;
}

OtherNoteFormMouseLButtonDblClk::OtherNoteFormMouseLButtonDblClk(const OtherNoteFormMouseLButtonDblClk& source)
	: MouseAction(source) {
	//this->form = source.form;
}

OtherNoteFormMouseLButtonDblClk::~OtherNoteFormMouseLButtonDblClk() {

}

OtherNoteFormMouseLButtonDblClk& OtherNoteFormMouseLButtonDblClk::operator=(const OtherNoteFormMouseLButtonDblClk& source) {
	//this->form = source.form;
	MouseAction::operator=(source);

	return *this;
}

void OtherNoteFormMouseLButtonDblClk::OnMouseAction(UINT nFlags, CPoint point) {
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	
	//1022 페이지 추가시 이전 빈메모가 삭제가 안되는것 해결하기 위해서
	otherNoteForm->GetDocumentWnd()->SetFocus();
	
	PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
	pageForm->ShowWindow(SW_HIDE);
	Long index = static_cast<Note*>(otherNoteForm->GetContents())->AddPage();
	Page *page = static_cast<Note*>(otherNoteForm->GetContents())->GetPage(index);
	index = otherNoteForm->AddPageForm(page);
	pageForm = otherNoteForm->GetPageForm(index);
	pageForm->ShowWindow(SW_SHOW);
	otherNoteForm->GetTabCtrl()->SetCurSel(index);
	pageForm->SetFocus();
	otherNoteForm->GetHorizontalScroll()->SetCurrent(index);
	otherNoteForm->GetVerticalScroll()->SetCurrent(index);
	/*CRect rect1;
	CRect rect2;
	otherNoteForm->GetPageForm(0)->GetClientRect(&rect1);
	otherNoteForm->GetPageForm(1)->GetClientRect(&rect2);*/
	otherNoteForm->GetTabCtrl()->DrawTabItem();
}

void OtherNoteFormMouseLButtonDblClk::OnMouseAction(int x, int y) {

}

void OtherNoteFormMouseLButtonDblClk::OnMouseAction(UINT nSide, LPRECT lpRect) {

}