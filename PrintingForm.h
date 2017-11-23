//PrintingForm.h

#ifndef _PRINTINGFORM_H
#define _PRINTINGFORM_H

#define A4WIDTH 1190
#define A4HEIGHT 1683

#include <afxext.h>
typedef signed long int Long;

class PrintingForm : public CPrintDialog {
public:
	PrintingForm(BOOL bPrintSetupOnly,
		DWORD dwFlags = PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS
		| PD_HIDEPRINTTOFILE | PD_NOSELECTION,
		CWnd* pParentWnd = NULL);
	~PrintingForm();
	//PrintingForm(PrintingForm& source);
	CBitmap& GetBufferPageBmp() const;
	CDC& GetBufferPageDC() const;
	void OnPrint(CDC *pDC, CPrintInfo *pInfo);
	Long GetMaxPages();
	void Print();
	afx_msg void OnClose();
private:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
private:
	CBitmap bufferPageBmp;
	CDC bufferPageDC;
	Long positionX;
	Long positionY;
	Long printWidth;
	Long printHeight;
};

inline CBitmap& PrintingForm::GetBufferPageBmp() const {
	return const_cast<CBitmap&>(this->bufferPageBmp);
}

inline CDC& PrintingForm::GetBufferPageDC() const {
	return const_cast<CDC&>(this->bufferPageDC);
}

#endif //_PRINTINGFORM_H