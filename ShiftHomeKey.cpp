//ShiftHomeKey.cpp

#include "ShiftHomeKey.h"
#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "SelectedBuffer.h"

ShiftHomeKey::ShiftHomeKey(Form *form)
	:KeyAction(form) {
}

ShiftHomeKey::ShiftHomeKey(const ShiftHomeKey& source)
	: KeyAction(source) {
}

ShiftHomeKey::~ShiftHomeKey() {

}

ShiftHomeKey& ShiftHomeKey::operator=(const ShiftHomeKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "OtherNoteForm.h"
#include "PageForm.h"
#include "HorizontalScroll.h"
#include "VerticalScroll.h"
void ShiftHomeKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	MemoForm *memoForm = static_cast<MemoForm*>(this->form);
	Memo *memo = static_cast<Memo*>(memoForm->GetContents());
	Line *line = memo->GetLine(memo->GetRow());
	Caret *caret = static_cast<MemoForm*>(this->form)->GetCaret();

	//1. store a caret of starting position
	if (memoForm->GetSelectedBuffer()->GetIsSelecting() == false) {
		memoForm->GetSelectedBuffer()->SetInitialPosition(memo->GetRow(), line->GetColumn());
	}

	//2. same caret logic
	if (memo->GetRow() > 0 || line->GetColumn() > 0) {
		//caret->MoveFirstCharacter();
		line->MoveFirstColumn();
		//if (line->GetColumn() > 0) {
			//caret->MovePreviousCharacter();
			//line->MovePreviousColumn();
		//}
		/*else if (line->GetColumn() == 0) {
			caret->MovePreviousLine();

			memo->MovePreviousRow();
			line = memo->GetLine(memo->GetRow());

			line->MoveLastColumn();
			caret->MoveLastCharacter();
		}*/
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

	if (point.x < docWndRect.left) {
		otherNoteForm->GetHorizontalScroll()->ScrollPrevious(docWndRect.left - point.x + 50);
	}

	/*if (point.y + 50 < docWndRect.top) {
		otherNoteForm->GetVerticalScroll()->ScrollPrevious(docWndRect.top - point.y + 50);
	}*/
	////////////////////////////////////////////////////////////////////////////////////////////

	dynamic_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
}