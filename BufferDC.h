#pragma once

#ifndef _BUFFERDC_H
#define _BUFFERDC_H

#include <afxwin.h>

class BufferDC : public CDC {
public:
	BufferDC(CWnd* pParent);
	~BufferDC();
	BufferDC& operator = (const BufferDC& source);
protected:
	BOOL Attatch(HDC hDC);
	HDC Detach();
private:
	CWnd* m_pParent;
	CDC* m_pTarget;
	PAINTSTRUCT m_PaintStruct;
	CRect m_RcClient;
	CRect m_RcWindow;
	CDC m_MemoryDC;
	CBitmap m_MemoryBmp;
	CBitmap* m_pOldMemoryBmp;
};

#endif //_BUFFERDC_H