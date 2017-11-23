//MouseMovingToBottom.cpp

#include "MouseScrollingToBottom.h"
#include "Form.h"
#include "MemoForm.h"

MouseScrollingToBottom::MouseScrollingToBottom(Form *form)
	:MouseAction(static_cast<MemoForm*>(form)){
	//this->form = form;
}

MouseScrollingToBottom::MouseScrollingToBottom(const MouseScrollingToBottom& source) 
	:MouseAction(source){
	//this->form = source.form;
}

MouseScrollingToBottom::~MouseScrollingToBottom() {

}

MouseScrollingToBottom& MouseScrollingToBottom::operator=(const MouseScrollingToBottom& source) {
	//this->form = source.form;
	MouseAction::operator=(source);

	return *this;
}

#include "OtherNoteForm.h"
#include "VerticalScroll.h"
#include "PageForm.h"
void MouseScrollingToBottom::OnMouseAction(UINT nSide, LPRECT lpRect) {
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	otherNoteForm->GetVerticalScroll()->ScrollNext(150);
	CPoint mousePoint;
	GetCursorPos(&mousePoint);
	SetCursorPos(mousePoint.x, mousePoint.y - 150);
}


void MouseScrollingToBottom::OnMouseAction(UINT nFlags, CPoint point) {

}

void MouseScrollingToBottom::OnMouseAction(int x, int y) {

}