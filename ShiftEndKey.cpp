//ShiftEndKey.cpp

#include "ShiftEndKey.h"
#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "SelectedBuffer.h"

ShiftEndKey::ShiftEndKey(Form *form)
	:KeyAction(form) {
}

ShiftEndKey::ShiftEndKey(const ShiftEndKey& source)
	: KeyAction(source) {
}

ShiftEndKey::~ShiftEndKey() {

}

ShiftEndKey& ShiftEndKey::operator=(const ShiftEndKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "OtherNoteForm.h"
#include "PageForm.h"
#include "HorizontalScroll.h"
#include "VerticalScroll.h"
void ShiftEndKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	MemoForm *memoForm = static_cast<MemoForm*>(this->form);
	Memo *memo = static_cast<Memo*>(memoForm->GetContents());
	Line *line = memo->GetLine(memo->GetRow());
	Caret *caret = static_cast<MemoForm*>(this->form)->GetCaret();

	//1. store a caret of starting position
	if (memoForm->GetSelectedBuffer()->GetIsSelecting() == false) {
		memoForm->GetSelectedBuffer()->SetInitialPosition(memo->GetRow(), line->GetColumn());
	}

	//2. same caret logic
	if (memo->GetRow() < memo->GetLength() - 1 || line->GetColumn() < line->GetLength()) {
		//caret->MoveLastCharacter();
		line->MoveLastColumn();
	}
	caret->UpdateCaret();
	//3. copy to buffer for selectedbuffer
	memoForm->GetSelectedBuffer()->CopyToBuffer(memo->GetRow(), line->GetColumn());

	//4. fixed shift button clicked a caret of the starting position
	memoForm->GetSelectedBuffer()->SetIsSelecting(true);

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
	/*else if (point.x < docWndRect.left) {
		otherNoteForm->GetHorizontalScroll()->ScrollPrevious(docWndRect.left - point.x + 50);
	}*/

	/*if (point.y + 50 > docWndRect.bottom) {
		otherNoteForm->GetVerticalScroll()->ScrollNext(point.y + 50 - docWndRect.bottom);
	}*/
	////////////////////////////////////////////////////////////////////////////////////////////

	dynamic_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
}