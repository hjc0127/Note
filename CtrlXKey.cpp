//CtrlXKey.cpp

#include "CtrlXKey.h"
#include "KeyActionCreator.h"
#include "MemoForm.h"
#include "Memo.h"
#include "Line.h"
#include "SelectedBuffer.h"
#include "CtrlCKey.h"
#include "DeleteKey.h"

CtrlXKey::CtrlXKey(Form *form)
	:KeyAction(form) {

}

CtrlXKey::CtrlXKey(const CtrlXKey& source)
	: KeyAction(source) {

}

CtrlXKey::~CtrlXKey() {

}

CtrlXKey& CtrlXKey::operator=(const CtrlXKey& source) {
	KeyAction::operator=(source);

	return *this;
}

void CtrlXKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	CtrlCKey ctrlCKey = CtrlCKey(this->form);
	ctrlCKey.OnKeyDown(nChar, nRepCnt, nFlags);
	
	DeleteKey deleteKey = DeleteKey(this->form);
	deleteKey.OnKeyDown(nChar, nRepCnt, nFlags);
	dynamic_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);
}