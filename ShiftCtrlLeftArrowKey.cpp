//ShiftCtrlLeftArrowKey.cpp

#include "ShiftCtrlLeftArrowKey.h"
#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "SelectedBuffer.h"

ShiftCtrlLeftArrowKey::ShiftCtrlLeftArrowKey(Form *form)
	:KeyAction(form) {
}

ShiftCtrlLeftArrowKey::ShiftCtrlLeftArrowKey(const ShiftCtrlLeftArrowKey& source)
	: KeyAction(source) {
}

ShiftCtrlLeftArrowKey::~ShiftCtrlLeftArrowKey() {

}

ShiftCtrlLeftArrowKey& ShiftCtrlLeftArrowKey::operator=(const ShiftCtrlLeftArrowKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "SingleCharacter.h"
#include "DoubleCharacter.h"
#include "OtherNoteForm.h"
#include "PageForm.h"
#include "HorizontalScroll.h"
void ShiftCtrlLeftArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
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
		if (line->GetColumn() > 0) {
			////caret->MovePreviousCharacter();
			//line->MovePreviousColumn();
			char previousCharacter = '\0';
			//caret->MovePreviousCharacter();
			line->MovePreviousColumn();
			Character *character = line->GetCharacter(line->GetColumn());
			char currentCharacter = '\0';
			if (dynamic_cast<SingleCharacter*>(character)) {
				currentCharacter = dynamic_cast<SingleCharacter*>(character)->GetValue();
			}
			else if (dynamic_cast<DoubleCharacter*>(character)) {
				currentCharacter = 'a';
			}

			//			while ((previousCharacter < 97 || previousCharacter > 122) || currentCharacter != ' ') {
			while ((previousCharacter < 33 || previousCharacter > 126 || currentCharacter != ' ') && line->GetColumn() > 0) {
				//caret->MovePreviousCharacter();
				line->MovePreviousColumn();
				character = line->GetCharacter(line->GetColumn());
				previousCharacter = currentCharacter;
				if (dynamic_cast<SingleCharacter*>(character)) {
					currentCharacter = dynamic_cast<SingleCharacter*>(character)->GetValue();
				}
				else if (dynamic_cast<DoubleCharacter*>(character)) {
					currentCharacter = 'a';
				}
			}
			if (line->GetColumn() > 0) {
				line->MoveNextColumn();
				//caret->MoveNextCharacter();
			}
		}
		else if (line->GetColumn() == 0) {
			//caret->MovePreviousLine();

			memo->MovePreviousRow();
			line = memo->GetLine(memo->GetRow());

			line->MoveLastColumn();
			//caret->MoveLastCharacter();
		}
	}
	caret->UpdateCaret();

	//3. copy to buffer for selectedbuffer
	memoForm->GetSelectedBuffer()->CopyToBuffer(memo->GetRow(), line->GetColumn());

	//4. fixed shift button clicked a caret of the starting position
	memoForm->GetSelectedBuffer()->SetIsSelecting(true);

	//5. scroll first column in row
	//////////////////////////////////////////////////////
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	CRect docWndRect;
	otherNoteForm->GetDocumentWnd()->GetWindowRect(&docWndRect);
	static_cast<PageForm*>(static_cast<MemoForm*>(this->form)->GetParent())->UpdateSize(static_cast<MemoForm*>(this->form));

	//페이지 이동
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
	//////////////////////////////////////////////////////

	dynamic_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
}