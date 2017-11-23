//MouseMovingToRight.cpp

#include "MouseMovingToRight.h"
#include "Form.h"
#include "MemoForm.h"

MouseMovingToRight::MouseMovingToRight(Form *form)
	:MouseAction(static_cast<MemoForm*>(form)) {
	//this->form = form;
}

MouseMovingToRight::MouseMovingToRight(const MouseMovingToRight& source)
	: MouseAction(source) {
	//this->form = source.form;
}

MouseMovingToRight::~MouseMovingToRight() {

}

MouseMovingToRight& MouseMovingToRight::operator=(const MouseMovingToRight& source) {
	//this->form = source.form;
	MouseAction::operator=(source);

	return *this;
}

#include "OtherNoteForm.h"
#include "HorizontalScroll.h"
#include "Note.h"
#include "PageForm.h"
void MouseMovingToRight::OnMouseAction(UINT nSide, LPRECT lpRect) {
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	CRect pageFormWndRect;
	static_cast<MemoForm*>(this->form)->GetParent()->GetWindowRect(&pageFormWndRect);
	CRect pageFormClientRect;
	static_cast<MemoForm*>(this->form)->GetParent()->GetClientRect(&pageFormClientRect);
	
	if (pageFormClientRect.Width() != PAGEFORM_MAX_WIDTH) {
		static_cast<PageForm*>(static_cast<MemoForm*>(this->form)->GetParent())->ResizeWindow(lpRect->right - pageFormWndRect.right, 0);
		static_cast<PageForm*>(static_cast<MemoForm*>(this->form)->GetParent())->UpdateScrinfo();
		SCROLLINFO hScrinfo = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent())->GetHScrinfo();
		otherNoteForm->GetHorizontalScroll()->GetScrollBar()->SetScrollInfo(&hScrinfo);
	}
	else {
		lpRect->right = pageFormWndRect.right - 10;
		lpRect->left = lpRect->right - static_cast<MemoForm*>(this->form)->GetMaxWidth();
	}
}

void MouseMovingToRight::OnMouseAction(UINT nFlags, CPoint point) {

}

void MouseMovingToRight::OnMouseAction(int x, int y) {

}