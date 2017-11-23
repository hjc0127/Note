//MouseMovingToTop.cpp

#include "MouseScrollingToTop.h"
#include "Form.h"
#include "MemoForm.h"

MouseScrollingToTop::MouseScrollingToTop(Form *form)
	:MouseAction(static_cast<MemoForm*>(form)){
	//this->form = form;
}

MouseScrollingToTop::MouseScrollingToTop(const MouseScrollingToTop& source) 
	:MouseAction(source){
	//this->form = source.form;
}

MouseScrollingToTop::~MouseScrollingToTop() {

}

MouseScrollingToTop& MouseScrollingToTop::operator=(const MouseScrollingToTop& source) {
	//this->form = source.form;
	MouseAction::operator=(source);

	return *this;
}

#include "OtherNoteForm.h"
#include "VerticalScroll.h"
void MouseScrollingToTop::OnMouseAction(UINT nSide, LPRECT lpRect) {
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
		otherNoteForm->GetVerticalScroll()->ScrollPrevious(150);
		CPoint mousePoint;
		GetCursorPos(&mousePoint);
		SetCursorPos(mousePoint.x, mousePoint.y + 30);
}

void MouseScrollingToTop::OnMouseAction(UINT nFlags, CPoint point) {

}

void MouseScrollingToTop::OnMouseAction(int x, int y) {

}