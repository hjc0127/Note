//PrintPreviewPaper.cpp

#include "PrintPreviewPaper.h"
#include "OtherNoteForm.h"
#include "PageForm.h"
#include "Note.h"
#include "PrintPreview.h"

BEGIN_MESSAGE_MAP(PrintPreviewPaper, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

PrintPreviewPaper::PrintPreviewPaper(Long paperWidth, Long paperHeight, Long previewWidth, Long previewHeight) {
	this->positionX = 0;
	this->positionY = 0;
	this->paperWidth = paperWidth;
	this->paperHeight = paperHeight;
	this->previewWidth = previewWidth;
	this->previewHeight = previewHeight;
}

PrintPreviewPaper::~PrintPreviewPaper() {
	//printf("%s", "�Ҹ���");
}

PrintPreviewPaper::PrintPreviewPaper(const PrintPreviewPaper& source) {
	this->positionX = 0;
	this->positionY = 0;
	this->paperWidth = source.paperWidth;
	this->paperHeight = source.paperHeight;
	this->previewWidth = source.previewWidth;
	this->previewHeight = source.previewHeight;
}

PrintPreviewPaper& PrintPreviewPaper::operator=(const PrintPreviewPaper& source) {
	this->positionX = 0;
	this->positionY = 0;
	this->paperWidth = source.paperWidth;
	this->paperHeight = source.paperHeight;
	this->previewWidth = source.previewWidth;
	this->previewHeight = source.previewHeight;
	return *this;
}

int PrintPreviewPaper::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	//1. ������������ OnCreate ȣ��
	CFrameWnd::OnCreate(lpCreateStruct);

	//2. ���������� �̸����� ���̸� �ٽ� �׸���.
	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

	//3. �����Ѵ�.
	return 0;
}

void PrintPreviewPaper::OnClose() {
	CFrameWnd::OnClose();
}

//#include "OtherNoteForm.h"
//#include "PageForm.h"
//#include "Note.h"
//void PrintPreviewPaper::OnPaint() {
//	CFrameWnd::OnPaint();
//		
//	//������	
//	/*CRect rect;
//	GetClientRect(&rect);*/
//
//	CClientDC paperDC(this);
//	//paperDC.SetMapMode(MM_LOMETRIC);
//	//paperDC.SetMapMode(MM_HIMETRIC);
//
//	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
//	CClientDC noteForm(otherNoteForm);
//	//PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
//	//CClientDC noteForm(pageForm);
//	//noteForm.SetMapMode(MM_HIMETRIC);
//
//	//paperDC.BitBlt(0, 0, rect.Width(), rect.Height(), &noteForm, 0, 0, SRCCOPY);
//	//paperDC.StretchBlt(0, 0, rect.Width(), rect.Height(), &noteForm, 0, 0, 1000, 1000, SRCCOPY);
//	CDC *pDC = CWnd::GetDC();
//	Long xDPI = pDC->GetDeviceCaps(LOGPIXELSX);	//144
//	Long yDPI = pDC->GetDeviceCaps(LOGPIXELSY);	//144
//
//	/*Long xDPI = GetSystemMetrics(SM_CXSCREEN);
//	Long yDPI = GetSystemMetrics(SM_CYSCREEN);*/
//
//	Long width = paperDC.GetDeviceCaps(HORZSIZE);	//252
//	Long height = paperDC.GetDeviceCaps(VERTSIZE);	//168
//
//	Long a4Width = (8.267 * xDPI) / 1;		//1190
//	Long a4Height = (11.692 * yDPI) / 1;	//1683
//	//Long a4Width = (Long)((8.267 * xDPI) / 96.0f);		//1190
//	//Long a4Height = (Long)((11.692 * yDPI) / 96.0f);	//1683
//
//	//paperDC.StretchBlt(0, 0, paperDC.GetDeviceCaps(HORZSIZE)*100, -paperDC.GetDeviceCaps(VERTSIZE)*100, &noteForm, 0, 0, 2000, 1000, SRCCOPY);
//	//paperDC.StretchBlt(0, 0, 110 * 100, -149 * 100, &noteForm, 0, 0, a4Width, a4Height, SRCCOPY);
//	//paperDC.StretchBlt(0, 0, paperDC.GetDeviceCaps(VERTSIZE) * 60, -paperDC.GetDeviceCaps(HORZSIZE) * 60, &noteForm, 0, 0, 21000, -29700, SRCCOPY);
//	//paperDC.StretchBlt(0, 0, 21000, -29700, &noteForm, 0, 0, 1190, 1683, SRCCOPY);
//	//paperDC.StretchBlt(0, 0, 21000, -29700, &noteForm, 0, 0, 2160-20, 1357, SRCCOPY);
//	//paperDC.StretchBlt(0, 0, 210*40, -297*40, &noteForm, 0, 0, a4Width, a4Height, SRCCOPY);
//	//paperDC.StretchBlt(0, 0, 833*10, -1178*10, &noteForm, 0, 0, a4Width, a4Height, SRCCOPY);
//	paperDC.StretchBlt(0, 0, 833, 1178 , &noteForm, 0, 0, a4Width, a4Height, SRCCOPY);
//
//	/*OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
//	CClientDC noteDC(otherNoteForm);
//	CRect noteRect;
//	otherNoteForm->GetClientRect(&noteRect);
//
//	CClientDC previewDC(this);
//	previewDC.SetMapMode(MM_HIMETRIC);
//
//	previewDC.StretchBlt(0, 0, previewDC.GetDeviceCaps(HORZSIZE), previewDC.GetDeviceCaps(VERTSIZE), &noteDC, 0, 0, 21000, -29700, SRCCOPY);*/
//	
//}

