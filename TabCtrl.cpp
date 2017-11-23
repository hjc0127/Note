//TabCtrl.cpp

#include "TabCtrl.h"
#include "OtherNoteForm.h"
#include "EditControl.h"

BEGIN_MESSAGE_MAP(TabCtrl, CTabCtrl)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_ERASEBKGND()
	ON_WM_DRAWITEM()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_POPUP_DELETE, OnDeletePageForm)
	ON_COMMAND(ID_POPUP_COPY, OnCopyPageForm)
	ON_COMMAND(ID_POPUP_CHANGE_NAME, OnChangeName)
END_MESSAGE_MAP()

TabCtrl::TabCtrl()
	:CTabCtrl() {
	this->selectedItem = 0;
}

TabCtrl::~TabCtrl() {

}

TabCtrl::TabCtrl(const TabCtrl& source) {

}

TabCtrl& TabCtrl::operator=(const TabCtrl& source) {
	return *this;
}

Long TabCtrl::InsertItem(int nItem, CString name) {
	/*TCITEM item;
	item.mask = TCIF_TEXT;
	
	CString pageName("Page");
	CString pageNumber;
	pageNumber.Format("%d", nItem);
	pageName += pageNumber;*/

	//item.pszText = pageName;
	//pageForm->InsertItem(0, &item);
	//pageForm->InsertItem(1, &item);
	//this->InsertItem(nItem, lpszItem);
	
	//this->InsertItem(nItem, pageName);
	//this->CTabCtrl::InsertItem(nItem, pageName);
	this->CTabCtrl::InsertItem(nItem, name);
	
	return 0;
}

#include "Note.h"
#include "PageForm.h"
#include "HorizontalScroll.h"
#include "VerticalScroll.h"
#include "MouseActionCreator.h"
#include "MouseAction.h"
void TabCtrl::OnLButtonDown(UINT nFlags, CPoint point) {
	CTabCtrl::OnLButtonDown(nFlags, point);
	MouseActionCreator mouseActionCreator;
	MouseAction *mouseAction = mouseActionCreator.Create(this, nFlags, point, WM_LBUTTONDOWN);
	if (mouseAction != 0) {
		mouseAction->OnMouseAction(nFlags, point);
		delete mouseAction;
		mouseAction = 0;
	}
}

void TabCtrl::OnRButtonDown(UINT nFlags, CPoint point) {
	CTabCtrl::OnRButtonDown(nFlags, point);
	MouseActionCreator mouseActionCreator;
	MouseAction *mouseAction = mouseActionCreator.Create(this, nFlags, point, WM_RBUTTONDOWN);
	if (mouseAction != 0) {
		mouseAction->OnMouseAction(nFlags, point);
		delete mouseAction;
		mouseAction = 0;
	}
}

//1017�߰�
void TabCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) {
	CTabCtrl::OnLButtonDblClk(nFlags, point);
	MouseActionCreator mouseActionCreator;
	MouseAction *mouseAction = mouseActionCreator.Create(this, nFlags, point, WM_LBUTTONDBLCLK);
	if (mouseAction != 0) {
		mouseAction->OnMouseAction(nFlags, point);
		delete mouseAction;
		mouseAction = 0;
	}
}

void TabCtrl::OnPaint() {
	CTabCtrl::OnPaint();
	this->DrawTabItem();
}

#include "OtherNoteForm.h"
#include "FindingForm.h"
void TabCtrl::OnDeletePageForm() {

	//1121 ã�� index ���� �ϱ�
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	FindingForm *findingForm = otherNoteForm->GetFindingForm();
	if (findingForm != NULL) {
		findingForm->ResetIndexes();
	}

	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));

	//1. ���� �������� �����Ѵ�.
	PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
	pageForm->OnClose();
	//2. ���� Ŭ���� tab ��ġ�� ���Ѵ�.
	Long index = this->GetCurSel();
	//3. ���� tabitem�� �����Ѵ�.
	this->DeleteItem(index);
	//4. tab item�� ������ ���Ѵ�.
	Long count = this->GetItemCount();
	//5. ������tab���� �����Ѵ�.
	//this->SetCurSel(count - 1);
	if (count >= 1) {
		this->SetCurSel(count - 1);
		otherNoteForm->SelectTabItem(count - 1);
	}
	else {
		Long index = static_cast<Note*>(otherNoteForm->GetContents())->AddPage();
		Page *page = static_cast<Note*>(otherNoteForm->GetContents())->GetPage(index);
		index = otherNoteForm->AddPageForm(page);
		pageForm = otherNoteForm->GetPageForm(index);
		pageForm->ShowWindow(SW_SHOW);
		otherNoteForm->GetTabCtrl()->SetCurSel(index);
		pageForm->SetFocus();
	}
}

