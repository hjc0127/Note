//ShiftLeftArrowKey.cpp

#include "ShiftLeftArrowKey.h"
#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "SelectedBuffer.h"

ShiftLeftArrowKey::ShiftLeftArrowKey(Form *form)
	:KeyAction(form) {
}

ShiftLeftArrowKey::ShiftLeftArrowKey(const ShiftLeftArrowKey& source)
	: KeyAction(source) {
}

ShiftLeftArrowKey::~ShiftLeftArrowKey() {

}

ShiftLeftArrowKey& ShiftLeftArrowKey::operator=(const ShiftLeftArrowKey& source) {
	KeyAction::operator=(source);

	return *this;
}

void ShiftLeftArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
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
			//caret->MovePreviousCharacter();
			line->MovePreviousColumn();
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
	dynamic_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
}