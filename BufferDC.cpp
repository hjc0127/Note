//BufferDC.cpp

#include "BufferDC.h"

BufferDC::BufferDC(CWnd *pParent) 
	:m_pParent(pParent) {
	ASSERT(pParent);

	m_pTarget = m_pParent->BeginPaint(&m_PaintStruct);
	m_pParent->GetClientRect(&m_RcClient);
	m_pParent->GetWindowRect(&m_RcWindow);

	m_MemoryDC.CreateCompatibleDC(m_pTarget);
	m_MemoryBmp.CreateBitmap(m_RcClient.Width(), m_RcClient.Height(), m_MemoryDC.GetDeviceCaps(PLANES), m_MemoryDC.GetDeviceCaps(BITSPIXEL), 0);
	m_pOldMemoryBmp = m_MemoryDC.SelectObject(&m_MemoryBmp);

	Attach(m_MemoryDC);
}

BufferDC::~BufferDC() {
	m_pTarget->BitBlt(m_PaintStruct.rcPaint.left, m_PaintStruct.rcPaint.top, m_PaintStruct.rcPaint.right - m_PaintStruct.rcPaint.left, m_PaintStruct.rcPaint.bottom - m_PaintStruct.rcPaint.top, &m_MemoryDC, m_PaintStruct.rcPaint.left, m_PaintStruct.rcPaint.top, SRCCOPY);

	m_MemoryDC.SelectObject(m_pOldMemoryBmp);
	m_pParent->EndPaint(&m_PaintStruct);

	Detach();
}

BufferDC& BufferDC::operator = (const BufferDC& source) {
	return *this;
}

BOOL BufferDC::Attatch(HDC hDC) {
	return CDC::Attach(hDC);
}

HDC BufferDC::Detach() {
	return CDC::Detach();
}

