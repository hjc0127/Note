//MouseMove.cpp

#include "MouseMove.h"
#include "Form.h"
#include "MemoForm.h"
#include "Pageform.h"

MouseMove::MouseMove(Form *form)
	:MouseAction(static_cast<MemoForm*>(form)){
	//this->form = form;
}

MouseMove::MouseMove(const MouseMove& source) 
	:MouseAction(source){
	//this->form = source.form;
}

MouseMove::~MouseMove() {

}

MouseMove& MouseMove::operator=(const MouseMove& source) {
	//this->form = source.form;
	MouseAction::operator=(source);

	return *this;
}

void MouseMove::OnMouseAction(int x, int y) {
	if (static_cast<MemoForm*>(this->form)->GetIsHovered() == FALSE) {
		static_cast<MemoForm*>(this->form)->SetIsHovered(TRUE);
		MemoForm *memoForm = static_cast<PageForm*>(this->form->GetParent())->GetHoveredMemo();
		if (memoForm != NULL) {
			memoForm->SetIsHovered(FALSE);
			memoForm->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_NOERASE);
		}
		static_cast<PageForm*>(this->form->GetParent())->HoverMemo(static_cast<MemoForm*>(this->form));
		static_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_NOERASE);
	}
}


void MouseMove::OnMouseAction(UINT nFlags, CPoint point) {

}

void MouseMove::OnMouseAction(UINT nSide, LPRECT lpRect) {

}