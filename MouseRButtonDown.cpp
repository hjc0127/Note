//MouseRButtonDown.cpp

#include "MouseRButtonDown.h"
#include "Form.h"
#include "MemoForm.h"

MouseRButtonDown::MouseRButtonDown(Form *form)
	:MouseAction(static_cast<MemoForm*>(form)) {
	//this->form = form;
}

MouseRButtonDown::MouseRButtonDown(const MouseRButtonDown& source) 
	:MouseAction(source){
	//this->form = source.form;
}

MouseRButtonDown::~MouseRButtonDown() {

}

MouseRButtonDown& MouseRButtonDown::operator=(const MouseRButtonDown& source) {
	//this->form = source.form;
	MouseAction::operator=(source);

	return *this;
}

#include "SelectedBuffer.h"
void MouseRButtonDown::OnMouseAction(UINT nFlags, CPoint point) {
	static_cast<MemoForm*>(this->form)->SetFocus();
	static_cast<MemoForm*>(this->form)->RedrawWindow();
	if (static_cast<MemoForm*>(this->form)->GetSelectedBuffer()->GetIsSelecting() == true) {
		CMenu menu;
		menu.LoadMenu(IDR_MENU_MEMOFORM);
		CMenu *popupMenu = menu.GetSubMenu(0);
		CPoint position;
		GetCursorPos(&position);
		popupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, position.x, position.y, static_cast<MemoForm*>(this->form));
		menu.DestroyMenu();
	}
}

void MouseRButtonDown::OnMouseAction(int x, int y) {

}

void MouseRButtonDown::OnMouseAction(UINT nSide, LPRECT lpRect) {

}