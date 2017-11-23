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
	
	//1. 현재 페이지를 hide한다.
	PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
	//pageForm->CleanUpMemoForms();
	pageForm->ShowWindow(SW_HIDE);
	
	//2. 현재 클릭된 tab 위치를 구한다.
	Long index = static_cast<TabCtrl*>(this->form)->GetCurSel();
	
	//3. 선택된 tab으로 변경한다.
	otherNoteForm->SelectTabItem(index);

	//4. 마지막 메모폼에 포커스 주기
	pageForm = otherNoteForm->GetPageForm(index);
	if (pageForm->GetLength() > 0) {		
		pageForm->GetMemoForm(pageForm->GetLength() - 1)->SetFocus();
	}
	
	//4. 스크롤을 해당 페이지로 갱신한다.
	otherNoteForm->GetHorizontalScroll()->SetCurrent(index);
	otherNoteForm->GetVerticalScroll()->SetCurrent(index);

	//5. 선택된 tab에 표시하기
	static_cast<TabCtrl*>(this->form)->DrawTabItem();

	//6. 찾기 tab에 표시하기 1116
	FindingForm *findingForm = otherNoteForm->GetFindingForm();
	if (findingForm != NULL) {
		findingForm->CheckFindingTabItem();
	}

	//7. note의 current를 변경 1121
	static_cast<Note*>(otherNoteForm->GetContents())->SetCurrent(index);
}

void TabCtrlMouseLButtonDown::OnMouseAction(int x, int y) {

}

void TabCtrlMouseLButtonDown::OnMouseAction(UINT nSide, LPRECT lpRect) {

}