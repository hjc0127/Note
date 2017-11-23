//MouseOnMove.cpp

#include "MouseOnMove.h"
#include "Form.h"
#include "MemoForm.h"

MouseOnMove::MouseOnMove(Form *form)
	:MouseAction(static_cast<MemoForm*>(form)) {
	//this->form = form;
}

MouseOnMove::MouseOnMove(const MouseOnMove& source)
	:MouseAction(source){
	//this->form = source.form;
}

MouseOnMove::~MouseOnMove() {

}

MouseOnMove& MouseOnMove::operator=(const MouseOnMove& source) {
	//this->form = source.form;
	MouseAction::operator=(source);

	return *this;
}

//#include "Page.h"
#include "Caret.h"
#include "SingleCharacter.h"
#include "DoubleCharacter.h"

#include "OtherNoteForm.h"
#include "Note.h"
#include "PageForm.h"
#include "Memo.h"
#include "Line.h"
#include "SelectedBuffer.h"
void MouseOnMove::OnMouseAction(UINT nFlags, CPoint point) {
	////OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow(NULL, "OtherNote"));
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	//Note *note = (Note*)(otherNoteForm->GetContents());
	//PageForm *pageForm = otherNoteForm->GetPageForm(note->GetCurrent());

	////1. point change to row and column
	//static_cast<MemoForm*>(this->form)->UpdateIndex(point);

	////2. copy to buffer for selectedbuffer
	//Memo *memo = static_cast<Memo*>(static_cast<MemoForm*>(this->form)->GetContents());
	//Line *line = memo->GetLine(memo->GetRow());
	//static_cast<MemoForm*>(this->form)->GetSelectedBuffer()->CopyToBuffer(memo->GetRow(), line->GetColumn());

	////3. fixed shift button clicked a caret of the starting position
	//static_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(true);
	//static_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);





	//1027 드래그 해서 선택/////////////////////////////////////////////////////////////////////////////////
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	//Note *note = (Note*)(otherNoteForm->GetContents());
	//PageForm *pageForm = otherNoteForm->GetPageForm(note->GetCurrent());

	//CPoint changedPoint = point;
	//static_cast<MemoForm*>(this->form)->ClientToScreen(&changedPoint);
	//Long i = pageForm->GetLength() - 1;
	//CRect memoFormRect;
	//MemoForm *memoForm = NULL;
	//while (i >= 0 && memoForm == NULL) {
	//	pageForm->GetMemoForm(i)->GetWindowRect(&memoFormRect);
	//	if (memoFormRect.left <= changedPoint.x && memoFormRect.right >= changedPoint.x && memoFormRect.top <= changedPoint.y && memoFormRect.bottom >= changedPoint.y) {
	//		memoForm = pageForm->GetMemoForm(i);
	//	}
	//	i--;
	//}

	//if (this->form != memoForm) {
	//	memoForm->ScreenToClient(&changedPoint);

	//	//1. point change to row and column
	//	memoForm->UpdateIndex(changedPoint);

	//	//2. copy to buffer for selectedbuffer
	//	Memo *memo = static_cast<Memo*>(memoForm->GetContents());
	//	Line *line = memo->GetLine(memo->GetRow());
	//	memoForm->GetSelectedBuffer()->CopyToBuffer(memo->GetRow(), line->GetColumn());

	//	//3. fixed shift button clicked a caret of the starting position
	//	memoForm->GetSelectedBuffer()->SetIsSelecting(true);
	//	memoForm->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_NOERASE);
	//}
	//else {
	//	////1. point change to row and column
		static_cast<MemoForm*>(this->form)->UpdateIndex(point);

		//2. copy to buffer for selectedbuffer
		Memo *memo = static_cast<Memo*>(static_cast<MemoForm*>(this->form)->GetContents());
		Line *line = memo->GetLine(memo->GetRow());
		static_cast<MemoForm*>(this->form)->GetSelectedBuffer()->CopyToBuffer(memo->GetRow(), line->GetColumn());

		//3. fixed shift button clicked a caret of the starting position
		static_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(true);
		static_cast<MemoForm*>(this->form)->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_NOERASE);
	//}
	///////////////////////////////////////////////////////////////////////////////////////////////////////
}


void MouseOnMove::OnMouseAction(int x, int y) {

}

void MouseOnMove::OnMouseAction(UINT nSide, LPRECT lpRect) {

}