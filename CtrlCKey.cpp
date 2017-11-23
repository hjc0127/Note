//CtrlCKey.cpp

#include "CtrlCKey.h"
#include "MemoForm.h"

CtrlCKey::CtrlCKey(Form *form)
	:KeyAction(form) {

}

CtrlCKey::CtrlCKey(const CtrlCKey& source)
	: KeyAction(source) {

}

CtrlCKey::~CtrlCKey() {

}

CtrlCKey& CtrlCKey::operator=(const CtrlCKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "SelectedBuffer.h"
void CtrlCKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	//this->otherNoteForm->selectedBuffer->SetIsCopy(true);
	static_cast<MemoForm*>(this->form)->GetSelectedBuffer()->CopyToClipboard();
	static_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(true);
}