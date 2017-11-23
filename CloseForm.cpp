//CloseForm.cpp

#include "CloseForm.h"

CloseForm::CloseForm(Form *form)
	:FindingFormAction(form) {

}

CloseForm::CloseForm(const CloseForm& source)
	: FindingFormAction(source) {

}

CloseForm::~CloseForm() {

}

CloseForm& CloseForm::operator=(const CloseForm& source) {
	FindingFormAction::operator=(source);

	return *this;
}

//#include "FindingForm.h"
//#include "OtherNoteForm.h"
//#include "PageForm.h"
//#include "MemoForm.h"
//#include "Note.h"
//#include "Memo.h"
//#include "Line.h"
//#include "SelectedBuffer.h"
//void CloseForm::OnFindingFormButtonClicked(WPARAM wParam, LPARAM lParam) {
//	OtherNoteForm *otherNoteForm = static_cast<OtherNoteForm*>(this->form);
//	FindingForm *findingForm = otherNoteForm->GetFindingForm();
//
//	//�����ϱ� ���� ���� ���� ã�� ������ memoForm�� fucous�� �ֱ� ���ؼ� 
//	FindIndex findIndex = findingForm->GetIndexes().GetAt(findingForm->GetCurrent());
//	PageForm *pageForm = otherNoteForm->GetPageForm(findIndex.GetPageIndex());
//	MemoForm *memoForm = pageForm->GetMemoForm(findIndex.GetMemoIndex());
//	memoForm->SetFocus();
//
//	//0924 : ĳ���� �ռ��� �����ϱ� �߰��ϱ�
//	Memo *memo = static_cast<Memo*>(memoForm->GetContents());
//	Line *line = memo->GetLine(memo->GetRow());
//	if (memoForm->GetSelectedBuffer()->GetIsSelecting() == false) {
//		memoForm->GetSelectedBuffer()->SetInitialPosition(memo->GetRow(), line->GetColumn() - findingForm->GetKey().GetLength());
//	}
//	memoForm->GetSelectedBuffer()->CopyToBuffer(memo->GetRow(), line->GetColumn());
//	memoForm->GetSelectedBuffer()->SetIsSelecting(true);
//	memoForm->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
//
//	findingForm->EraseFindIndexes();
//	if (findingForm->GetLength() > 0) {
//		otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent())->OnEraseFindIndexes();
//	}
//	otherNoteForm->SetFindingForm(NULL);
//	otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent())->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
//
//	otherNoteForm->GetTabCtrl()->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
//}


#include "FindingForm.h"
#include "OtherNoteForm.h"
#include "PageForm.h"
#include "MemoForm.h"
#include "Note.h"
#include "Page.h"
#include "Memo.h"
#include "Line.h"
#include "SelectedBuffer.h"
void CloseForm::OnFindingFormButtonClicked(WPARAM wParam, LPARAM lParam) {
	OtherNoteForm *otherNoteForm = static_cast<OtherNoteForm*>(this->form);
	FindingForm *findingForm = otherNoteForm->GetFindingForm();

	if (findingForm->GetLength() > 0) {
		//�����ϱ� ���� ���� ���� ã�� ������ memoForm�� fucous�� �ֱ� ���ؼ� 
		FindIndex findIndex = findingForm->GetIndexes().GetAt(findingForm->GetCurrent());
		PageForm *pageForm = otherNoteForm->GetPageForm(findIndex.GetPageIndex());
		//MemoForm *memoForm = pageForm->GetMemoForm(findIndex.GetMemoIndex());
		MemoForm *memoForm = findIndex.GetMemoIndex();
		memoForm->SetFocus();

		//0924 : ĳ���� �ռ��� �����ϱ� �߰��ϱ�
		Memo *memo = static_cast<Memo*>(memoForm->GetContents());
		Line *line = memo->GetLine(memo->GetRow());
		if (memoForm->GetSelectedBuffer()->GetIsSelecting() == false) {
			memoForm->GetSelectedBuffer()->SetInitialPosition(memo->GetRow(), line->GetColumn() - findingForm->GetKeyLength());
		}
		memoForm->GetSelectedBuffer()->CopyToBuffer(memo->GetRow(), line->GetColumn());
		memoForm->GetSelectedBuffer()->SetIsSelecting(true);
		memoForm->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

		findingForm->EraseFindIndexes();
		if (findingForm->GetLength() > 0) {
			otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent())->OnEraseFindIndexes();
		}

		//otherNoteForm->SetFindingForm(NULL);//1104
		otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent())->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

		otherNoteForm->GetTabCtrl()->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	}
	else {
		PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
		Page *page = static_cast<Page*>(pageForm->GetContents());
		if (page->GetCurrent() >= 0 && page->GetLength() > 0) {//�޸� ���� ��� ã������ �� ��
			MemoForm *memoForm = pageForm->GetMemoForm(static_cast<Page*>(pageForm->GetContents())->GetCurrent());
			memoForm->SetFocus();
		}
	}

	//findingForm�� ���� ������ �ʿ��ϴ� 11/12
	if (findingForm != 0) {
		//
		//delete findingForm;
		findingForm->CloseWindow();
		otherNoteForm->SetFindingForm(NULL);
	}
}