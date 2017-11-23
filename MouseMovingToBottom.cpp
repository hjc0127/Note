//MouseMovingToBottom.cpp

#include "MouseMovingToBottom.h"
#include "Form.h"
#include "MemoForm.h"

MouseMovingToBottom::MouseMovingToBottom(Form *form)
	:MouseAction(static_cast<MemoForm*>(form)) {
	//this->form = form;
}

MouseMovingToBottom::MouseMovingToBottom(const MouseMovingToBottom& source)
	: MouseAction(source) {
	//this->form = source.form;
}

MouseMovingToBottom::~MouseMovingToBottom() {

}

MouseMovingToBottom& MouseMovingToBottom::operator=(const MouseMovingToBottom& source) {
	//this->form = source.form;
	MouseAction::operator=(source);

	return *this;
}

#include "OtherNoteForm.h"
#include "VerticalScroll.h"
#include "Note.h"
#include "PageForm.h"
void MouseMovingToBottom::OnMouseAction(UINT nSide, LPRECT lpRect) {
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	CRect pageFormWndRect;
	static_cast<MemoForm*>(this->form)->GetParent()->GetWindowRect(&pageFormWndRect);
	CRect pageFormClientRect;
	static_cast<MemoForm*>(this->form)->GetParent()->GetClientRect(&pageFormClientRect);

	if (pageFormClientRect.Height() != PAGEFORM_MAX_HEIGHT) {
		static_cast<PageForm*>(static_cast<MemoForm*>(this->form)->GetParent())->ResizeWindow(0, lpRect->bottom - pageFormWndRect.bottom);
		static_cast<PageForm*>(static_cast<MemoForm*>(this->form)->GetParent())->UpdateScrinfo();
		SCROLLINFO vScrinfo = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent())->GetVScrinfo();
		otherNoteForm->GetVerticalScroll()->GetScrollBar()->SetScrollInfo(&vScrinfo);
	}
	else {
		lpRect->bottom = pageFormWndRect.bottom - 10;
		lpRect->top = lpRect->bottom - static_cast<MemoForm*>(this->form)->GetMaxHeight();
	}
}

void MouseMovingToBottom::OnMouseAction(UINT nFlags, CPoint point) {

}

void MouseMovingToBottom::OnMouseAction(int x, int y) {

}