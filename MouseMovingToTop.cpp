//MouseMovingToTop.cpp

#include "MouseMovingToTop.h"
#include "Form.h"
#include "MemoForm.h"

MouseMovingToTop::MouseMovingToTop(Form *form)
	:MouseAction(static_cast<MemoForm*>(form)) {
	//this->form = form;
}

MouseMovingToTop::MouseMovingToTop(const MouseMovingToTop& source)
	: MouseAction(source) {
	//this->form = source.form;
}

MouseMovingToTop::~MouseMovingToTop() {

}

MouseMovingToTop& MouseMovingToTop::operator=(const MouseMovingToTop& source) {
	//this->form = source.form;
	MouseAction::operator=(source);

	return *this;
}

#include "OtherNoteForm.h"
#include "VerticalScroll.h"
void MouseMovingToTop::OnMouseAction(UINT nSide, LPRECT lpRect) {
	CRect pageFormWndRect;
	static_cast<MemoForm*>(this->form)->GetParent()->GetWindowRect(&pageFormWndRect);
	lpRect->top = pageFormWndRect.top + 10;
	lpRect->bottom = lpRect->top + static_cast<MemoForm*>(this->form)->GetMaxHeight();
}

void MouseMovingToTop::OnMouseAction(UINT nFlags, CPoint point) {

}

void MouseMovingToTop::OnMouseAction(int x, int y) {

}