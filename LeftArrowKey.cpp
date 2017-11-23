//LeftArrowKey.cpp

#include "LeftArrowKey.h"

LeftArrowKey::LeftArrowKey(Form *form)
	:KeyAction(form) {

}

LeftArrowKey::LeftArrowKey(const LeftArrowKey& source)
	: KeyAction(source) {

}

LeftArrowKey::~LeftArrowKey() {

}

LeftArrowKey& LeftArrowKey::operator=(const LeftArrowKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "OtherNoteForm.h"
#include "HorizontalScroll.h"
#include "PageForm.h"
#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "SelectedBuffer.h"
void LeftArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	
	if (dynamic_cast<MemoForm*>(this->form)) {
		Memo *memo = static_cast<Memo*>(this->form->GetContents());
		Line *line = memo->GetLine(memo->GetRow());

		Caret *caret = dynamic_cast<MemoForm*>(this->form)->GetCaret();
	
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
		
		//1027일 선택영역/////////////////////////////////////////////////////////////////////////////
		if (static_cast<MemoForm*>(this->form)->GetSelectedBuffer()->GetIsSelecting() == TRUE) {
			//beginRow, beginColumn으로 설정
			MemoForm *memoForm = static_cast<MemoForm*>(this->form);			
			Memo *memo = static_cast<Memo*>(memoForm->GetContents());
			memo->SetRow(memoForm->GetSelectedBuffer()->GetBeginRow());
			Line *line = memo->GetLine(memoForm->GetSelectedBuffer()->GetBeginRow());
			line->SetColumn(memoForm->GetSelectedBuffer()->GetBeginColumn());			
			caret->UpdateCaret();
		}
		caret->ShowCaret();
		//////////////////////////////////////////////////////////////////////////////////////////////

		dynamic_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);

		//0910 왼쪽으로 이동
		//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow(NULL, "OtherNote"));
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

		dynamic_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	}
}