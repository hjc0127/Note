//EditControl.cpp
#include "EditControl.h"

BEGIN_MESSAGE_MAP(EditControl, CEdit)
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

EditControl::EditControl() 
	:CEdit(){
}

EditControl::~EditControl() {

}

EditControl::EditControl(const EditControl& source) {

}

EditControl& EditControl::operator = (const EditControl& source) {
	return *this;
}

#include "OtherNoteForm.h"
#include "TabCtrl.h"
void EditControl::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar == VK_RETURN) {
		OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
		TabCtrl *tabCtrl = otherNoteForm->GetTabCtrl();
		tabCtrl->UpdateItemName();
		if (this != 0) {
			delete this;
		}
		//포커스를 OtherNoteForm에 준다 1030이름변경후 버티컬스크롤캐럿 제거해주기 위해서 추가
		//otherNoteForm->SetFocus();
	}
	else if (nChar == VK_ESCAPE) {
		if (this != 0) {
			delete this;
		}
	}
	//else if (nChar == VK_RIGHT) {
	//	//처음 선택시 모든 문자가 선택되고, 그때 ->키 누르면 캐럿이 제일 끝에 표시된다.
	//	this->SetSel(-1, -1);
	//	//this->ShowCaret();
	//	//this->SetFocus();
	//	//issue 캐럿이 출력되지 않는다....
	//}
	else {
		//this->ShowCaret();
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
	
}

void EditControl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if ((nChar == 'A' || nChar == 'a') && GetKeyState(VK_CONTROL) < 0) {
		this->SetSel(0, -1);
		this->SetFocus();
	}
	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

#include "OtherNoteForm.h"
void EditControl::OnKillFocus(CWnd* pNewWnd) {
	CEdit::OnKillFocus(pNewWnd);
	
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
	TabCtrl *tabCtrl = otherNoteForm->GetTabCtrl();
	tabCtrl->UpdateItemName();

	if (this != 0) {
		delete this;
	}
}
