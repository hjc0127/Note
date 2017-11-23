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
				//아래로, 다음 검색 클릭시
				//같은 페이지내 다음 단어로 커서 및 스크롤 이동
				return new FindDownward(form);
			}
			else {
				//위로, 다음 검색 클릭시
				//같은 페이지내 이전 찾은위치로 커서 및 스크롤 이동
				return new FindUpward(form);
			}
		}
		//else if (findingForm->GetIsEdited() == TRUE){
		else if (findingForm->GetLength() == 0){
			//새로운 키워드로 다음 검색 클릭시
			//모든 페이지의 색깔표시 다 지운 후 새로 찾은 위치들 다시 색깔표시, 페이지내 첫번째 찾은 위치에 블록커서
			return new FindOnNewStr(form);
			findingForm->SetIsEdited(false);
		}
	}
	//다이얼로그 종료시 포커스 보내기 위해서 추가한 부분 && 찾아서 선택된 문자들 강조해제하기
	else if (findingForm->IsTerminating() == TRUE) {
		findingForm->OnClose();
	}

	return 0;
	//else {
	//	//취소 클릭시
	//	//(만약에 있으면)색깔표시 다 지움
	//	return new CloseForm(form);
	//}
}