//DeleteKey.cpp

#include "DeleteKey.h"
//#include "OtherNoteForm.h"

DeleteKey::DeleteKey(Form *form) 
	:KeyAction(form){
}

DeleteKey::DeleteKey(const DeleteKey& source) 
	:KeyAction(source){
}

DeleteKey::~DeleteKey() {

}

DeleteKey& DeleteKey::operator=(const DeleteKey& source) {
	KeyAction::operator=(source);
	return *this;
}

#include "Page.h"
#include "Note.h"
#include "MemoForm.h"
#include "Memo.h"
#include "Line.h"
#include "Caret.h"
#include "Character.h"
#include "SelectedBuffer.h"
#include "OtherNoteForm.h"
#include "PageForm.h"
#include "HorizontalScroll.h"
void DeleteKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (dynamic_cast<MemoForm*>(this->form)) {
		if (static_cast<MemoForm*>(this->form)->GetFocusType() == MEMOFORM_FOCUS_CLIENT) {
			/*if (dynamic_cast<MemoForm*>(this->form)->GetIsCaption()) {
				dynamic_cast<MemoForm*>(this->form)->OnClose();
			}
			else {*/
			//{
			Memo *memo = static_cast<Memo*>(this->form->GetContents());
			//			Line *line = memo->GetLine(memo->GetRow());
			Line *line;

			Caret *caret = dynamic_cast<MemoForm*>(this->form)->GetCaret();

			//
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

				Long xPos = 0;
				Long yPos = 0;
				memoForm->CalculatePosition(&xPos, &yPos);
				yPos += 20;
				//caret->UpdateCaret(xPos, yPos);
				memo->SetRow(selectedBuffer->GetBeginRow());
				line = memo->GetLine(memo->GetRow());
				line->SetColumn(selectedBuffer->GetBeginColumn());
			}
			else {
				count = 1;
			}
			//
			Long j = 0;
			line = memo->GetLine(memo->GetRow());
			while (j < count) {

				if (line->GetLength() > 0 && line->GetColumn() < line->GetLength()) {//remove character
					line->MoveNextColumn();
					line->Erase();
					//dynamic_cast<MemoForm*>(this->form)->ReSizeWindow();
				}
				else if (memo->GetRow() + 1 < memo->GetLength()) {//remove line
					if (line->GetLength() == 0) {
						memo->RemoveLine();
						memo->MoveNextRow();
						line = memo->GetLine(memo->GetRow());
						line->MoveFirstColumn();
					}
					else {
						Line *lineToCopy = memo->GetLine(memo->GetRow() + 1);

						Long i = 0;
						while (i < lineToCopy->GetLength()) {
							Contents *contents = lineToCopy->GetCharacter(i)->Clone();
							line->Add(contents);
							i++;
						}
						memo->MoveNextRow();
						memo->RemoveLine();
					}
				}
				j++;
			}
			caret->UpdateCaret();
			dynamic_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);
			static_cast<MemoForm*>(this->form)->AutoReturn();
			dynamic_cast<MemoForm*>(this->form)->ReSizeWindow();
			//dynamic_cast<MemoForm*>(this->form)->RedrawWindow();
			//}

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
			}
			/*else if (point.x < docWndRect.left) {
				otherNoteForm->GetHorizontalScroll()->ScrollPrevious(docWndRect.left - point.x + 50);
			}*/

			static_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
			static_cast<MemoForm*>(this->form)->RePosition();
		}
		else if (static_cast<MemoForm*>(this->form)->GetFocusType() == MEMOFORM_FOCUS_CAPTION) {
			static_cast<MemoForm*>(this->form)->OnClose();

			//1119
			OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
			PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
			static_cast<Page*>(pageForm->GetContents())->SetCurrent(-1);
		}
	}
}