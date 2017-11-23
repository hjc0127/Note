//ShiftDownArrowKey.cpp

#include "ShiftDownArrowKey.h"
#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "Character.h"
#include "SelectedBuffer.h"

ShiftDownArrowKey::ShiftDownArrowKey(Form *form)
	:KeyAction(form) {

}

ShiftDownArrowKey::ShiftDownArrowKey(const ShiftDownArrowKey& source)
	: KeyAction(source) {

}

ShiftDownArrowKey::~ShiftDownArrowKey() {

}

ShiftDownArrowKey& ShiftDownArrowKey::operator=(const ShiftDownArrowKey& source) {
	KeyAction::operator=(source);

	return *this;
}

void ShiftDownArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	MemoForm *memoForm = static_cast<MemoForm*>(this->form);
	Memo *memo = static_cast<Memo*>(memoForm->GetContents());
	Line *line = memo->GetLine(memo->GetRow());
	Caret *caret = static_cast<MemoForm*>(this->form)->GetCaret();

	//1. store a caret of starting position
	if (memoForm->GetSelectedBuffer()->GetIsSelecting() == false) {
		memoForm->GetSelectedBuffer()->SetInitialPosition(memo->GetRow(), line->GetColumn());
	}

	//2. same caret logic
	if (memo->GetRow() < memo->GetLength() - 1) {
		Long originalXPos = caret->GetXPosition();

		memo->MoveNextRow();
		line = memo->GetLine(memo->GetRow());
		line->MoveFirstColumn();

		//Long previousWidth = -1;
		Long previousXPos = static_cast<MemoForm*>(this->form)->GetMarginWidth();
		Long currentXPos = static_cast<MemoForm*>(this->form)->GetMarginWidth();
		while (currentXPos < originalXPos && line->GetColumn() < line->GetLength()) {
			previousXPos = currentXPos;
			currentXPos += line->GetCharacter(line->GetColumn())->GetWidth();
			line->MoveNextColumn();
		}

		if (currentXPos - originalXPos > originalXPos - previousXPos) {
			line->MovePreviousColumn();
		}

	}
	caret->UpdateCaret();
	//3. copy to buffer for selectedbuffer
	memoForm->GetSelectedBuffer()->CopyToBuffer(memo->GetRow(), line->GetColumn());

	//4. fixed shift button clicked a caret of the starting position
	memoForm->GetSelectedBuffer()->SetIsSelecting(true);

	dynamic_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
}