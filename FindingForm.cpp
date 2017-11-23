//FindingForm.cpp

#include "FindingForm.h"
#include "FindVisitor.h"
#include "Contents.h"
#include "Note.h"
#include "Memo.h"
#include "OtherNoteForm.h"
#include "PageForm.h"
#include "MemoForm.h"
#include "Line.h"
#include "Character.h"

UINT FindingForm::WM_FIND = RegisterWindowMessage(FINDMSGSTRING);

BEGIN_MESSAGE_MAP(FindingForm, CFindReplaceDialog)
	ON_WM_CLOSE()
	//ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

FindingForm::FindingForm(Contents *contents) {
	this->contents = contents;
	//11/12
	this->key = "";
	this->indexes = NULL;
	this->capacity = 0;
	this->length = 0;
	this->current = 0;
	this->isEdited = true;
}

FindingForm::~FindingForm() {
	//1104
	//this->DestroyWindow();
}

FindingForm::FindingForm(const FindingForm& source) {

}

FindingForm& FindingForm::operator=(const FindingForm& source) {
	return *this;
}

void FindingForm::Create(OtherNoteForm *otherNoteForm) {
	CFindReplaceDialog::Create(TRUE, NULL, NULL, FR_DOWN | FR_HIDEMATCHCASE | FR_HIDEWHOLEWORD, otherNoteForm);
	//this->otherNoteForm = otherNoteForm;
}

//1104
#include "OtherNoteForm.h"
#include "MemoForm.h"
#include "SelectedBuffer.h"
void FindingForm::OnClose() {
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	if (this->GetLength() > 0) {
		FindIndex findIndex = this->GetIndexes().GetAt(this->GetCurrent());
		MemoForm *memoForm = findIndex.GetMemoIndex();
		Memo *memo = static_cast<Memo*>(memoForm->GetContents());
		Line *line = memo->GetLine(memo->GetRow());
		if (memoForm->GetSelectedBuffer()->GetIsSelecting() == false) {
			memoForm->GetSelectedBuffer()->SetInitialPosition(memo->GetRow(), line->GetColumn() - this->GetKeyLength());
		}
		memoForm->GetSelectedBuffer()->CopyToBuffer(memo->GetRow(), line->GetColumn());
		memoForm->GetSelectedBuffer()->SetIsSelecting(true);
	
		this->EraseFindIndexes();
		if (this->GetLength() > 0) {
			otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent())->OnEraseFindIndexes();
		}

		otherNoteForm->GetTabCtrl()->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
		memoForm->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	}
	else {
		Note *note = static_cast<Note*>(otherNoteForm->GetContents());
		PageForm *pageForm = otherNoteForm->GetPageForm(note->GetCurrent());
		if (pageForm->GetLength() > 0) {
			MemoForm *memoForm = pageForm->GetMemoForm(pageForm->GetLength() - 1);
			memoForm->SetFocus();
		}
	}

	//DestroyWindow();
	CFindReplaceDialog::OnClose();
}

//1104
void FindingForm::PostNcDestroy() {
	CFindReplaceDialog::PostNcDestroy();
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(FindWindow("OtherNote", NULL));
	otherNoteForm->SetFindingForm(NULL);
	//delete this;
}


void FindingForm::Find(CString key) {
	this->key = key;
	FindVisitor findVisitor((LPCTSTR)key);
	this->contents->Accept(&findVisitor);
	this->indexes = findVisitor.GetIndexes();
	this->length = findVisitor.GetLength();
	this->capacity = findVisitor.GetCapacity();
	this->current = 0;//1103
	this->CheckFindingTabItem();
}

FindIndex& FindingForm::GetAt(Long index) {
	return this->indexes.GetAt(index);
}

Long FindingForm::SetCurrent(Long current) {
	this->current = current;
	return this->current;
}

void FindingForm::EraseFindIndexes() {
	Long i = 0;
	while (i < this->length) {
		FindIndex findIndex= this->GetAt(i);
		OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CWnd::FindWindow("OtherNote", NULL));
		PageForm *pageForm = otherNoteForm->GetPageForm(findIndex.GetPageIndex());
		//MemoForm *memoForm = pageForm->GetMemoForm(findIndex.GetMemoIndex());
		MemoForm *memoForm = findIndex.GetMemoIndex();
		Line *line = static_cast<Memo*>(memoForm->GetContents())->GetLine(findIndex.GetRow());
		Long j = 0;
		while (j < this->GetKeyLength()) {
			Character *character = line->GetCharacter(findIndex.GetColumn()+j);
			character->SetIsFindIndexPainted(false);
			j++;
		}
		memoForm->RedrawWindow();//11/12
		i++;
	}
}

