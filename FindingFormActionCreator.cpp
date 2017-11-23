//FindingFormActionCreator.cpp

#include "FindingFormActionCreator.h"
#include "FindingForm.h"
#include "FindDownward.h"
#include "FindUpward.h"
#include "FindOnNewStr.h"
#include "CloseForm.h"
#include "Form.h"


FindingFormActionCreator::FindingFormActionCreator() {

}

FindingFormActionCreator::FindingFormActionCreator(const FindingFormActionCreator& source) {

}

FindingFormActionCreator::~FindingFormActionCreator() {

}

FindingFormActionCreator& FindingFormActionCreator::operator=(const FindingFormActionCreator& source) {
	return *this;
}

#include "OtherNoteForm.h"
#include "PageForm.h"
#include "MemoForm.h"
#include "Note.h"
#include "FindIndex.h"
#include "Memo.h"
#include "Line.h"
#include "SelectedBuffer.h"
FindingFormAction* FindingFormActionCreator::Create(Form *form, WPARAM wParam, LPARAM lParam) {
	FINDREPLACE *findReplace = (FINDREPLACE*)(lParam);
	FindingForm *findingForm= static_cast<FindingForm*>(CFindReplaceDialog::GetNotifier(lParam));
	if (findingForm->FindNext() == TRUE) {
		//if (findingForm->GetKey() == CString(findReplace->lpstrFindWhat) && findingForm->GetIsEdited() == FALSE) {
		if (findingForm->GetLength() > 0) {
			if (findingForm->SearchDown() == TRUE) {
				//�Ʒ���, ���� �˻� Ŭ����
				//���� �������� ���� �ܾ�� Ŀ�� �� ��ũ�� �̵�
				return new FindDownward(form);
			}
			else {
				//����, ���� �˻� Ŭ����
				//���� �������� ���� ã����ġ�� Ŀ�� �� ��ũ�� �̵�
				return new FindUpward(form);
			}
		}
		//else if (findingForm->GetIsEdited() == TRUE){
		else if (findingForm->GetLength() == 0){
			//���ο� Ű����� ���� �˻� Ŭ����
			//��� �������� ����ǥ�� �� ���� �� ���� ã�� ��ġ�� �ٽ� ����ǥ��, �������� ù��° ã�� ��ġ�� ���Ŀ��
			return new FindOnNewStr(form);
			findingForm->SetIsEdited(false);
		}
	}
	//���̾�α� ����� ��Ŀ�� ������ ���ؼ� �߰��� �κ� && ã�Ƽ� ���õ� ���ڵ� ���������ϱ�
	else if (findingForm->IsTerminating() == TRUE) {
		findingForm->OnClose();
	}

	return 0;
	//else {
	//	//��� Ŭ����
	//	//(���࿡ ������)����ǥ�� �� ����
	//	return new CloseForm(form);
	//}
}