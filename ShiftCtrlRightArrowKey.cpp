//ShiftCtrlRightArrowKey.cpp

#include "ShiftCtrlRightArrowKey.h"
#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "SelectedBuffer.h"

ShiftCtrlRightArrowKey::ShiftCtrlRightArrowKey(Form *form)
	:KeyAction(form) {

}

ShiftCtrlRightArrowKey::ShiftCtrlRightArrowKey(const ShiftCtrlRightArrowKey& source)
	: KeyAction(source) {

}

ShiftCtrlRightArrowKey::~ShiftCtrlRightArrowKey() {

}

ShiftCtrlRightArrowKey& ShiftCtrlRightArrowKey::operator=(const ShiftCtrlRightArrowKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "SingleCharacter.h"
#include "DoubleCharacter.h"
#include "OtherNoteForm.h"
#include "PageForm.h"
#include "HorizontalScroll.h"
void ShiftCtrlRightArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
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
		if (line->GetColumn() < line->GetLength()) {
			//line->MoveNextColumn();
			//caret->MoveNextCharacter();
			char previousCharacter = '\0';
			line->MoveNextColumn();
			//caret->MoveNextCharacter();
			Character *character = line->GetCharacter(line->GetColumn());
			char currentCharacter = '\0';
			if (dynamic_cast<SingleCharacter*>(character)) {
				currentCharacter = dynamic_cast<SingleCharacter*>(character)->GetValue();
			}
			else if (dynamic_cast<DoubleCharacter*>(character)) {
				currentCharacter = 'a';
			}

			//while (currentCharacter < 33 || currentCharacter > 126 || previousCharacter != ' ') {
			while ((currentCharacter < 33 || currentCharacter > 126 || previousCharacter != ' ') && line->GetColumn() < line->GetLength() - 1) {
				line->MoveNextColumn();
				//caret->MoveNextCharacter();
				character = line->GetCharacter(line->GetColumn());
				previousCharacter = currentCharacter;
				if (dynamic_cast<SingleCharacter*>(character)) {
					currentCharacter = dynamic_cast<SingleCharacter*>(character)->GetValue();
				}
				else if (dynamic_cast<DoubleCharacter*>(character)) {
					currentCharacter = 'a';
				}
			}
			if (line->GetColumn() == line->GetLength() - 1) {
				line->MoveNextColumn();
				//caret->MoveNextCharacter();
			}
		}
		else if (line->GetColumn() == line->GetLength()) {
			memo->MoveNextRow();
			line = memo->GetLine(memo->GetRow());
			line->MoveFirstColumn();
			//caret->MoveNextLine();
		}
	}
	caret->UpdateCaret();

	//3. copy to buffer for selectedbuffer
	memoForm->GetSelectedBuffer()->CopyToBuffer(memo->GetRow(), line->GetColumn());

	//4. fixed shift button clicked a caret of the starting position
	memoForm->GetSelectedBuffer()->SetIsSelecting(true);

	//5. scroll last column in row
	///////////////////////////////////////////////////////////
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
	///////////////////////////////////////////////////////////
	dynamic_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
}