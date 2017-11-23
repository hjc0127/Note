//FindUpward.cpp

#include "FindUpward.h"

FindUpward::FindUpward(Form *form)
	:FindingFormAction(form) {

}

FindUpward::FindUpward(const FindUpward& source)
	: FindingFormAction(source) {

}

FindUpward::~FindUpward() {

}

FindUpward& FindUpward::operator=(const FindUpward& source) {
	FindingFormAction::operator=(source);

	return *this;
}

#include "FindingForm.h"
#include "OtherNoteForm.h"
#include "PageForm.h"
#include "MemoForm.h"
#include "Note.h"
#include "Page.h"
#include "Memo.h"
#include "Line.h"
#include "SelectedBuffer.h"
#include "Caret.h"
void FindUpward::OnFindingFormButtonClicked(WPARAM wParam, LPARAM lParam) {
	OtherNoteForm *otherNoteForm = static_cast<OtherNoteForm*>(this->form);
	FindingForm *findingForm = otherNoteForm->GetFindingForm();
	Long current = findingForm->GetCurrent();
	FindIndex findIndex = findingForm->GetAt(current);
	PageForm *pageForm = otherNoteForm->GetPageForm((static_cast<Note*>(otherNoteForm->GetContents()))->GetCurrent());
	MemoForm *memoForm = pageForm->GetMemoForm((static_cast<Page*>(pageForm->GetContents()))->GetCurrent());
	//memoForm->GetSelectedBuffer()->SetIsSelecting(false);

	current--;
	/*if (current < 0 || findingForm->GetAt(current).GetPageIndex() != findIndex.GetPageIndex()) {
		while (current <findingForm->GetLength() && findingForm->GetAt(current + 1).GetPageIndex() <= findIndex.GetPageIndex()) {
			current++;
		}
	}*/
	if (current < 0) {
		current = findingForm->GetLength() - 1;
	}

	findingForm->SetCurrent(current);
	//
	otherNoteForm->ScrollToFindIndex(&otherNoteForm->GetFindingForm()->GetIndexes().GetAt(otherNoteForm->GetFindingForm()->GetCurrent()));
	
	findIndex = findingForm->GetAt(findingForm->GetCurrent());
	static_cast<Note*>(otherNoteForm->GetContents())->SetCurrent(findIndex.GetPageIndex());
	pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());

	//1027 zorder
	Long memoFormIndex = 0;
	//PageForm *tempPageForm = otherNoteForm->GetPageForm(pageIndex);
	MemoForm *tempMemoForm = findingForm->GetAt(findingForm->GetCurrent()).GetMemoIndex();
	while (memoFormIndex < pageForm->GetLength()
		&& pageForm->GetMemoForm(memoFormIndex) != tempMemoForm) {
		memoFormIndex++;
	}
	//

	//static_cast<Page*>(pageForm->GetContents())->SetCurrent(findIndex.GetMemoIndex());
	static_cast<Page*>(pageForm->GetContents())->SetCurrent(memoFormIndex);
	memoForm = pageForm->GetMemoForm(static_cast<Page*>(pageForm->GetContents())->GetCurrent());
	Memo *memo = static_cast<Memo*>(memoForm->GetContents());
	memo->SetRow(findIndex.GetRow());
	Line *line = memo->GetLine(memo->GetRow());
	line->SetColumn(findIndex.GetColumn());
	Caret *caret = memoForm->GetCaret();
	//1027
	pageForm->FocusMemo(memoForm);
	//
	memoForm->SetFocus();
	//블록커서 씌우기
	//1. store a caret of starting position
	//if (memoForm->GetSelectedBuffer()->GetIsSelecting() == false) {
		memoForm->GetSelectedBuffer()->SetInitialPosition(memo->GetRow(), line->GetColumn());
	//}

	//2. same caret logic
	Long j = 0;
	//while (j < findingForm->GetKey().GetLength()) {
	while (j < findingForm->GetKeyLength()) {
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
		j++;
	}
	//caret->UpdateCaret();

	//3. copy to buffer for selectedbuffer
	memoForm->GetSelectedBuffer()->CopyToBuffer(memo->GetRow(), line->GetColumn());

	//4. fixed shift button clicked a caret of the starting position
	//memoForm->GetSelectedBuffer()->SetIsSelecting(true);
	//otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent())->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

	//5. check item finded
	findingForm->CheckFindingTabItem();

	//6. caret을 제일 마지막에
	caret->UpdateCaret();

	Long previouseCurrent = current + 1;
	if (previouseCurrent >= findingForm->GetLength()) {
		previouseCurrent = 0;
	}

	findingForm->GetAt(previouseCurrent).GetMemoIndex()->GetSelectedBuffer()->SetIsSelecting(false);
	findingForm->GetAt(current).GetMemoIndex()->GetSelectedBuffer()->SetIsSelecting(true);

	memoForm->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
}