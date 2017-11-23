//MouseMovingToLeft.cpp

#include "MouseScrollingToLeft.h"
#include "Form.h"
#include "MemoForm.h"

MouseScrollingToLeft::MouseScrollingToLeft(Form *form)
	:MouseAction(static_cast<MemoForm*>(form)){
	//this->form = form;
}

MouseScrollingToLeft::MouseScrollingToLeft(const MouseScrollingToLeft& source) 
	:MouseAction(source){
	//this->form = source.form;
}

MouseScrollingToLeft::~MouseScrollingToLeft() {

}

MouseScrollingToLeft& MouseScrollingToLeft::operator=(const MouseScrollingToLeft& source) {
	//this->form = source.form;
	MouseAction::operator=(source);

	return *this;
}

#include "OtherNoteForm.h"
#include "HorizontalScroll.h"
void MouseScrollingToLeft::OnMouseAction(UINT nSide, LPRECT lpRect) {
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	otherNoteForm->GetHorizontalScroll()->ScrollPrevious(150);
	CPoint mousePoint;
	GetCursorPos(&mousePoint);
	SetCursorPos(mousePoint.x + 60, mousePoint.y);
}


void MouseScrollingToLeft::OnMouseAction(UINT nFlags, CPoint point) {

}

void MouseScrollingToLeft::OnMouseAction(int x, int y) {

}