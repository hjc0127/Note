//CtrlVKey.cpp

#include "CtrlVKey.h"
#include "MemoForm.h"

CtrlVKey::CtrlVKey(Form *form)
	:KeyAction(form) {

}

CtrlVKey::CtrlVKey(const CtrlVKey& source)
	: KeyAction(source) {

}

CtrlVKey::~CtrlVKey() {

}

CtrlVKey& CtrlVKey::operator=(const CtrlVKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "SelectedBuffer.h"
#include "OtherNoteForm.h"
#include "PageForm.h"
#include "HorizontalScroll.h"
#include "VerticalScroll.h"
void CtrlVKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	//SelectedBuffer *selectedBuffer = this->otherNoteForm->selectedBuffer;
	//if (selectedBuffer->GetIsCopy()) {
	//	selectedBuffer->Paste();
	//}
	static_cast<MemoForm*>(this->form)->GetSelectedBuffer()->PasteToMemoForm();
	static_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);

	//함수로 빼든지....
	static_cast<MemoForm*>(this->form)->ReSizeWindow();
	static_cast<PageForm*>(static_cast<MemoForm*>(this->form)->GetParent())->UpdateSize(static_cast<MemoForm*>(this->form));
	MemoForm *memoForm = static_cast<MemoForm*>(this->form);
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	CRect docWndRect;
	otherNoteForm->GetDocumentWnd()->GetWindowRect(&docWndRect);
	CRect memoFormRect;
	memoForm->GetWindowRect(&memoFormRect);
	CRect pageFormWndRect;
	memoForm->GetParent()->GetWindowRect(&pageFormWndRect);

	////////////////////////////////////////////////////////////////
	CPoint point;
	point.x = static_cast<Caret*>(memoForm->GetCaret())->GetXPosition();
	point.y = static_cast<Caret*>(memoForm->GetCaret())->GetYPosition();
	memoForm->ClientToScreen(&point);
	CPoint tempPoint = point;
	static_cast<PageForm*>(memoForm->GetParent())->ScreenToClient(&point);
	////////////////////////////////////////////////////////////////

	//if (memoFormRect.right > docWndRect.right) {
	if (tempPoint.x > docWndRect.right || tempPoint.x < docWndRect.left) {
		if (pageFormWndRect.right + 2 == docWndRect.right) {
			static_cast<PageForm*>(memoForm->GetParent())->ResizeWindow(memoFormRect.right - docWndRect.right + 150, 0);
			otherNoteForm->GetHorizontalScroll()->UpdateScrinfo(static_cast<PageForm*>(memoForm->GetParent())->GetHScrinfo());
		}
		//otherNoteForm->GetHorizontalScroll()->ScrollNext(memoFormRect.right - docWndRect.right + 150);
		otherNoteForm->GetHorizontalScroll()->ScrollToPosition(point.x - 50);
	}

	//if (memoFormRect.bottom > docWndRect.bottom) {
	if (tempPoint.y > docWndRect.bottom || tempPoint.y < docWndRect.top) {
		//1. 페이지폼 증가 상황
		if (pageFormWndRect.bottom + 2 == docWndRect.bottom) {
			static_cast<PageForm*>(memoForm->GetParent())->ResizeWindow(0, memoFormRect.bottom - docWndRect.bottom + 150);
			otherNoteForm->GetVerticalScroll()->UpdateScrinfo(static_cast<PageForm*>(memoForm->GetParent())->GetVScrinfo());
		}
		//2. 스크롤 아래쪽을 이동
		//otherNoteForm->GetVerticalScroll()->ScrollNext(memoFormRect.bottom - docWndRect.bottom + 150);
		otherNoteForm->GetVerticalScroll()->ScrollToPosition(point.y - 50);
	}

	memoForm->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	memoForm->RePosition();
}