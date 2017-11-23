//NewFileDialog.h

#ifndef _NEWFILEDIALOG
#define _NEWFILEDIALOG
#include <afxwin.h>
#include "resource1.h"
class NewFileDialog : public CDialog {
public:
	NewFileDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	~NewFileDialog();
	virtual BOOL OnInitDialog();
private:
	afx_msg void OnOkButtonClicked();
	afx_msg void OnNoSaveButtonClicked();
	afx_msg void OnCancelButtonClicked();
	DECLARE_MESSAGE_MAP()
private:
	CString fileName;
};

#endif //_NEWFILEDIALOG