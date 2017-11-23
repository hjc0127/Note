//MouseMovingToRight.cpp

#include "MouseScrollingToRight.h"
#include "Form.h"
#include "MemoForm.h"

MouseScrollingToRight::MouseScrollingToRight(Form *form)
	:MouseAction(static_cast<MemoForm*>(form)){
	//this->form = form;
}

MouseScrollingToRight::MouseScrollingToRight(const MouseScrollingToRight& source)
	:MouseAction(source) {
	//this->form = source.form;
}

MouseScrollingToRight::~MouseScrollingToRight() {

}

MouseScrollingToRight& MouseScrollingToRight::operator=(const MouseScrollingToRight& source) {
	//this->form = source.form;
	MouseAction::operator=(source);

	return *this;
}

#include "OtherNoteForm.h"
#include "PageForm.h"
#include "HorizontalScroll.h"
void MouseScrollingToRight::OnMouseAction(UINT nSide, LPRECT lpRect) {
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	otherNoteForm->GetHorizontalScroll()->ScrollNext(150);
	CPoint mousePoint;
	GetCursorPos(&mousePoint);
	SetCursorPos(mousePoint.x - 150, mousePoint.y);
}

void MouseScrollingToRight::OnMouseAction(UINT nFlags, CPoint point) {

}

void MouseScrollingToRight::OnMouseAction(int x, int y) {

}