#include "CopyVisitor.h"
#include "MemoForm.h"
#include "Page.h"
void TabCtrl::OnCopyPageForm() {
	//1. Ŭ���ߴ� tab���� page�� �˾ƿ´�.
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
	PageForm *oldPageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
	oldPageForm->ShowWindow(SW_HIDE);

	//2. AddPageForm(pageForm)
	Page *newPage = new Page(*static_cast<Page*>(oldPageForm->GetContents()));
	//static_cast<Note*>(otherNoteForm->GetContents())->AddPage();
	static_cast<Note*>(otherNoteForm->GetContents())->AddPage(newPage);

	CString pageFormName;
	pageFormName = oldPageForm->GetPageFormName().c_str();

	PageForm *newPageForm = new PageForm(newPage, 64, (LPCTSTR)pageFormName);
	Long index = otherNoteForm->AddPageForm(newPageForm);

	//11/12 ��ũ�� ���� ���ϴ� ���� ����
	CRect originPageFormRect;
	oldPageForm->GetWindowRect(&originPageFormRect);
	newPageForm->SetWindowPos(0, originPageFormRect.left, originPageFormRect.top, originPageFormRect.right - originPageFormRect.left, originPageFormRect.bottom - originPageFormRect.top, 0);
	newPageForm->UpdateScrinfo();

	//3. create memoform
	Long i = 0;
	while (i < newPage->GetLength()) {
		MemoForm *newMemoForm = new MemoForm(*(oldPageForm->GetMemoForm(i)));//11/12 ������ �����ϱ� �״� ����
		newMemoForm->SetContents(newPage->GetMemo(i));
		newPageForm->AddMemoForm(newMemoForm);
		i++;
	}

	//4. pageForm�� Show���ش�.
	newPageForm->ShowWindow(SW_SHOW);

	//5. ����� tab���� �����Ѵ�.
	this->SetCurSel(index);
	otherNoteForm->SelectTabItem(index);
	newPageForm->SetFocus();

	//6. ĳ���� �����ϵ��� �������ش�.
	if (newPageForm->GetLength() != 0) {
		newPageForm->GetMemoForm(static_cast<Page*>(newPageForm->GetContents())->GetCurrent())->HideCaret();
	}

	//11/12 ��ũ���� �ش� �������� �����Ѵ�.
	otherNoteForm->GetHorizontalScroll()->SetCurrent(index);
	otherNoteForm->GetVerticalScroll()->SetCurrent(index);

	//7. ���Ӱ� ������ �������� ǥ�ø� ���ش�.
	this->DrawTabItem();
}

//void TabCtrl::UpdataItemName() {
//
//}

void TabCtrl::DrawTabItem() {
	//1. ���õ� �������� �ε����� ���Ѵ�.
	Long selectIndex = this->GetCurSel();
	//2. dc�� ���Ѵ�.
	CDC *dc = this->GetDC();
	dc->SetBkMode(TRANSPARENT);
	//3. ���� ������ tab item�� ������ ������ ǥ�ø� �Ѵ�.
	Long i = 0;
	while (i < this->GetItemCount()) {
		if (i == this->GetCurSel()) {
			CRect itemRectTop;
			this->GetItemRect(i, &itemRectTop);
			itemRectTop.bottom = itemRectTop.top + 4;
			//itemRectTop.bottom = itemRectTop.top + 2;
			dc->FillSolidRect(itemRectTop, RGB(250, 170, 60));

			/*CRect itemRectBottom;
			this->GetItemRect(i, &itemRectBottom);
			itemRectBottom.top = itemRectBottom.bottom - 2;
			dc->FillSolidRect(itemRectBottom, RGB(250, 170, 60));

			CRect itemRectLeft;
			this->GetItemRect(i, &itemRectLeft);
			itemRectLeft.right = itemRectLeft.left + 2;
			dc->FillSolidRect(itemRectLeft, RGB(250, 170, 60));

			CRect itemRectRight;
			this->GetItemRect(i, &itemRectRight);
			itemRectRight.left = itemRectRight.right - 2;
			dc->FillSolidRect(itemRectRight, RGB(250, 170, 60));*/
		}
		i++;
	}
}

