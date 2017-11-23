//TabCtrlMouseRButtonDown.cpp

//#include "Form.h"
#include "TabCtrlMouseRButtonDown.h"
#include "TabCtrl.h"

TabCtrlMouseRButtonDown::TabCtrlMouseRButtonDown(TabCtrl *form)
	:MouseAction(form) {
	//this->form = form;
}

TabCtrlMouseRButtonDown::TabCtrlMouseRButtonDown(const TabCtrlMouseRButtonDown& source)
	: MouseAction(source) {
	//this->form = source.form;
}

TabCtrlMouseRButtonDown::~TabCtrlMouseRButtonDown() {

}

TabCtrlMouseRButtonDown& TabCtrlMouseRButtonDown::operator=(const TabCtrlMouseRButtonDown& source) {
	//this->form = source.form;
	MouseAction::operator=(source);

	return *this;
}

#include "Note.h"
#include "PageForm.h"
//#include "Page.h"
//#include "MemoForm.h"
//#include "Memo.h"
//#include "Caret.h"
//#include "SelectedBuffer.h"
//#include "Line.h"
#include "OtherNoteForm.h"
#include "HorizontalScroll.h"
#include "VerticalScroll.h"
void TabCtrlMouseRButtonDown::OnMouseAction(UINT nFlags, CPoint point) {
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	//1. ���� �������� hide�Ѵ�.
	PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
	//pageForm->CleanUpMemoForms();
	pageForm->ShowWindow(SW_HIDE);
	
	TC_HITTESTINFO tcHitTestInfo;
	POINT sPoint;
	sPoint.x = point.x;
	sPoint.y = point.y;
	tcHitTestInfo.pt = sPoint;
	tcHitTestInfo.flags = nFlags;
	Long index = static_cast<TabCtrl*>(this->form)->HitTest(&tcHitTestInfo);
	
	//2. ���� Ŭ���� tab ��ġ�� ���Ѵ�.
	otherNoteForm->SelectTabItem(index);
	
	//3. ���õ� tab���� �����Ѵ�.
	static_cast<TabCtrl*>(this->form)->SetCurSel(index);

	//4. ������ �޸����� ��Ŀ�� �ֱ�
	pageForm = otherNoteForm->GetPageForm(index);
	if (pageForm->GetLength() > 0) {
		pageForm->GetMemoForm(pageForm->GetLength() - 1)->SetFocus();
	}
	
	//4. ��ũ���� �ش� �������� �����Ѵ�.
	otherNoteForm->GetHorizontalScroll()->SetCurrent(index);
	otherNoteForm->GetVerticalScroll()->SetCurrent(index);

	//5. ���õ� tab�� ǥ���ϱ�
	static_cast<TabCtrl*>(this->form)->DrawTabItem();
	
	//6. Pop-up menu
	CMenu menu;
	menu.LoadMenu(IDR_MENU_POPUP);
	CMenu *popupMenu = menu.GetSubMenu(0);
	CPoint position;
	GetCursorPos(&position);
	popupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, position.x, position.y, this->form);
	menu.DestroyMenu();
}

void TabCtrlMouseRButtonDown::OnMouseAction(int x, int y) {

}

void TabCtrlMouseRButtonDown::OnMouseAction(UINT nSide, LPRECT lpRect) {

}