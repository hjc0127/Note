//TabCtrlMouseLButtonDown.cpp

//#include "Form.h"
#include "TabCtrlMouseLButtonDown.h"
#include "TabCtrl.h"
#include "Note.h"
#include "OtherNoteForm.h"
#include "PageForm.h"
#include "Page.h"
#include "MemoForm.h"
#include "Memo.h"
#include "Caret.h"
#include "SelectedBuffer.h"
#include "Line.h"
#include "HorizontalScroll.h"
#include "VerticalScroll.h"

TabCtrlMouseLButtonDown::TabCtrlMouseLButtonDown(TabCtrl *form)
	:MouseAction(form) {
	//this->form = form;
}

TabCtrlMouseLButtonDown::TabCtrlMouseLButtonDown(const TabCtrlMouseLButtonDown& source)
	: MouseAction(source) {
	//this->form = source.form;
}

TabCtrlMouseLButtonDown::~TabCtrlMouseLButtonDown() {

}

TabCtrlMouseLButtonDown& TabCtrlMouseLButtonDown::operator=(const TabCtrlMouseLButtonDown& source) {
	//this->form = source.form;
	MouseAction::operator=(source);

	return *this;
}

#include "FindingForm.h"
void TabCtrlMouseLButtonDown::OnMouseAction(UINT nFlags, CPoint point) {
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	
	//1. ���� �������� hide�Ѵ�.
	PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
	//pageForm->CleanUpMemoForms();
	pageForm->ShowWindow(SW_HIDE);
	
	//2. ���� Ŭ���� tab ��ġ�� ���Ѵ�.
	Long index = static_cast<TabCtrl*>(this->form)->GetCurSel();
	
	//3. ���õ� tab���� �����Ѵ�.
	otherNoteForm->SelectTabItem(index);

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

	//6. ã�� tab�� ǥ���ϱ� 1116
	FindingForm *findingForm = otherNoteForm->GetFindingForm();
	if (findingForm != NULL) {
		findingForm->CheckFindingTabItem();
	}

	//7. note�� current�� ���� 1121
	static_cast<Note*>(otherNoteForm->GetContents())->SetCurrent(index);
}

void TabCtrlMouseLButtonDown::OnMouseAction(int x, int y) {

}

void TabCtrlMouseLButtonDown::OnMouseAction(UINT nSide, LPRECT lpRect) {

}