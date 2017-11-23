//NewFileDialog.cpp

#include "NewFileDialog.h"
BEGIN_MESSAGE_MAP(NewFileDialog, CDialog)
	ON_BN_CLICKED(IDOK, &NewFileDialog::OnOkButtonClicked)
	ON_BN_CLICKED(IDC_BUTTON_NOSAVE, &NewFileDialog::OnNoSaveButtonClicked)
	ON_BN_CLICKED(IDCANCEL, &NewFileDialog::OnCancelButtonClicked)
END_MESSAGE_MAP()

#include "OtherNoteForm.h"
NewFileDialog::NewFileDialog(UINT nIDTemplate, CWnd* pParentWnd)
	:CDialog(nIDTemplate, pParentWnd) {
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
	this->fileName = otherNoteForm->GetFileName();
}

NewFileDialog::~NewFileDialog() {

}

BOOL NewFileDialog::OnInitDialog() {
	CDialog::OnInitDialog();
	CString context;
	context += "변경된 내용을 ";
	context += this->fileName;
	context += "에 저장하시겠습니까?";
	SetDlgItemText(IDC_STATIC_CONTEXT, context);
	return TRUE;
}

//1. 저장한적 없는 상태
//2. 내용 작성
//3. 새로 만들기 클릭
//3.1. 저장
//3.1.1. SaveAS열고
//3.1.2. otherNote 리셋
//3.2. 저장안함
//3.2.1. otherNote 리셋
//3.3. 취소
//3.3.1. 다이얼로그 닫기

//1. 열기한 상태
//2. 새로만들기 클릭
//3. 파일 닫고 otherNote 리셋
#include "OtherNoteForm.h"
void NewFileDialog::OnOkButtonClicked() {
	CDialog::OnOK();
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(FindWindow("OtherNote", NULL));
	otherNoteForm->OnMenuSaveAs();
	otherNoteForm->Reset();
}

#include "PageForm.h"
#include "Note.h"
#include "Page.h"
#include "CharacterFaces.h"
void NewFileDialog::OnNoSaveButtonClicked() {
	CDialog::OnCancel();
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(FindWindow("OtherNote", NULL));
	otherNoteForm->Reset();
}

void NewFileDialog::OnCancelButtonClicked() {
	CDialog::OnCancel();
}