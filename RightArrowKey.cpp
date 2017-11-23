//RightArrowKey.cpp

#include "RightArrowKey.h"

RightArrowKey::RightArrowKey(Form *form)
	:KeyAction(form) {

}

RightArrowKey::RightArrowKey(const RightArrowKey& source)
	: KeyAction(source) {

}

RightArrowKey::~RightArrowKey() {

}

RightArrowKey& RightArrowKey::operator=(const RightArrowKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "OtherNoteForm.h"
#include "PageForm.h"
#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "SelectedBuffer.h"
#include "HorizontalScroll.h"
void RightArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (dynamic_cast<MemoForm*>(this->form)) {
		Memo *memo = static_cast<Memo*>(this->form->GetContents());
		Line *line = memo->GetLine(memo->GetRow());

		Caret *caret = dynamic_cast<MemoForm*>(this->form)->GetCaret();

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
		
		//1027일 선택영역/////////////////////////////////////////////////////////////////////////////
		if (static_cast<MemoForm*>(this->form)->GetSelectedBuffer()->GetIsSelecting() == TRUE) {
			//beginRow, beginColumn으로 설정
			MemoForm *memoForm = static_cast<MemoForm*>(this->form);
			Memo *memo = static_cast<Memo*>(memoForm->GetContents());
			memo->SetRow(memoForm->GetSelectedBuffer()->GetEndRow());
			Line *line = memo->GetLine(memoForm->GetSelectedBuffer()->GetEndRow());
			line->SetColumn(memoForm->GetSelectedBuffer()->GetEndColumn());
			caret->UpdateCaret();
		}
		caret->ShowCaret();
		//////////////////////////////////////////////////////////////////////////////////////////////

		dynamic_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);

		//0910 추가
		//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow(NULL, "OtherNote"));
		OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
		CRect docWndRect;
		otherNoteForm->GetDocumentWnd()->GetWindowRect(&docWndRect);
		static_cast<PageForm*>(static_cast<MemoForm*>(this->form)->GetParent())->UpdateSize(static_cast<MemoForm*>(this->form));

		CPoint point;
		point.x = static_cast<MemoForm*>(this->form)->GetCaret()->GetXPosition();
		point.y = static_cast<MemoForm*>(this->form)->GetCaret()->GetYPosition();
		static_cast<MemoForm*>(this->form)->ClientToScreen(&point);
		
		//1. 오늘쪽 방향키를 누를때 스크롤하기
		if (point.x + 50 > docWndRect.right) {
			otherNoteForm->GetHorizontalScroll()->ScrollNext(50);
		}
		else if (point.x < docWndRect.left) { //다음칸으로 이동시 스크롤 앞으로 이동
			otherNoteForm->GetHorizontalScroll()->ScrollPrevious(docWndRect.left - point.x + 50);
		}
		//

		dynamic_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	}
}