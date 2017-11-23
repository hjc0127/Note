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
		//���ڵ鿡�� ���̶���Ʈ ǥ�ø� �����Ѵ�.
		findingForm->EraseFindIndexes();
		if (findingForm->GetLength() > 0) {
			//������ ã�� findIndex���� �����Ѵ�.
			Long i = 0;
			while (i <= findingForm->GetLength() - 1) {
				findingForm->RemoveFindIndex(i);
				//i++;
			}
			//����tab�� ���� ���� ��� ĥ�ϱ�
			findingForm->CancelFindingTabItem();
			//���� �������� ã�� ���ڵ��� �����Ѵ�
			otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent())->OnEraseFindIndexes();
		}
	}

	//�ش� ���� ��ĥǥ��
	findingForm->Find(findReplace->lpstrFindWhat);

	//y�������� ����, �����̽� : ������ �Ǹ� �����ͺ��� �ϴ°� �ƴ϶� ó������ �Ұ��̴�.
	findingForm->SortFindIndexes();
	
	//���� findIndex �������� ã�� ���� ����
	if (findingForm->GetLength() > 0) {
		//ĳ���������� ���� ����� inde ã��
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

			//�޸��� �ּҷ� �޸� ��ġ ã��
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

			//���Ŀ�� �����
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
			
			//1104 ���������� �ִ� ã�� �͵鿡 ���ؼ� �׷��ش�.
			PageForm *pageFormToCheck = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
			Long k = 0;
			while (k < findingForm->GetLength()) {
				MemoForm *memoFormToCheck = findingForm->GetAt(k).GetMemoIndex();
				memoFormToCheck->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
				k++;
			}

			//5. check item finded
			findingForm->CheckFindingTabItem();

			//6. caret ���� ��������
			caret->UpdateCaret();
		}
	}
	else {
		//1103 tab üũ �������ִ� �ڵ� �߰�		
		otherNoteForm->GetTabCtrl()->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

		CString message = "'" + findingForm->GetKey() + "'�� ã�� �� �����ϴ�.";
		otherNoteForm->MessageBox(message, "Error", NULL);
	}
}