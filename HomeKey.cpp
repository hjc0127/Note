//HomeKey.cpp

#include "HomeKey.h"
#include "MemoForm.h"

HomeKey::HomeKey(Form *form)
	:KeyAction(form) {

}

HomeKey::HomeKey(const HomeKey& source)
	: KeyAction(source) {

}

HomeKey::~HomeKey() {

}

HomeKey& HomeKey::operator=(const HomeKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "Memo.h"
#include "Line.h"
#include "Caret.h"
#include "SelectedBuffer.h"
#include "OtherNoteForm.h"
#include "PageForm.h"
#include "HorizontalScroll.h"
void HomeKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Memo *memo = static_cast<Memo*>(this->form->GetContents());

	Line *line = memo->GetLine(memo->GetRow());
	line->MoveFirstColumn();

	Caret *caret = dynamic_cast<MemoForm*>(this->form)->GetCaret();
	//caret->MoveFirstCharacter();
	caret->UpdateCaret();
	static_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);

	//1109 scroll to first column in a row
	////////////////////////////////////////////////////////////////////////////////////////
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	CRect docWndRect;
	otherNoteForm->GetDocumentWnd()->GetWindowRect(&docWndRect);
	static_cast<PageForm*>(static_cast<MemoForm*>(this->form)->GetParent())->UpdateSize(static_cast<MemoForm*>(this->form));

	CPoint point;
	point.x = static_cast<MemoForm*>(this->form)->GetCaret()->GetXPosition();
	point.y = static_cast<MemoForm*>(this->form)->GetCaret()->GetYPosition();
	static_cast<MemoForm*>(this->form)->ClientToScreen(&point);

	if (point.x < docWndRect.left) {
		otherNoteForm->GetHorizontalScroll()->ScrollPrevious(docWndRect.left - point.x + 50);
	}
	////////////////////////////////////////////////////////////////////////////////////////////
}