Long FindingForm::GetKeyLength() {
	Long length = this->key.GetLength();
	//1. key ��������
	
	//2. �ѱ����� �Ǵ�
	Long keyLength = 0;
	Long i = 0;
	while (i < length) {
		//if (this->key.GetAt(i) >= 33 && this->key.GetAt(i) <= 126) {
		if (this->key.GetAt(i) >= 32 && this->key.GetAt(i) <= 126) {
			i++;
		}
		else {
			i += 2;
		}
		keyLength++;
	}
	//3. ���� ����
	return keyLength;
}

CString& FindingForm::SetKey(CString key) {
	this->key = key;
	return this->key;
}

//1104 ������ ������ �̻���
//������ ���������� �޸���� y�������� �����Ѵ�.
void FindingForm::SortFindIndexes() {
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(FindWindow("OtherNote", NULL));
	//1. indexes�� pageIndex�� ������ ����.
	Long i = 0;
	PageForm *pageFormOne = otherNoteForm->GetPageForm(this->GetIndexes().GetAt(i).GetPageIndex());
	while (i < this->GetIndexes().GetLength() - 1) {
		//2. pageForm���� �ݺ��Ѵ�.
		Long j = i + 1;
		PageForm *pageFormOther = otherNoteForm->GetPageForm(this->GetIndexes().GetAt(j).GetPageIndex());
		while (j < this->GetIndexes().GetLength()
			&& pageFormOne == pageFormOther) {
			
			FindIndex oneIndex = this->GetIndexes().GetAt(i);
			FindIndex otherIndex = this->GetIndexes().GetAt(j);

			MemoForm *memoFormOne = this->GetIndexes().GetAt(i).GetMemoIndex();
			MemoForm *memoFormOther = this->GetIndexes().GetAt(j).GetMemoIndex();

			//2.1. ���� ��ġ�� �޸����� y�� ���Ѵ�.
			CRect memoFormOneWndRect;
			memoFormOne->GetWindowRect(&memoFormOneWndRect);
			Long onePositionY = memoFormOneWndRect.top;

			//2.2. ���� ��ġ�� �޸����� y�� ���Ѵ�.
			CRect memoFormOtherWndRect;
			memoFormOther->GetWindowRect(&memoFormOtherWndRect);
			Long otherPositionY = memoFormOtherWndRect.top;

			//2.3. ������ġ�� ������ġ�� y���� ũ�� 2���� ��ȯ�Ѵ�.
			if (onePositionY > otherPositionY) {
				FindIndex temp = this->GetIndexes().GetAt(i);
				this->GetIndexes().GetAt(i) = this->GetIndexes().GetAt(j);
				this->GetIndexes().GetAt(j) = temp;
			}
			else if (onePositionY == otherPositionY) { //Y�� ������ ���
				if (oneIndex.GetRow() > otherIndex.GetRow()) {
					FindIndex temp = this->GetIndexes().GetAt(i);
					this->GetIndexes().GetAt(i) = this->GetIndexes().GetAt(j);
					this->GetIndexes().GetAt(j) = temp;
				}
				else if (oneIndex.GetRow() == otherIndex.GetRow() && 
					oneIndex.GetColumn() > otherIndex.GetColumn()) {
					FindIndex temp = this->GetIndexes().GetAt(i);
					this->GetIndexes().GetAt(i) = this->GetIndexes().GetAt(j);
					this->GetIndexes().GetAt(j) = temp;
				}
			}
			j++;
			pageFormOther = otherNoteForm->GetPageForm(this->GetIndexes().GetAt(j).GetPageIndex());
		}
		i++;
		pageFormOne = otherNoteForm->GetPageForm(this->GetIndexes().GetAt(i).GetPageIndex());
	}
	//3. ������.
}

void FindingForm::CheckFindingTabItem() {
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
	CTabCtrl *cTabCtrl = otherNoteForm->GetTabCtrl();
	Long i = 0;
	while (i < this->GetIndexes().GetLength()) {		
		CDC *dc = cTabCtrl->GetDC();
		dc->SetBkMode(TRANSPARENT);
		CRect itemRect;
		cTabCtrl->GetItemRect(this->GetIndexes().GetAt(i).GetPageIndex(), &itemRect);
		itemRect.left += 2;
		itemRect.right = itemRect.left + 10;
		itemRect.top += 6;
		itemRect.bottom = itemRect.top + 10;
		dc->FillSolidRect(itemRect, RGB(0, 255, 0));
		i++;
	}
}