CString TabCtrl::GetItemName() {
	CString itemName("");
	//1. ���� ���õ� item�� ��ġ�� ���Ѵ�.
	Long index = this->GetCurSel();

	//2. tab���� ������ ��Ī�� �����´�.
	TCITEM tcItem;
	TCHAR buffer[256] = { 0 };
	tcItem.pszText = buffer;
	tcItem.cchTextMax = 256;
	tcItem.mask = TCIF_TEXT;
	this->GetItem(index, &tcItem);

	//3. ������ ��Ī���� �յ� ������ �����Ѵ�.
	itemName = tcItem.pszText;
	itemName.Trim();
	
	//4. tab item ��Ī�� ��ȯ�Ѵ�.
	return itemName;
}

void TabCtrl::OnChangeName() {
	//1. ���õ� ���� �ҷ��´�.
	//Long index = this->GetCurSel();
	this->selectedItem = this->GetCurSel();

	//2. ���̾�α׸� ����.
	CRect rect;
	//this->GetItemRect(index, &rect);
	this->GetItemRect(this->selectedItem, &rect);
	this->editCtrl = new EditControl;
	this->editCtrl->Create(ES_AUTOHSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rect, this, 1);
	
	//3. ���� tab item�� ��Ī�� ����Ѵ�.
	this->editCtrl->SetWindowText(this->GetItemName());

	//4. editCtrl�� ��ü ���ڸ� �����Ѵ�.
	this->editCtrl->SetSel(0, -1);
	this->editCtrl->SetFocus();
	//this->editCtrl->HideCaret();//��� ���ڰ� ���ø� �ǰ� ĳ���� ����� ���ؼ� �߰���
}

void TabCtrl::UpdateItemName() {
	//1. ������ ��Ī�� �����Ѵ�.
	CString inputName = "";
	this->editCtrl->GetWindowText(inputName);
	CString newName = "   ";//3ĭ
	newName += inputName;
	newName += "   ";//3ĭ

	//2. tab�� ���� ���õ� tab�� �����´�.
	//Long index = this->GetCurSel();

	//3. ������ �̸��� �Է¹޴´�.
	TCITEM item;
	item.mask = TCIF_TEXT;
	item.pszText = newName.GetBuffer(256);;

	//4. ������ �̸����� tab�� �����Ѵ�.
	//this->SetItem(index, &item);
	this->SetItem(this->selectedItem, &item);

	//5. page �̸��� �����Ѵ�.1104
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
	//PageForm *pageForm = otherNoteForm->GetPageForm(index);
	PageForm *pageForm = otherNoteForm->GetPageForm(this->selectedItem);
	pageForm->SetPageFormName((LPCTSTR)newName);

	//5. EditControl�� �����Ѵ�.
	/*if (this != 0) {
		delete this;
	}*/
}

#include "FindingForm.h"
void TabCtrl::OnSetFocus(CWnd *pOldWnd) {
	CTabCtrl::OnSetFocus(pOldWnd);
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
	FindingForm *findingForm = otherNoteForm->GetFindingForm();
	if (findingForm != NULL) {
		findingForm->SetIsEdited(true);
	}
}

#include "FindingForm.h"
void TabCtrl::OnKillFocus(CWnd *pOldWnd) {
	CTabCtrl::OnKillFocus(pOldWnd);
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
	FindingForm *findingForm = otherNoteForm->GetFindingForm();
	if (findingForm != NULL) {
		findingForm->SetIsEdited(false);
	}
}