#pragma once
//PageForm.h

#ifndef _PAGEFORM_H
#define _PAGEFORM_H

//#define PAGEFORM_MAX_WIDTH 32767
//#define PAGEFORM_MAX_HEIGHT 32767
#define PAGEFORM_MAX_WIDTH 4000
#define PAGEFORM_MAX_HEIGHT 4000

#include "CompositeForm.h"
#include "MemoForm.h"
#include <afxwin.h>
#include <string>
using namespace std;
typedef signed long int Long;

class Visitor;
class Contents;
class MemoForm;
class Memo;
class PageForm :public CWnd, public CompositeForm {
public:
	PageForm(Contents *contents=0,Long capacity = 64, string pageFormName = "");
	virtual ~PageForm();
	PageForm(const PageForm& source);
	PageForm& operator=(const PageForm& source);
	//Long AddMemoForm(Memo *memo);
	//Long AddMemoForm(Memo *memo, CPoint point);
	//Long AddMemoForm(Memo *memo, CRect rect);
	Long AddMemoForm(Memo *memo, CRect rect, Long color = -1);
	Long AddMemoForm(MemoForm *memoForm);
	Long RemoveMemoForm(Long index);
	MemoForm* GetMemoForm(Long index);
	MemoForm* operator[](Long index);
	string& GetPageFormName() const;
	//void SetPageFormName(const string& pageFormName);
	void SetPageFormName(string pageFormName);
	virtual Form* Clone() const;
	virtual void Accept(Visitor* visitor);
	virtual ArrayIterator<Form*>* CreateIterator() const;
	afx_msg void OnClose();
	bool CleanUpMemoForms();
	void SetHScrinfo(SCROLLINFO hScrinfo);
	void SetVScrinfo(SCROLLINFO vScrinfo);
	SCROLLINFO GetHScrinfo() const;
	SCROLLINFO GetVScrinfo() const;
	void UpdateScrinfo();
	void ResizeWindow(Long width, Long height);
	void UpdateSize(MemoForm* memoForm);
	void OnEraseFindIndexes();
	void UpdatePageForm();
	MemoForm* GetFocusedMemo() const;
	MemoForm* GetHoveredMemo() const;
	void FocusMemo(MemoForm *memoForm);
	void HoverMemo(MemoForm *memoForm);
	void Redraw();
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//afx_msg void OnSize(UINT nType, int cx, int cy);
	//afx_msg void OnSelChanging();
	//afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

private:
	string pageFormName;
	SCROLLINFO hScrinfo;
	SCROLLINFO vScrinfo;
	MemoForm *focusedMemo;
	MemoForm *hoveredMemo;
};

inline string& PageForm::GetPageFormName() const {
	return const_cast<string&>(this->pageFormName);
}

inline SCROLLINFO PageForm::GetHScrinfo() const {
	return this->hScrinfo;
}

inline SCROLLINFO PageForm::GetVScrinfo() const {
	return this->vScrinfo;
}

inline MemoForm* PageForm::GetFocusedMemo() const {
	return const_cast<MemoForm*>(this->focusedMemo);
}

inline MemoForm* PageForm::GetHoveredMemo() const {
	return const_cast<MemoForm*>(this->hoveredMemo);
}

//inline void PageForm::SetPageFormName(const string& pageFormName) {
//	this->pageFormName = pageFormName;
//}
#endif	//_MEMO_H