//1104 �߰� tab �ٽ� ã�� ǥ�� �����ϱ�
void FindingForm::CancelFindingTabItem() {
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
	CTabCtrl *cTabCtrl = otherNoteForm->GetTabCtrl();
	Long i = 0;
	while (i < this->GetIndexes().GetLength()) {
		CDC *dc = cTabCtrl->GetDC();
		dc->SetBkMode(TRANSPARENT);
		CRect itemRect;
		cTabCtrl->GetItemRect(this->GetIndexes().GetAt(i).GetPageIndex(), &itemRect);
		itemRect.left += 2;
		itemRect.right = itemRect.left + 10;
		itemRect.top += 6;
		itemRect.bottom = itemRect.top + 10;
		dc->FillSolidRect(itemRect, RGB(240, 240, 240));
		i++;
	}
	cTabCtrl->RedrawWindow();
}

//1104 ������ ã�� index�� ��� �����ϱ�
Long FindingForm::RemoveFindIndex(Long index) {
	Long ret = this->indexes.Delete(index);
	this->length = this->indexes.GetLength();
	this->capacity = this->indexes.GetCapacity();
	return ret;
}

void FindingForm::ClearFindIndexes() {
	this->indexes.Clear();
	this->length = 0;
	this->capacity = 0;
}

void FindingForm::SetIsEdited(bool isEdited) {
	this->isEdited = isEdited;
}

//void FindingForm::OnKillFocus(CWnd* pNewWnd) {
//	if (this->tempFlag == false) {
//		this->tempFlag = true;
//	}
//	else {
//		this->isEdited = true;
//	}
//	CFindReplaceDialog::OnKillFocus(pNewWnd);
//}

#include "Page.h"
Long FindingForm::GetNextIndex() {
	//1. ���� ���� ����
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	FindingForm *findingForm = otherNoteForm->GetFindingForm();
	Long pageIndex = static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent();
	PageForm *pageForm = static_cast<PageForm*>(otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent()));
	Page *page = static_cast<Page*>(pageForm->GetContents());
	MemoForm *memoFormIndex = pageForm->GetMemoForm(page->GetCurrent());
	Memo *memo = NULL;
	Long row = 0;
	Line *line = NULL;
	Long column = 0;

	if (page->GetCurrent() >= 0) {
		memo = static_cast<Memo*>(memoFormIndex->GetContents());
		row = memo->GetRow();
		line = memo->GetLine(memo->GetRow());
		column = line->GetColumn();
	}

	//2. 
	//������ �����Ŵ� �ɷ�����
	Long current = 0;
	while (current < findingForm->GetLength() && pageIndex > findingForm->GetAt(current).GetPageIndex()) {
		current++;
	}
	if (current >= findingForm->GetLength()) {
		current = 0;
		return current;
	}

	if (pageIndex < findingForm->GetAt(current).GetPageIndex()) {
		return current;
	}
	else {
		//memo ��
		CRect memoWndRect;
		memoFormIndex->GetWindowRect(&memoWndRect);
		CRect tempMemoWndRect;
		findingForm->GetAt(current).GetMemoIndex()->GetWindowRect(&tempMemoWndRect);
		while (current < findingForm->GetLength() && memoWndRect.top > tempMemoWndRect.top 
			&& pageIndex == findingForm->GetAt(current).GetPageIndex()) {
			current++;
			if (current < findingForm->GetLength()) {
				findingForm->GetAt(current).GetMemoIndex()->GetWindowRect(&tempMemoWndRect);
			}
			else {
				current = 0;
				return current;
			}
		}

		if (memoWndRect.top < tempMemoWndRect.top) {
			return current;
		}
		else {
			//row ��
			findingForm->GetAt(current).GetMemoIndex()->GetWindowRect(&tempMemoWndRect);
			while (current < findingForm->GetLength() && row > findingForm->GetAt(current).GetRow() 
				&& memoWndRect.top == tempMemoWndRect.top 
				&& pageIndex == findingForm->GetAt(current).GetPageIndex()) {
				current++;
				if (current < findingForm->GetLength()) {
					findingForm->GetAt(current).GetMemoIndex()->GetWindowRect(&tempMemoWndRect);
				}
				else {
					current = 0;
					return current;
				}
			}
			if (row < findingForm->GetAt(current).GetRow()) {
				return current;
			}
			else {
				//column�� 1121 ���� �ڵ�
				findingForm->GetAt(current).GetMemoIndex()->GetWindowRect(&tempMemoWndRect);
				while (current < findingForm->GetLength() && column > findingForm->GetAt(current).GetColumn() 
					&& row == findingForm->GetAt(current).GetRow() 
					&& memoWndRect.top == tempMemoWndRect.top 
					&& pageIndex == findingForm->GetAt(current).GetPageIndex()) {
					current++;
					if (current < findingForm->GetLength()) {
						findingForm->GetAt(current).GetMemoIndex()->GetWindowRect(&tempMemoWndRect);
					}
					else {
						current = 0;
						return current;
					}
				}
				if (column <= findingForm->GetAt(current).GetColumn()) {
					return current;
				}
			}
		}
	}
	
	/*if (current >= findingForm->GetLength()) {
		current = 0;
	}*/

	return current;
}

