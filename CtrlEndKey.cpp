//CtrlEndKey.cpp

#include "CtrlEndKey.h"

CtrlEndKey::CtrlEndKey(Form *form)
	:KeyAction(form) {

}

CtrlEndKey::CtrlEndKey(const CtrlEndKey& source)
	: KeyAction(source) {

}

CtrlEndKey::~CtrlEndKey() {

}

CtrlEndKey& CtrlEndKey::operator=(const CtrlEndKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "SelectedBuffer.h"
#include "OtherNoteForm.h"
#include "PageForm.h"
#include "HorizontalScroll.h"
#include "VerticalScroll.h"
void CtrlEndKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (dynamic_cast<MemoForm*>(this->form)) {
		Memo *memo = static_cast<Memo*>(this->form->GetContents());
		memo->MoveLastRow();

		Line *line = memo->GetLine(memo->GetRow());
		line->MoveLastColumn();

		Caret *caret = dynamic_cast<MemoForm*>(this->form)->GetCaret();

		//caret->MoveLastLine();
		//caret->MoveLastCharacter();
		caret->UpdateCaret();
		dynamic_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);

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
		else if (point.x < docWndRect.left) {
			otherNoteForm->GetHorizontalScroll()->ScrollPrevious(docWndRect.left - point.x + 50);
		}

		if (point.y + 50 > docWndRect.bottom) {
			otherNoteForm->GetVerticalScroll()->ScrollNext(point.y + 50 - docWndRect.bottom);
		}
		////////////////////////////////////////////////////////////////////////////////////////////
	}
}