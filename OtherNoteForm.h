//OtherNoteForm.h

#ifndef _OTHERNOTEFORM_H
#define _OTHERNOTEFORM_H

#include "resource1.h"
#include "CompositeForm.h"
#include "ArrayIterator.h"
#include "TabCtrl.h"
#include "NewFileDialog.h"
#include <afxwin.h>
#include <Windows.h>
//using namespace std;

class PrintingForm;
class PrintPreview;
class FindIndex;
class Contents;
class Form;
class PageForm;
class Visitor;
class Page;
class HorizontalScroll;
class VerticalScroll;
class FindingForm;
class OtherNoteForm :public CFrameWnd, public CompositeForm{
public:
	OtherNoteForm(Contents *contents = 0, Long capacity = 64);
	~OtherNoteForm();
	OtherNoteForm(const OtherNoteForm& source);
	OtherNoteForm& operator=(const OtherNoteForm& source);

	//Long AddPageForm(Page *page);
	Long AddPageForm(Page *page, CString pageFormName = "");
	Long AddPageForm(PageForm *pageForm);
	Long RemovePageForm(Long index);
	PageForm* GetPageForm(Long index);
	PageForm* operator[](Long index);

	virtual Form* Clone() const;
	virtual ArrayIterator<Form*>* CreateIterator() const;
	virtual void Accept(Visitor *visitor);

	//void Detach(Contents *contents);
	//void DisplayMemoForm(Long index);
	void SelectTabItem(Long index);

	TabCtrl* GetTabCtrl() const;

	void Load(LPTSTR lpstrFile);
	void Save(LPTSTR lpstrFile);
	CString& GetFileName() const;
	void SetFileName(CString& fileName);
	void ClearPageForms();
	//CFrameWnd* GetDocumentWnd() const;
	CWnd* GetDocumentWnd() const;
	HorizontalScroll* GetHorizontalScroll() const;
	VerticalScroll* GetVerticalScroll() const;
	FindingForm* SetFindingForm(FindingForm *findingForm);
	FindingForm* GetFindingForm() const;
	void ScrollToFindIndex(FindIndex *findIndex);
	void OnFilePrintPreview();
	void OnFilePrint();
	void Reset();
	Long GetDefaultMemoColor() const;
	void SetDefaultMemoColor(Long color);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	PrintingForm* GetPrintingForm() const;
	afx_msg void OnMenuSaveAs();
protected:
	//afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//afx_msg LRESULT OnImeComposition(WPARAM wParam, LPARAM lParam);
	//afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMenuNewFile();
	afx_msg void OnMenuExit();
	afx_msg void OnMenuOpen();
	afx_msg void OnMenuSave();
	afx_msg void OnMenuInformation();
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	
	afx_msg void OnMenuFindPage();
	afx_msg void OnMenuFindOtherNote();
	afx_msg LRESULT OnFind(WPARAM wParam, LPARAM lParam);

	afx_msg BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
	
private:
	TabCtrl *tabCtrl;
	CMenu menu;
	CString fileName;
	HorizontalScroll *horizontalScroll;
	VerticalScroll *verticalScroll;
	CWnd *documentWnd;
	FindingForm *findingForm;
	PrintPreview *printPreview;
	PrintingForm *printingForm;
	Long defaultMemoColor;

	HACCEL m_accelerators_key;
public:
	static UINT WM_FIND;
};

inline TabCtrl* OtherNoteForm::GetTabCtrl() const {
	return const_cast<TabCtrl*>(this->tabCtrl);
}

inline CString& OtherNoteForm::GetFileName() const {
	return const_cast<CString&>(this->fileName);
}

//inline CFrameWnd* OtherNoteForm::GetDocumentWnd() const {
//	return const_cast<CFrameWnd*>(this->documentWnd);
//}

inline CWnd* OtherNoteForm::GetDocumentWnd() const {
	return const_cast<CWnd*>(this->documentWnd);
}

inline HorizontalScroll* OtherNoteForm::GetHorizontalScroll() const {
	return const_cast<HorizontalScroll*>(this->horizontalScroll);
}

inline VerticalScroll* OtherNoteForm::GetVerticalScroll() const {
	return const_cast<VerticalScroll*>(this->verticalScroll);
}

inline FindingForm* OtherNoteForm::GetFindingForm() const {
	return const_cast<FindingForm*>(this->findingForm);
}

inline PrintingForm* OtherNoteForm::GetPrintingForm() const {
	return const_cast<PrintingForm*>(this->printingForm);
}

inline Long OtherNoteForm::GetDefaultMemoColor() const {
	return this->defaultMemoColor;
}

#endif	//_OTHERNOTEFORM_H