void PrintPreviewPaper::OnPaint() {
	CFrameWnd::OnPaint();

	//CClientDC paperDC(this);
	/*OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
	CClientDC noteForm(otherNoteForm);*/
	//CDC *pDC = CWnd::GetDC();
	//Long xDPI = pDC->GetDeviceCaps(LOGPIXELSX);	//144
	//Long yDPI = pDC->GetDeviceCaps(LOGPIXELSY);	//144
	//Long width = paperDC.GetDeviceCaps(HORZSIZE);	//252
	//Long height = paperDC.GetDeviceCaps(VERTSIZE);	//168

	//Long a4Width = (8.267 * xDPI) / 1;		//1190
	//Long a4Height = (11.692 * yDPI) / 1;	//1683

	//this->positionX = a4Width;
	//this->positionY = a4Height;

	//paperDC.StretchBlt(0, 0, 833, 1178, &static_cast<PrintPreview*>(this->GetParent())->GetBufferPageDC(), 0, 0, a4Width, a4Height, SRCCOPY);
	//paperDC.StretchBlt(0, 0, 833, 1178, &static_cast<PrintPreview*>(this->GetParent())->GetBufferPageDC(), this->positionX, this->positionY, A4WIDTH, A4HEIGHT, SRCCOPY);
	
	//1006
	//CClientDC paperDC(this);
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
	//PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
	//CRect pageWndRect;
	//pageForm->GetWindowRect(&pageWndRect);

	////
	//this->positionX = pageWndRect.left;
	////this->positionY = pageWndRect.top;
	////

	//if (this->positionX < pageWndRect.right && this->positionY < pageWndRect.bottom) {
	//	paperDC.StretchBlt(0, 0, 833, 1178, &static_cast<PrintPreview*>(this->GetParent())->GetBufferPageDC(), this->positionX, this->positionY, this->paperWidth, this->paperHeight, SRCCOPY);
	//	if (this->positionX + this->paperWidth > pageWndRect.right && this->positionY + this->paperHeight < pageWndRect.bottom) {
	//		this->positionX = 0;
	//		this->positionY += this->paperHeight;
	//	}
	//	//else if (positionX + this->paperWidth < pageWndRect.right && positionY + this->paperHeight < pageWndRect.bottom) {
	//	else if (positionX + this->paperWidth < pageWndRect.right) {
	//		this->positionX += this->paperWidth;
	//	}
	//}
	//1006

	//1. Ŭ���̾�Ʈ DC�� ���Ѵ�.
	CClientDC paperDC(this);

	//2. ���������� a4ũ�⸸ŭ �̸�����â�� �׸���.
	paperDC.StretchBlt(0, 0, this->previewWidth, this->previewHeight, &static_cast<PrintPreview*>(this->GetParent())->GetBufferPageDC(), this->positionX, this->positionY, this->paperWidth, this->paperHeight, SRCCOPY);
}

