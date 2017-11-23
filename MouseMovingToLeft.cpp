//MouseMovingToLeft.cpp

#include "MouseMovingToLeft.h"
#include "Form.h"
#include "MemoForm.h"

MouseMovingToLeft::MouseMovingToLeft(Form *form)
	:MouseAction(static_cast<MemoForm*>(form)) {
	//this->form = form;
}

MouseMovingToLeft::MouseMovingToLeft(const MouseMovingToLeft& source)
	: MouseAction(source) {
	//this->form = source.form;
}

MouseMovingToLeft::~MouseMovingToLeft() {

}

MouseMovingToLeft& MouseMovingToLeft::operator=(const MouseMovingToLeft& source) {
	//this->form = source.form;
	MouseAction::operator=(source);

	return *this;
}

#include "OtherNoteForm.h"
#include "VerticalScroll.h"
void MouseMovingToLeft::OnMouseAction(UINT nSide, LPRECT lpRect) {
	CRect pageFormWndRect;
	static_cast<MemoForm*>(this->form)->GetParent()->GetWindowRect(&pageFormWndRect);
	lpRect->left = pageFormWndRect.left + 10;
	lpRect->right = lpRect->left + static_cast<MemoForm*>(this->form)->GetMaxWidth();
}

void MouseMovingToLeft::OnMouseAction(UINT nFlags, CPoint point) {

}

void MouseMovingToLeft::OnMouseAction(int x, int y) {

}