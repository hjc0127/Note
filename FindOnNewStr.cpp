//FindOnNewStr.cpp

#include "FindOnNewStr.h"

FindOnNewStr::FindOnNewStr(Form *form)
	:FindingFormAction(form) {

}

FindOnNewStr::FindOnNewStr(const FindOnNewStr& source)
	: FindingFormAction(source) {

}

FindOnNewStr::~FindOnNewStr() {

}

FindOnNewStr& FindOnNewStr::operator=(const FindOnNewStr& source) {
	FindingFormAction::operator=(source);

	return *this;
}

#include "HorizontalScroll.h"
#include "VerticalScroll.h"
#include "FindingForm.h"
#include "OtherNoteForm.h"
#include "PageForm.h"
#include "MemoForm.h"
#include "Note.h"
#include "Page.h"
#include "Memo.h"
#include "Line.h"
#include "EraseFindIndexVisitor.h"
#include "Caret.h"
#include "SelectedBuffer.h"
void FindOnNewStr::OnFindingFormButtonClicked(WPARAM wParam, LPARAM lParam) {
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	FindingForm *findingForm = otherNoteForm->GetFindingForm();
	FINDREPLACE *findReplace = (FINDREPLACE*)(lParam);
	
	if (findingForm->GetKey() != CString(findReplace->lpstrFindWhat)) {
		//문자들에게 하이라이트 표시를 해제한다.
		findingForm->EraseFindIndexes();
		if (findingForm->GetLength() > 0) {
			//기존에 찾은 findIndex들을 삭제한다.
			Long i = 0;
			while (i <= findingForm->GetLength() - 1) {
				findingForm->RemoveFindIndex(i);
				//i++;
			}
			//기존tab에 색깔 원래 대로 칠하기
			findingForm->CancelFindingTabItem();
			//현제 페이지에 찾은 글자들을 해제한다
			otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent())->OnEraseFindIndexes();
		}
	}

	//해당 문자 색칠표시
	findingForm->Find(findReplace->lpstrFindWhat);

	//y기준으로 정렬, 예상이슈 : 정렬이 되면 가까운것부터 하는게 아니라 처음부터 할것이다.
	findingForm->SortFindIndexes();
	
	//현재 findIndex 기준으로 찾기 동작 진행
	if (findingForm->GetLength() > 0) {
		//캐럿기준으로 가장 가까운 inde 찾기
		Long current;
		if (findingForm->SearchDown() == TRUE) {
			current = findingForm->GetNextIndex();
		}
		else {
			current = findingForm->GetPreviousIndex();
		}

		if (current >= 0) {
			findingForm->SetCurrent(current);
			otherNoteForm->ScrollToFindIndex(&otherNoteForm->GetFindingForm()->GetIndexes().GetAt(otherNoteForm->GetFindingForm()->GetCurrent()));

			FindIndex findIndex = findingForm->GetAt(current);
			static_cast<Note*>(otherNoteForm->GetContents())->SetCurrent(findIndex.GetPageIndex());
			PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());

			//메모폼 주소로 메모 위치 찾기
			Long memoFormIndex = 0;
			MemoForm *tempMemoForm = findingForm->GetAt(current).GetMemoIndex();
			while (memoFormIndex < pageForm->GetLength()
				&& pageForm->GetMemoForm(memoFormIndex) != tempMemoForm) {
				memoFormIndex++;
			}
			static_cast<Page*>(pageForm->GetContents())->SetCurrent(memoFormIndex);

			MemoForm *memoForm = pageForm->GetMemoForm(static_cast<Page*>(pageForm->GetContents())->GetCurrent());
			Memo *memo = static_cast<Memo*>(memoForm->GetContents());
			memo->SetRow(findIndex.GetRow());
			Line *line = memo->GetLine(memo->GetRow());
			line->SetColumn(findIndex.GetColumn());
			Caret *caret = memoForm->GetCaret();
			
			pageForm->FocusMemo(memoForm);
			memoForm->SetFocus();

			//블록커서 씌우기
			//1. store a caret of starting position
			//if (memoForm->GetSelectedBuffer()->GetIsSelecting() == false) {
				memoForm->GetSelectedBuffer()->SetInitialPosition(memo->GetRow(), line->GetColumn());
			//}

			//2. same caret logic
			Long j = 0;
			while (j < findingForm->GetKeyLength()) {
				if (memo->GetRow() < memo->GetLength() - 1 || line->GetColumn() < line->GetLength()) {
					if (line->GetColumn() < line->GetLength()) {
						line->MoveNextColumn();
					}
					else if (line->GetColumn() == line->GetLength()) {
						memo->MoveNextRow();
						line = memo->GetLine(memo->GetRow());
						line->MoveFirstColumn();
					}
				}
				j++;
			}

			//3. copy to buffer for selectedbuffer
			memoForm->GetSelectedBuffer()->CopyToBuffer(memo->GetRow(), line->GetColumn());

			//4. fixed shift button clicked a caret of the starting position
			memoForm->GetSelectedBuffer()->SetIsSelecting(true);
			memoForm->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
			
			//1104 페이지내에 있는 찾은 것들에 대해서 그려준다.
			PageForm *pageFormToCheck = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
			Long k = 0;
			while (k < findingForm->GetLength()) {
				MemoForm *memoFormToCheck = findingForm->GetAt(k).GetMemoIndex();
				memoFormToCheck->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
				k++;
			}

			//5. check item finded
			findingForm->CheckFindingTabItem();

			//6. caret 제일 마지막에
			caret->UpdateCaret();
		}
	}
	else {
		//1103 tab 체크 해제해주는 코드 추가		
		otherNoteForm->GetTabCtrl()->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

		CString message = "'" + findingForm->GetKey() + "'를 찾을 수 없습니다.";
		otherNoteForm->MessageBox(message, "Error", NULL);
	}
}