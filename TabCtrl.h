#pragma once
//TabCtrl.h

#ifndef _TABCTRL_H
#define _TABCTRL_H

#include <afxwin.h>
#include <afxcmn.h>
#include <Windows.h>
#include "resource1.h"
typedef signed long int Long;

class EditControl;
class TabCtrl :public CTabCtrl {
public:
	TabCtrl();
	~TabCtrl();
	TabCtrl(const TabCtrl& source);
	TabCtrl& operator=(const TabCtrl& source);
	//Long InsertItem(int nItem, LPCTSTR lpszItem);
	//Long InsertItem(int nItem);
	Long InsertItem(int nItem, CString name);
	void DrawTabItem();
	void UpdateItemName();
	CString GetItemName();
	EditControl* GetEditControl() const;
	afx_msg void OnDeletePageForm();
	afx_msg void OnChangeName();
protected:
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
//	afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnContextMenu(CWnd* pWnd, CPoint pos);
	afx_msg void OnCopyPageForm();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//afx_msg void OnDeletePageForm();
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnKillFocus(CWnd *pOldWnd);
	DECLARE_MESSAGE_MAP()
private:
	EditControl *editCtrl;
	Long selectedItem;
};

inline EditControl* TabCtrl::GetEditControl() const {
	return this->editCtrl;
}

#endif	//_TABCTRL_H