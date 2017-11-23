//ShiftRightArrowKey.cpp

#include "ShiftRightArrowKey.h"
#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "SelectedBuffer.h"

ShiftRightArrowKey::ShiftRightArrowKey(Form *form)
	:KeyAction(form) {

}

ShiftRightArrowKey::ShiftRightArrowKey(const ShiftRightArrowKey& source)
	: KeyAction(source) {

}

ShiftRightArrowKey::~ShiftRightArrowKey() {

}

ShiftRightArrowKey& ShiftRightArrowKey::operator=(const ShiftRightArrowKey& source) {
	KeyAction::operator=(source);

	return *this;
}

void ShiftRightArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
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
			line->MoveNextColumn();
			//caret->MoveNextCharacter();
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
	dynamic_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
}