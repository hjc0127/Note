//MouseActionCreator.cpp

#include "MouseActionCreator.h"

MouseActionCreator::MouseActionCreator() {

}

MouseActionCreator::MouseActionCreator(const MouseActionCreator& source) {

}

MouseActionCreator::~MouseActionCreator() {

}

MouseActionCreator& MouseActionCreator::operator=(const MouseActionCreator& source) {
	return *this;
}

#include "MouseAction.h"
#include "MouseLButtonDown.h"
#include "MouseRButtonDown.h"
#include "MouseOnMove.h"
#include "PageFormMouseLButtonDown.h"
#include "MemoForm.h"
#include "PageForm.h"
#include "Form.h"
#include "OtherNoteFormMouseLButtonDblClk.h"
#include "FindingForm.h"
MouseAction* MouseActionCreator::Create(Form *form, UINT nFlags, CPoint point, Long message) {

	//1121 찾은 index 해제 하기
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	FindingForm *findingForm = otherNoteForm->GetFindingForm();
	if (findingForm != NULL) {
		findingForm->ResetIndexes();
	}

	if (dynamic_cast<MemoForm*>(form)) {
		if (message == WM_LBUTTONDOWN && nFlags == MK_LBUTTON) {
			return new MouseLButtonDown(form);
		}
		else if (message == WM_RBUTTONDOWN && nFlags == MK_RBUTTON) {
			return new MouseRButtonDown(form);
		}
		else if (message == WM_MOUSEMOVE && nFlags & MK_LBUTTON) {
			return new MouseOnMove(form);
		}
	}
	else if (dynamic_cast<PageForm*>(form)) {
		if (message == WM_LBUTTONDOWN && nFlags == MK_LBUTTON) {
			return new PageFormMouseLButtonDown(form);
		}
	}
	else if (dynamic_cast<OtherNoteForm*>(form)) {
		if (message == WM_LBUTTONDBLCLK && nFlags == MK_LBUTTON) {
			return new OtherNoteFormMouseLButtonDblClk(form);
		}
	}

	return 0;
}

#include "MouseMove.h"
MouseAction* MouseActionCreator::Create(Form *form, int x, int y, Long message) {
	return new MouseMove(form);
}

#include "OtherNoteForm.h"
#include "MouseScrollingToLeft.h"
#include "MouseScrollingToRight.h"
#include "MouseScrollingToBottom.h"
#include "MouseScrollingToTop.h"
#include "MouseMovingToLeft.h"
#include "MouseMovingToRight.h"
#include "MouseMovingToTop.h"
#include "MouseMovingToBottom.h"
MouseAction* MouseActionCreator::Create(Form *form, UINT nSide, LPRECT lpRect, Long message) {
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	
	//1. Moving : 별도로 분리가 필요함 0904
	CRect pageFormWndRect;
	static_cast<MemoForm*>(form)->GetParent()->GetWindowRect(&pageFormWndRect);
	if (lpRect->left <= pageFormWndRect.left) {
		return new MouseMovingToLeft(form);
	}
	if (lpRect->right > pageFormWndRect.right) {
		return new MouseMovingToRight(form);
	}
	if (lpRect->top <= pageFormWndRect.top) {
		return new MouseMovingToTop(form);
	}
	if (lpRect->bottom > pageFormWndRect.bottom) {
		return new MouseMovingToBottom(form);
	}

	//2. Scrolling
	CRect docWndRect;
	otherNoteForm->GetDocumentWnd()->GetWindowRect(&docWndRect);
	CPoint point;
	GetCursorPos(&point);
	if (point.x - 5 <= docWndRect.left) {
		return new MouseScrollingToLeft(form);
	}
	else if (point.x + 10 >= docWndRect.right) {
		return new MouseScrollingToRight(form);
	}	
	else if (point.y + 15 >= docWndRect.bottom) {
		return new MouseScrollingToBottom(form);
	}
	else if (point.y - 5 <= docWndRect.top) {
		return new MouseScrollingToTop(form);
	}
	return 0;
}

#include "TabCtrl.h"
#include "TabCtrlMouseLButtonDown.h"
#include "TabCtrlMouseRButtonDown.h"
#include "TabCtrlMouseLButtonDoubleClicked.h"
MouseAction* MouseActionCreator::Create(TabCtrl *tabCtrl, UINT nFlags, CPoint point, Long message) {
	if (nFlags == MK_LBUTTON && message == WM_LBUTTONDOWN) {
		return new TabCtrlMouseLButtonDown(tabCtrl);
	}
	else if (nFlags == MK_RBUTTON && message == WM_RBUTTONDOWN) {
		return new TabCtrlMouseRButtonDown(tabCtrl);
	}
	else if (nFlags == MK_LBUTTON && message == WM_LBUTTONDBLCLK) {
		//1121 찾은 index 해제 하기
		OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
		FindingForm *findingForm = otherNoteForm->GetFindingForm();
		if (findingForm != NULL) {
			findingForm->ResetIndexes();
		}

		return new TabCtrlMouseLButtonDoubleClicked(tabCtrl);
	}
	return 0;
}