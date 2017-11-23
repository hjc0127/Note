//EditControl.h

#ifndef _EDITCONTROL_H
#define _EDITCONTROL_H

#include <afxwin.h>
typedef signed long int Long;

class EditControl : public CEdit {
public :
	EditControl();
	~EditControl();
	EditControl(const EditControl& source);
	EditControl& operator = (const EditControl& source);
private:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	DECLARE_MESSAGE_MAP()
};

#endif //_EDITCONTROL_H