////1�������� ���� ������ �ڵ� 0929
//#include "OtherNoteForm.h"
//#include "PageForm.h"
//#include "Note.h"
//void PrintPreviewPaper::OnPaint() {
//	CFrameWnd::OnPaint();
//	CClientDC paperDC(this);
//	
//	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
//	CClientDC noteForm(otherNoteForm);
//	
//	CDC *pDC = CWnd::GetDC();
//	Long xDPI = pDC->GetDeviceCaps(LOGPIXELSX);	//144
//	Long yDPI = pDC->GetDeviceCaps(LOGPIXELSY);	//144
//
//	Long width = paperDC.GetDeviceCaps(HORZSIZE);	//252
//	Long height = paperDC.GetDeviceCaps(VERTSIZE);	//168
//
//	Long a4Width = (8.267 * xDPI) / 1;		//1190
//	Long a4Height = (11.692 * yDPI) / 1;	//1683
//	paperDC.StretchBlt(0, 0, 833, 1178, &noteForm, 0, 0, a4Width, a4Height, SRCCOPY);
//
//}

void PrintPreviewPaper::moveNextPaper() {
	//1. DC�� ���Ѵ�.
	CClientDC paperDC(this);

	//2. ���������� ������ ���Ѵ�.
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
	PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
	CRect pageWndRect;
	pageForm->GetWindowRect(&pageWndRect);
	
	//3. �̸������� ������ ��Ʈ�ʿ��� ���ϰ� paper�� �ٽ� �׸���.
	if (this->positionX < pageWndRect.Width() && this->positionY < pageWndRect.Height()) {
		if (this->positionX + this->paperWidth > pageWndRect.Width() && this->positionY + this->paperHeight <= pageWndRect.Height()) {
			this->positionX = 0;
			this->positionY += this->paperHeight;
		}
		else if (positionX + this->paperWidth <= pageWndRect.Width()) {
			this->positionX += this->paperWidth;
		}
		paperDC.StretchBlt(0, 0, this->previewWidth, this->previewHeight, &static_cast<PrintPreview*>(this->GetParent())->GetBufferPageDC(), this->positionX, this->positionY, this->paperWidth, this->paperHeight, SRCCOPY);
		
		this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	}
}

void PrintPreviewPaper::movePreviousPaper() {
	//1. DC�� ���Ѵ�.
	CClientDC paperDC(this);
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));

	//2. �������� ������ ���Ѵ�.
	PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
	CRect pageWndRect;
	pageForm->GetWindowRect(&pageWndRect);

	//3. �̸������� ������ ��Ʈ�ʿ��� ���ϰ� paper�� �ٽ� �׸���.
	if (this->positionX >= 0 && this->positionY >= 0) {
		if (this->positionX == 0 && this->positionY - this->paperHeight >= 0) {
			this->positionX = (pageWndRect.Width() / A4WIDTH) * A4WIDTH;
			this->positionY -= this->paperHeight;
		}
		else if (this->positionX - this->paperWidth >= 0) {
			this->positionX -= this->paperWidth;
		}
		paperDC.StretchBlt(0, 0, this->previewWidth, this->previewHeight, &static_cast<PrintPreview*>(this->GetParent())->GetBufferPageDC(), this->positionX, this->positionY, this->paperWidth, this->paperHeight, SRCCOPY);
		
		this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	}
}