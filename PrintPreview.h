#pragma once
#ifndef _PRINTPREVIEW_H
#define _PRINTPREVIEW_H

#define PREVIEW_MARGIN_HEIGHT 15
#define PREVIEW_BUTTON_HEIGHT 50

#include <afxwin.h>

class PrintPreviewPaper;
class PrintPreview : public CFrameWnd {
public :
	PrintPreview();
	~PrintPreview();
	PrintPreview(const PrintPreview& source);
	PrintPreview& operator=(const PrintPreview& source);
	CBitmap& GetBufferPageBmp() const;
	CDC& GetBufferPageDC() const;
private:
	void CreateButtons(CRect buttonLayer);
	void SetMagnification();
	void CreateBitmapFromPageForm();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnPrintButtonClicked();
	afx_msg void OnNextButtonClicked();
	afx_msg void OnPreviousButtonClicked();
	afx_msg void OnCloseButtonClicked();
	DECLARE_MESSAGE_MAP()

private:
	PrintPreviewPaper *previewPaper;
	CBitmap bufferPageBmp;
	CDC bufferPageDC;
	double magnification;
	double a4Width;
	double a4Height;
	int systemCX;
	int systemCY;
	//버튼 추가
	CButton *printButton;
	CButton *nextButton;
	CButton *previousButton;
	CButton *closeButton;
};

inline CBitmap& PrintPreview::GetBufferPageBmp() const {
	return const_cast<CBitmap&>(this->bufferPageBmp);
}

inline CDC& PrintPreview::GetBufferPageDC() const {
	return const_cast<CDC&>(this->bufferPageDC);
}

#endif //_PRINTPREVIEW_H