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
	context += "����� ������ ";
	context += this->fileName;
	context += "�� �����Ͻðڽ��ϱ�?";
	SetDlgItemText(IDC_STATIC_CONTEXT, context);
	return TRUE;
}

//1. �������� ���� ����
//2. ���� �ۼ�
//3. ���� ����� Ŭ��
//3.1. ����
//3.1.1. SaveAS����
//3.1.2. otherNote ����
//3.2. �������
//3.2.1. otherNote ����
//3.3. ���
//3.3.1. ���̾�α� �ݱ�

//1. ������ ����
//2. ���θ���� Ŭ��
//3. ���� �ݰ� otherNote ����
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