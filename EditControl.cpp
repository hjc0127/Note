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
		//��Ŀ���� OtherNoteForm�� �ش� 1030�̸������� ��Ƽ�ý�ũ��ĳ�� �������ֱ� ���ؼ� �߰�
		//otherNoteForm->SetFocus();
	}
	else if (nChar == VK_ESCAPE) {
		if (this != 0) {
			delete this;
		}
	}
	//else if (nChar == VK_RIGHT) {
	//	//ó�� ���ý� ��� ���ڰ� ���õǰ�, �׶� ->Ű ������ ĳ���� ���� ���� ǥ�õȴ�.
	//	this->SetSel(-1, -1);
	//	//this->ShowCaret();
	//	//this->SetFocus();
	//	//issue ĳ���� ��µ��� �ʴ´�....
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
