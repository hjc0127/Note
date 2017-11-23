//PageFormMouseLButtonDown.cpp

#include "Form.h"
#include "PageFormMouseLButtonDown.h"
#include "Note.h"
#include "OtherNoteForm.h"
#include "PageForm.h"
#include "Page.h"
#include "MemoForm.h"
#include "Memo.h"
#include "Caret.h"
#include "SelectedBuffer.h"
#include "Line.h"

PageFormMouseLButtonDown::PageFormMouseLButtonDown(Form *form)
	:MouseAction(static_cast<PageForm*>(form)) {
	//this->form = form;
}

PageFormMouseLButtonDown::PageFormMouseLButtonDown(const PageFormMouseLButtonDown& source)
	: MouseAction(source) {
	//this->form = source.form;
}

PageFormMouseLButtonDown::~PageFormMouseLButtonDown() {

}

PageFormMouseLButtonDown& PageFormMouseLButtonDown::operator=(const PageFormMouseLButtonDown& source) {
	//this->form = source.form;
	MouseAction::operator=(source);

	return *this;
}

void PageFormMouseLButtonDown::OnMouseAction(UINT nFlags, CPoint point) {
	Long index = static_cast<Page*>(static_cast<PageForm*>(this->form)->GetContents())->AddMemo();
	//Memo *memo = static_cast<Page*>(this->contents)->GetMemo(static_cast<Page*>(this->contents)->GetCurrentMemo());
	Memo *memo = static_cast<Page*>(static_cast<PageForm*>(this->form)->GetContents())->GetMemo(index);
	memo->AddLine();
	//Long current = this->AddMemoForm(memo, point);
	CRect rect;
	rect.left = point.x;
	rect.top = point.y;
	rect.right = rect.left + 300;
	rect.bottom = rect.top + 200;
	Long current = static_cast<PageForm*>(this->form)->AddMemoForm(memo, rect);
	MemoForm *memoForm = static_cast<PageForm*>(this->form)->GetMemoForm(current);
	//static_cast<PageForm*>(this->form)->FocusMemo(memoForm);
	memoForm->SetFocus();
	memoForm->RePosition();
}

void PageFormMouseLButtonDown::OnMouseAction(int x, int y) {

}

void PageFormMouseLButtonDown::OnMouseAction(UINT nSide, LPRECT lpRect) {

}