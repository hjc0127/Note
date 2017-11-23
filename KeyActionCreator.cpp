//KeyActionCreator.cpp

#include "KeyActionCreator.h"
#include "LeftArrowKey.h"
#include "UpArrowKey.h"
#include "DownArrowKey.h"
#include "RightArrowKey.h"
#include "CtrlLeftArrowKey.h"
#include "CtrlRightArrowKey.h"
#include "CtrlCKey.h"
#include "CtrlVKey.h"
#include "CtrlXKey.h"
#include "ShiftLeftArrowKey.h"
#include "ShiftRightArrowKey.h"
#include "ShiftUpArrowKey.h"
#include "ShiftDownArrowKey.h"
#include "ShiftHomeKey.h"
#include "ShiftEndKey.h"
#include "ShiftCtrlHomeKey.h"
#include "ShiftCtrlEndKey.h"
#include "ShiftCtrlLeftArrowKey.h"
#include "ShiftCtrlRightArrowKey.h"
//#include "CtrlShiftLeftArrowKey.h"
//#include "CtrlShiftRightArrowKey.h"
#include "TabKey.h"
#include "ReturnKey.h"
#include "BackspaceKey.h"
#include "DeleteKey.h"
#include "HomeKey.h"
#include "EndKey.h"
#include "CtrlHomeKey.h"
#include "CtrlEndKey.h"
#include "CharacterKey.h"


KeyActionCreator::KeyActionCreator() {

}

KeyActionCreator::KeyActionCreator(const KeyActionCreator& source) {

}

KeyActionCreator::~KeyActionCreator() {

}

KeyActionCreator& KeyActionCreator::operator=(const KeyActionCreator& source) {
	return *this;
}

#include "FindingForm.h"
#include "OtherNoteForm.h"
KeyAction* KeyActionCreator::Create(Form *form, UINT nChar, UINT nRepCnt, UINT nFlags, Long message) {
	//1121 찾은 index 해제 하기
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	FindingForm *findingForm = otherNoteForm->GetFindingForm();
	if (findingForm != NULL) {
		findingForm->ResetIndexes();
	}

	if (nChar >= 32 && nChar <= 126 && message == WM_CHAR) {
		return new CharacterKey(form);
	}
	else if ((nChar == 'C'|| nChar == 'c') && GetKeyState(VK_CONTROL) < 0) {
		return new CtrlCKey(form);
	}
	else if ((nChar == 'V' || nChar == 'v') && GetKeyState(VK_CONTROL) < 0) {
		return new CtrlVKey(form);
	}
	else if ((nChar == 'X' || nChar == 'x') && GetKeyState(VK_CONTROL) < 0) {
		return new CtrlXKey(form);
	}
	else if (nChar == VK_HOME && GetKeyState(VK_SHIFT) < 0 && GetKeyState(VK_CONTROL) < 0) {
		return new ShiftCtrlHomeKey(form);
	}
	else if (nChar == VK_END && GetKeyState(VK_SHIFT) < 0 && GetKeyState(VK_CONTROL) < 0) {
		return new ShiftCtrlEndKey(form);
	}
	else if (nChar == VK_LEFT && GetKeyState(VK_SHIFT) < 0 && GetKeyState(VK_CONTROL) < 0) {
		return new ShiftCtrlLeftArrowKey(form);
	}
	else if (nChar == VK_RIGHT && GetKeyState(VK_SHIFT) < 0 && GetKeyState(VK_CONTROL) < 0) {
		return new ShiftCtrlRightArrowKey(form);
	}
	else if (nChar == VK_HOME && GetKeyState(VK_CONTROL) < 0) {
		return new CtrlHomeKey(form);
	}
	else if (nChar == VK_END && GetKeyState(VK_CONTROL) < 0) {
		return new CtrlEndKey(form);
	}
	else if (nChar == VK_LEFT && GetKeyState(VK_CONTROL) < 0) {
		return new CtrlLeftArrowKey(form);
	}
	else if (nChar == VK_RIGHT && GetKeyState(VK_CONTROL) < 0) {
		return new CtrlRightArrowKey(form);
	}
	else if (nChar == VK_HOME && GetKeyState(VK_SHIFT) < 0) {
		return new ShiftHomeKey(form);
	}
	else if (nChar == VK_END && GetKeyState(VK_SHIFT) < 0) {
		return new ShiftEndKey(form);
	}
	else if (nChar == VK_LEFT && GetKeyState(VK_SHIFT) < 0) {
		return new ShiftLeftArrowKey(form);
	}
	else if (nChar == VK_RIGHT && GetKeyState(VK_SHIFT) < 0) {
		return new ShiftRightArrowKey(form);
	}
	else if (nChar == VK_UP && GetKeyState(VK_SHIFT) < 0) {
		return new ShiftUpArrowKey(form);
	}
	else if (nChar == VK_DOWN && GetKeyState(VK_SHIFT) < 0) {
		return new ShiftDownArrowKey(form);
	}
	else if (nChar == VK_LEFT) {
		return new LeftArrowKey(form);
	}
	else if (nChar == VK_RIGHT) {
		return new RightArrowKey(form);
	}
	else if (nChar == VK_UP) {
		return new UpArrowKey(form);
	}
	else if (nChar == VK_DOWN) {
		return new DownArrowKey(form);
	}
	else if (nChar == VK_TAB) {
		return new TabKey(form);
	}
	else if (nChar == VK_RETURN) {
		return new ReturnKey(form);
	}
	else if (nChar == VK_BACK) {
		return new BackspaceKey(form);
	}
	else if (nChar == VK_DELETE) {
		return new DeleteKey(form);
	}
	else if (nChar == VK_HOME) {
		return new HomeKey(form);
	}
	else if (nChar == VK_END) {
		return new EndKey(form);
	}
	return 0;
}