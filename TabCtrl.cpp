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

//1017추가
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

	//1121 찾은 index 해제 하기
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	FindingForm *findingForm = otherNoteForm->GetFindingForm();
	if (findingForm != NULL) {
		findingForm->ResetIndexes();
	}

	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));

	//1. 현재 페이지를 삭제한다.
	PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
	pageForm->OnClose();
	//2. 현재 클릭된 tab 위치를 구한다.
	Long index = this->GetCurSel();
	//3. 현재 tabitem을 제거한다.
	this->DeleteItem(index);
	//4. tab item의 개수를 구한다.
	Long count = this->GetItemCount();
	//5. 마지막tab으로 설정한다.
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
	//1. 클릭했던 tab에서 page를 알아온다.
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

	//11/12 스크롤 갱신 못하는 버그 수정
	CRect originPageFormRect;
	oldPageForm->GetWindowRect(&originPageFormRect);
	newPageForm->SetWindowPos(0, originPageFormRect.left, originPageFormRect.top, originPageFormRect.right - originPageFormRect.left, originPageFormRect.bottom - originPageFormRect.top, 0);
	newPageForm->UpdateScrinfo();

	//3. create memoform
	Long i = 0;
	while (i < newPage->GetLength()) {
		MemoForm *newMemoForm = new MemoForm(*(oldPageForm->GetMemoForm(i)));//11/12 페이지 복사하기 죽는 문제
		newMemoForm->SetContents(newPage->GetMemo(i));
		newPageForm->AddMemoForm(newMemoForm);
		i++;
	}

	//4. pageForm을 Show해준다.
	newPageForm->ShowWindow(SW_SHOW);

	//5. 복사된 tab으로 변경한다.
	this->SetCurSel(index);
	otherNoteForm->SelectTabItem(index);
	newPageForm->SetFocus();

	//6. 캐럿을 삭제하도록 설정해준다.
	if (newPageForm->GetLength() != 0) {
		newPageForm->GetMemoForm(static_cast<Page*>(newPageForm->GetContents())->GetCurrent())->HideCaret();
	}

	//11/12 스크롤을 해당 페이지로 갱신한다.
	otherNoteForm->GetHorizontalScroll()->SetCurrent(index);
	otherNoteForm->GetVerticalScroll()->SetCurrent(index);

	//7. 새롭게 복사한 페이지에 표시를 해준다.
	this->DrawTabItem();
}

//void TabCtrl::UpdataItemName() {
//
//}

void TabCtrl::DrawTabItem() {
	//1. 선택된 아이템의 인덱스를 구한다.
	Long selectIndex = this->GetCurSel();
	//2. dc를 구한다.
	CDC *dc = this->GetDC();
	dc->SetBkMode(TRANSPARENT);
	//3. 현재 선택한 tab item은 설정된 색으로 표시를 한다.
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
	//1. 현재 선택된 item의 위치를 구한다.
	Long index = this->GetCurSel();

	//2. tab에서 기존의 명칭을 가져온다.
	TCITEM tcItem;
	TCHAR buffer[256] = { 0 };
	tcItem.pszText = buffer;
	tcItem.cchTextMax = 256;
	tcItem.mask = TCIF_TEXT;
	this->GetItem(index, &tcItem);

	//3. 가져온 명칭에서 앞뒤 공백은 삭제한다.
	itemName = tcItem.pszText;
	itemName.Trim();
	
	//4. tab item 명칭을 반환한다.
	return itemName;
}

void TabCtrl::OnChangeName() {
	//1. 선택된 탭의 불러온다.
	//Long index = this->GetCurSel();
	this->selectedItem = this->GetCurSel();

	//2. 다이얼로그를 띄운다.
	CRect rect;
	//this->GetItemRect(index, &rect);
	this->GetItemRect(this->selectedItem, &rect);
	this->editCtrl = new EditControl;
	this->editCtrl->Create(ES_AUTOHSCROLL | WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER, rect, this, 1);
	
	//3. 현재 tab item의 명칭을 출력한다.
	this->editCtrl->SetWindowText(this->GetItemName());

	//4. editCtrl의 전체 글자를 선택한다.
	this->editCtrl->SetSel(0, -1);
	this->editCtrl->SetFocus();
	//this->editCtrl->HideCaret();//모든 글자가 선택만 되고 캐럿을 숨기기 위해서 추가함
}

void TabCtrl::UpdateItemName() {
	//1. 변경할 명칭을 설정한다.
	CString inputName = "";
	this->editCtrl->GetWindowText(inputName);
	CString newName = "   ";//3칸
	newName += inputName;
	newName += "   ";//3칸

	//2. tab의 현재 선택된 tab을 가져온다.
	//Long index = this->GetCurSel();

	//3. 변경할 이름을 입력받는다.
	TCITEM item;
	item.mask = TCIF_TEXT;
	item.pszText = newName.GetBuffer(256);;

	//4. 변경한 이름으로 tab을 설정한다.
	//this->SetItem(index, &item);
	this->SetItem(this->selectedItem, &item);

	//5. page 이름을 갱신한다.1104
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
	//PageForm *pageForm = otherNoteForm->GetPageForm(index);
	PageForm *pageForm = otherNoteForm->GetPageForm(this->selectedItem);
	pageForm->SetPageFormName((LPCTSTR)newName);

	//5. EditControl을 해제한다.
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