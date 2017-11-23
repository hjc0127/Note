//MouseLButtonDown.cpp

#include "Form.h"
#include "MouseLButtonDown.h"
#include "Note.h"
#include "OtherNoteForm.h"
#include "PageForm.h"
#include "Page.h"
#include "MemoForm.h"
#include "Memo.h"
#include "Caret.h"
#include "SelectedBuffer.h"
#include "Line.h"

MouseLButtonDown::MouseLButtonDown(Form *form)
	:MouseAction(static_cast<MemoForm*>(form)) {
	//this->form = form;
}

MouseLButtonDown::MouseLButtonDown(const MouseLButtonDown& source) 
	:MouseAction(source) {
	//this->form = source.form;
}

MouseLButtonDown::~MouseLButtonDown() {

}

MouseLButtonDown& MouseLButtonDown::operator=(const MouseLButtonDown& source) {
	//this->form = source.form;
	MouseAction::operator=(source);

	return *this;
}

void MouseLButtonDown::OnMouseAction(UINT nFlags, CPoint point) {
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	Note *note = (Note*)(otherNoteForm->GetContents());
	PageForm *pageForm = otherNoteForm->GetPageForm(note->GetCurrent());

	Long i = 0;
	while (pageForm->GetMemoForm(i) != static_cast<MemoForm*>(this->form) && i < pageForm->GetLength()) {
		i++;
	}
	Page *page = static_cast<Page*>(pageForm->GetContents());
	page->SetCurrent(i);
	static_cast<MemoForm*>(this->form)->UpdateIndex(point);
	static_cast<MemoForm*>(this->form)->GetCaret()->UpdateCaret();
	static_cast<MemoForm*>(this->form)->SetIsCaption(false);
	static_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);
	Memo *memo = static_cast<Memo*>(static_cast<MemoForm*>(this->form)->GetContents());
	Line *line = memo->GetLine(memo->GetRow());
	static_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetInitialPosition(memo->GetRow(), line->GetColumn());
	static_cast<MemoForm*>(this->form)->SetFocusType(MEMOFORM_FOCUS_CLIENT);
	static_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
}

void MouseLButtonDown::OnMouseAction(int x, int y) {

}

void MouseLButtonDown::OnMouseAction(UINT nSide, LPRECT lpRect) {

}