//EndKey.cpp

#include "EndKey.h"
#include "MemoForm.h"

EndKey::EndKey(Form *form)
	:KeyAction(form) {

}

EndKey::EndKey(const EndKey& source)
	: KeyAction(source) {

}

EndKey::~EndKey() {

}

EndKey& EndKey::operator=(const EndKey& source) {
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
void EndKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	Memo *memo = static_cast<Memo*>(this->form->GetContents());

	Line *line = memo->GetLine(memo->GetRow());
	line->MoveLastColumn();

	Caret *caret = dynamic_cast<MemoForm*>(this->form)->GetCaret();
	//caret->MoveLastCharacter();
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
	if (point.x + 50 > docWndRect.right) {
		otherNoteForm->GetHorizontalScroll()->ScrollNext(point.x + 50 - docWndRect.right);
	}
	////////////////////////////////////////////////////////////////////////////////////////////
}