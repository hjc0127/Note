//BackspaceKey.cpp

#include "BackspaceKey.h"
#include "MemoForm.h"
#include "Memo.h"
#include "Line.h"
#include "Caret.h"
#include "Character.h"
#include "SelectedBuffer.h"

BackspaceKey::BackspaceKey(Form *form)
	:KeyAction(form) {
}

BackspaceKey::BackspaceKey(const BackspaceKey& source)
	:KeyAction(source) {
}

BackspaceKey::~BackspaceKey() {

}

#include "OtherNoteForm.h"
#include "PageForm.h"
#include "HorizontalScroll.h"
BackspaceKey& BackspaceKey::operator=(const BackspaceKey& source) {
	KeyAction::operator=(source);

	return *this;
}

void BackspaceKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (dynamic_cast<MemoForm*>(this->form)) {
		//1026
		static_cast<MemoForm*>(this->form)->GetCaret()->ChangeCaret();
		//
		Memo *memo = static_cast<Memo*>(this->form->GetContents());
		Line *line;

		Caret *caret = dynamic_cast<MemoForm*>(this->form)->GetCaret();

		MemoForm *memoForm = dynamic_cast<MemoForm*>(this->form);
		Long count = 0;
		if (memoForm->GetSelectedBuffer()->GetIsSelecting() == true) {
			SelectedBuffer *selectedBuffer = memoForm->GetSelectedBuffer();
			Memo *buffer = selectedBuffer->GetBuffer();
			Long i = 0;
			while (i < buffer->GetLength()) {
				line = buffer->GetLine(i);
				count += line->GetLength();
				count++;
				i++;
			}
			count--;

			memo->SetRow(selectedBuffer->GetEndRow());
			line = memo->GetLine(memo->GetRow());
			line->SetColumn(selectedBuffer->GetEndColumn());
		}
		else {
			count = 1;
		}

		Long j = 0;
		while (j < count) {
			line = memo->GetLine(memo->GetRow());
			if (line->GetLength() != 0 && line->GetColumn() != 0) {
				line->Erase();
			}
			else if (memo->GetRow() != 0) {
				if (line->GetLength() == 0) {
					memo->RemoveLine();
					memo->GetLine(memo->GetRow())->MoveLastColumn();
				}
				else {
					Line *lineToCopy = memo->GetLine(memo->MovePreviousRow());
					lineToCopy->MoveLastColumn();
					
					Long i = 0;
					while (i < line->GetLength()) {
						Contents *contents = line->GetCharacter(i)->Clone();
						lineToCopy->Add(contents);
						i++;
					}
					memo->MoveNextRow();
					memo->RemoveLine();
				}
			}
			j++;
		}
		
		if (memoForm->GetSelectedBuffer()->GetIsSelecting() == true) {
			Long xPos = 0;
			Long yPos = 0;
			memoForm->CalculatePosition(&xPos, &yPos);
			yPos += 20;
			caret->Move(xPos, yPos);
		}
		caret->UpdateCaret();
		
		dynamic_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);
		static_cast<MemoForm*>(this->form)->AutoReturn();
		dynamic_cast<MemoForm*>(this->form)->ReSizeWindow();
		//dynamic_cast<MemoForm*>(this->form)->RedrawWindow();

		//페이지 사이즈 변경
		//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow(NULL, "OtherNote"));
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
			//otherNoteForm->GetHorizontalScroll()->ScrollNext(50);
			otherNoteForm->GetHorizontalScroll()->ScrollNext(point.x + 50 - docWndRect.right);
		}else if (point.x < docWndRect.left) {
			otherNoteForm->GetHorizontalScroll()->ScrollPrevious(docWndRect.left - point.x + 50);
		}
		static_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
		static_cast<MemoForm*>(this->form)->RePosition();
	}
}