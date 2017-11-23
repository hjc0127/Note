//CharacterKey.cpp

#include "CharacterKey.h"
#include "SelectedBuffer.h"
#include "MemoForm.h"
#include "DeleteKey.h"
#include "Line.h"
#include "Contents.h"
#include "Caret.h"
#include "Memo.h"
#include "OtherNoteForm.h"
#include "PageForm.h"
#include "HorizontalScroll.h"
#include "VerticalScroll.h"

CharacterKey::CharacterKey(Form *form)
	:KeyAction(form) {

}

CharacterKey::CharacterKey(const CharacterKey& source)
	: KeyAction(source) {

}

CharacterKey::~CharacterKey() {

}

CharacterKey& CharacterKey::operator=(const CharacterKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "CharacterFaces.h"
#include "Character.h"
#include "SingleCharacter.h"
#include "DoubleCharacter.h"
void CharacterKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (static_cast<MemoForm*>(this->form)->GetSelectedBuffer()->GetIsSelecting() == true) {
		static_cast<MemoForm*>(this->form)->SetFocusType(MEMOFORM_FOCUS_CLIENT);
		DeleteKey deleteKey = DeleteKey(static_cast<MemoForm*>(this->form));
		deleteKey.OnKeyDown(nChar, nRepCnt, nFlags);
		static_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);
	}

	Memo *tempMemo = static_cast<Memo*>(static_cast<MemoForm*>(this->form)->GetContents());		
	Line *line = static_cast<Memo*>(static_cast<MemoForm*>(this->form)->GetContents())->GetLine(tempMemo->GetRow());
	Memo *copyMemo = static_cast<Memo*>(tempMemo->Clone());
	line->Write(nChar);
	static_cast<MemoForm*>(this->form)->AutoReturn();
	
	Long heightOfMemoForm = MEMOFORM_MARGIN_BOTTOM + MEMOFORM_MARGIN_TOP + MEMOFORM_CAPTION_HEIGHT;
	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	Long characterHeight = characterFaces->GetCharacterSize(97).GetHeight();
	Long j = 0;
	while (j < tempMemo->GetLength()) {
		heightOfMemoForm += characterHeight;
		j++;
	}

	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	CRect memoFormWndRect;
	static_cast<MemoForm*>(this->form)->GetWindowRect(&memoFormWndRect);
	CRect pageFormWndRect;
	static_cast<PageForm*>(static_cast<MemoForm*>(this->form)->GetParent())->GetWindowRect(&pageFormWndRect);
	if (memoFormWndRect.top + heightOfMemoForm >= pageFormWndRect.top + PAGEFORM_MAX_HEIGHT) {
		delete static_cast<MemoForm*>(this->form)->GetContents();
		static_cast<MemoForm*>(this->form)->SetContents(copyMemo);
	}
	else {
		if (copyMemo != 0) {
			delete copyMemo;
		}
		//캐럿의 위치를 갱신한다.
		static_cast<MemoForm*>(this->form)->GetCaret()->UpdateCaret();
		//영역해제
		static_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);
		//메모폼의 사이즈를 갱신한다.
		static_cast<MemoForm*>(this->form)->ReSizeWindow();
		//페이지폼 사이즈 갱신
		static_cast<PageForm*>(static_cast<MemoForm*>(this->form)->GetParent())->UpdateSize(static_cast<MemoForm*>(this->form));
		//스크롤 기능
		CPoint point;
		point.x = static_cast<MemoForm*>(this->form)->GetCaret()->GetXPosition();
		point.y = static_cast<MemoForm*>(this->form)->GetCaret()->GetYPosition();
		static_cast<MemoForm*>(this->form)->ClientToScreen(&point);
		CRect docWndRect;
		otherNoteForm->GetDocumentWnd()->GetWindowRect(&docWndRect);
		if (point.x + 50 > docWndRect.right) {
			otherNoteForm->GetHorizontalScroll()->ScrollNext(50);
		}
		else if (point.x < docWndRect.left) {
			otherNoteForm->GetHorizontalScroll()->ScrollPrevious(docWndRect.left - point.x + 50);
		}
	}

	/////////// 페이지 스크롤이 많이 될수록 처리속도가 느려진다 //////////////
	static_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
}