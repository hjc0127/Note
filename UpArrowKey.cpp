//UpArrowKey.cpp

#include "UpArrowKey.h"

UpArrowKey::UpArrowKey(Form *form)
	:KeyAction(form) {

}

UpArrowKey::UpArrowKey(const UpArrowKey& source)
	: KeyAction(source) {

}

UpArrowKey::~UpArrowKey() {

}

UpArrowKey& UpArrowKey::operator=(const UpArrowKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "OtherNoteForm.h"
#include "VerticalScroll.h"
#include "PageForm.h"
#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "Character.h"
#include "SelectedBuffer.h"
void UpArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (dynamic_cast<MemoForm*>(this->form)) {
		Memo *memo = static_cast<Memo*>(this->form->GetContents());

		Caret *caret = dynamic_cast<MemoForm*>(this->form)->GetCaret();

		if (memo->GetRow() > 0) {
			Long originalXPos = caret->GetXPosition();

			//caret->MovePreviousLine();
			memo->MovePreviousRow();

			Line *line = memo->GetLine(memo->GetRow());
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

			caret->UpdateCaret();
		}
		dynamic_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);

		//0910
		//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow(NULL, "OtherNote"));
		OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
		CRect docWndRect;
		otherNoteForm->GetDocumentWnd()->GetWindowRect(&docWndRect);
		static_cast<PageForm*>(static_cast<MemoForm*>(this->form)->GetParent())->UpdateSize(static_cast<MemoForm*>(this->form));

		CPoint point;
		point.x = static_cast<MemoForm*>(this->form)->GetCaret()->GetXPosition();
		point.y = static_cast<MemoForm*>(this->form)->GetCaret()->GetYPosition();
		static_cast<MemoForm*>(this->form)->ClientToScreen(&point);

		if (point.y < docWndRect.top) {
			otherNoteForm->GetVerticalScroll()->ScrollPrevious(docWndRect.top - point.y + 50);
		}
		//

		dynamic_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	}
}