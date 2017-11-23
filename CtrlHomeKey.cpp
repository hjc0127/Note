//CtrlHomeKey.cpp

#include "CtrlHomeKey.h"

CtrlHomeKey::CtrlHomeKey(Form *form)
	:KeyAction(form) {

}

CtrlHomeKey::CtrlHomeKey(const CtrlHomeKey& source)
	: KeyAction(source) {

}

CtrlHomeKey::~CtrlHomeKey() {

}

CtrlHomeKey& CtrlHomeKey::operator=(const CtrlHomeKey& source) {
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
void CtrlHomeKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (dynamic_cast<MemoForm*>(this->form)) {
		Memo *memo = static_cast<Memo*>(this->form->GetContents());
		memo->MoveFirstRow();

		Line *line = memo->GetLine(memo->GetRow());
		line->MoveFirstColumn();

		Caret *caret = dynamic_cast<MemoForm*>(this->form)->GetCaret();
		//caret->MoveFirstLine();
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

		if (point.x < docWndRect.left) {
			otherNoteForm->GetHorizontalScroll()->ScrollPrevious(docWndRect.left - point.x + 50);
		}

		if (point.y  + 50 < docWndRect.top) {
			otherNoteForm->GetVerticalScroll()->ScrollPrevious(docWndRect.top - point.y + 50);
		}
		////////////////////////////////////////////////////////////////////////////////////////////
	}
}