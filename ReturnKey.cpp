//ReturnKey.cpp

#include "ReturnKey.h"

ReturnKey::ReturnKey(Form *form)
	:KeyAction(form) {

}

ReturnKey::ReturnKey(const ReturnKey& source)
	: KeyAction(source) {

}

ReturnKey::~ReturnKey() {

}

ReturnKey& ReturnKey::operator=(const ReturnKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "Character.h"
#include "SelectedBuffer.h"
#include "OtherNoteForm.h"
#include "PageForm.h"
#include "HorizontalScroll.h"
#include "VerticalScroll.h"
#include "CharacterFaces.h"
void ReturnKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (dynamic_cast<MemoForm*>(this->form)) {
		Memo *memo = static_cast<Memo*>(this->form->GetContents());
		//11.12
		Long heightOfMemoForm = MEMOFORM_MARGIN_BOTTOM + MEMOFORM_MARGIN_TOP + MEMOFORM_CAPTION_HEIGHT;
		CharacterFaces *characterFaces = CharacterFaces::Instance(0);
		Long characterHeight = characterFaces->GetCharacterSize(97).GetHeight();
		Long j = 0;
		while (j < memo->GetLength()) {
			heightOfMemoForm += characterHeight;
			j++;
		}
		//
		OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
		CRect pageFormWndRect;
		static_cast<PageForm*>(static_cast<MemoForm*>(this->form)->GetParent())->GetWindowRect(&pageFormWndRect);
		CRect memoFormWndRect;
		static_cast<MemoForm*>(this->form)->GetWindowRect(&memoFormWndRect);
		//CharacterFaces *characterFaces = CharacterFaces::Instance(0);
		//Long characterHeight = characterFaces->GetCharacterSize(97).GetHeight();
		//if (memoFormWndRect.bottom + characterHeight <= pageFormWndRect.top + PAGEFORM_MAX_HEIGHT) {
		if (memoFormWndRect.top + heightOfMemoForm + characterHeight <= pageFormWndRect.top + PAGEFORM_MAX_HEIGHT) {
			Line *line = memo->GetLine(memo->GetRow());

			Caret *caret = dynamic_cast<MemoForm*>(this->form)->GetCaret();
			memo->InsertLine();
			Line *newLine = memo->GetLine(memo->GetRow());

			while (line->GetColumn() < line->GetLength()) {
				newLine->Add(line->GetCharacter(line->GetColumn())->Clone());
				newLine->MoveNextColumn();

				line->MoveNextColumn();
				line->Erase();
			}
			newLine->MoveFirstColumn();

			caret->UpdateCaret();
			static_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);
			static_cast<MemoForm*>(this->form)->ReSizeWindow();
			static_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

			//horizontal scroll 캐럿앞으로 이동
			//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CWnd::FindWindow(NULL, "OtherNote"));
			OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CWnd::FindWindow("OtherNote", NULL));
			CRect docRect;
			otherNoteForm->GetDocumentWnd()->GetWindowRect(&docRect);
		
			CPoint point;
			point.x = static_cast<MemoForm*>(this->form)->GetCaret()->GetXPosition();
			point.y = static_cast<MemoForm*>(this->form)->GetCaret()->GetYPosition();
			static_cast<MemoForm*>(this->form)->ClientToScreen(&point);

			if (point.x < docRect.left) {
				otherNoteForm->GetHorizontalScroll()->ScrollPrevious(docRect.left - point.x + 50);
			}

			static_cast<PageForm*>(static_cast<MemoForm*>(this->form)->GetParent())->UpdateSize(static_cast<MemoForm*>(this->form));
		}
	}
}