Long FindingForm::GetPreviousIndex() {
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	FindingForm *findingForm = otherNoteForm->GetFindingForm();
	Long pageIndex = static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent();
	PageForm *pageForm = static_cast<PageForm*>(otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent()));
	Page *page = static_cast<Page*>(pageForm->GetContents());
	MemoForm *memoFormIndex = pageForm->GetMemoForm(page->GetCurrent());
	Memo *memo = NULL;
	Long row = 0;
	Line *line = NULL;
	Long column = 0;
	
	if (page->GetCurrent() >= 0) {
		memo = static_cast<Memo*>(memoFormIndex->GetContents());
		row = memo->GetRow();
		line = memo->GetLine(memo->GetRow());
		column = line->GetColumn();
	}
	//2. 
	//������ �����Ŵ� �ɷ�����
	Long current = findingForm->GetLength() - 1;
	while (current >= 0 && pageIndex < findingForm->GetAt(current).GetPageIndex()) {
		current--;
	}
	if (current < 0) {
		current = current = findingForm->GetLength() - 1;
		return current;
	}

	if (pageIndex > findingForm->GetAt(current).GetPageIndex()) {
		return current;
	}
	else {
		//memo ��
		CRect memoWndRect;
		memoFormIndex->GetWindowRect(&memoWndRect);
		CRect tempMemoWndRect;
		findingForm->GetAt(current).GetMemoIndex()->GetWindowRect(&tempMemoWndRect);
		while (current >= 0 && memoWndRect.top < tempMemoWndRect.top
			&& pageIndex == findingForm->GetAt(current).GetPageIndex()) {
			current--;
			if (current >= 0) {
				findingForm->GetAt(current).GetMemoIndex()->GetWindowRect(&tempMemoWndRect);
			}
			else {
				current = findingForm->GetLength() - 1;
				return current;
			}
			
		}

		if (memoWndRect.top > tempMemoWndRect.top) {
			return current;
		}
		else {
			//row ��
			findingForm->GetAt(current).GetMemoIndex()->GetWindowRect(&tempMemoWndRect);
			while (current >= 0 && row < findingForm->GetAt(current).GetRow()
				&& memoWndRect.top == tempMemoWndRect.top
				&& pageIndex == findingForm->GetAt(current).GetPageIndex()) {
				current--;
				if (current >= 0) {
					findingForm->GetAt(current).GetMemoIndex()->GetWindowRect(&tempMemoWndRect);
				}
				else {
					current = findingForm->GetLength() - 1;
					return current;
				}
			}
			if (row > findingForm->GetAt(current).GetRow()) {
				return current;
			}
			/*else if (column > findingForm->GetAt(current).GetColumn()) {
			current++;
			}*/
			else {
				//column��
				findingForm->GetAt(current).GetMemoIndex()->GetWindowRect(&tempMemoWndRect);
				while (current >= 0 && column <= findingForm->GetAt(current).GetColumn() + findingForm->GetKeyLength() - 1
					&& row == findingForm->GetAt(current).GetRow()
					&& memoWndRect.top == tempMemoWndRect.top
					&& pageIndex == findingForm->GetAt(current).GetPageIndex()) {
					current--;
					if (current >= 0) {
						findingForm->GetAt(current).GetMemoIndex()->GetWindowRect(&tempMemoWndRect);
					}
					else {
						current = findingForm->GetLength() - 1;
						return current;
					}
				}
				if (column > findingForm->GetAt(current).GetColumn() + findingForm->GetKeyLength() - 1) {
					return current;
				}
			}
		}
	}

	/*if (current < 0) {
		current = findingForm->GetLength() - 1;
	}*/

	return current;
}


void FindingForm::ResetIndexes() {
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	//FindingForm *findingForm = otherNoteForm->GetFindingForm();
	if (this != NULL) {
		//ã���ܾ��� ���ڵ��� ǥ�ø� �����Ѵ�.
		this->EraseFindIndexes();
		if (this->GetLength() > 0) {
			if (this->GetAt(this->GetCurrent()).GetMemoIndex()->GetSelectedBuffer() != NULL) {
				this->GetAt(this->GetCurrent()).GetMemoIndex()->GetSelectedBuffer()->SetIsSelecting(false);
			}
			//������ ã�� findIndex���� �����Ѵ�.
			Long i = 0;
			while (i <= this->GetLength() - 1) {
				this->RemoveFindIndex(i);
			}
			//����tab�� ���� ���� ��� ĥ�ϱ�
			this->CancelFindingTabItem();
			//���� �������� ã�� ���ڵ��� �����Ѵ�
			otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent())->OnEraseFindIndexes();
		}
	}
}