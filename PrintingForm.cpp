//PrintingForm.cpp

#include "PrintingForm.h"
#include "OtherNoteForm.h"
#include "Note.h"
#include "PageForm.h"
#include "Page.h"
#include "MemoForm.h"
#include "PaintVisitor.h"
#include "HighLightVisitor.h"

BEGIN_MESSAGE_MAP(PrintingForm, CPrintDialog)
	ON_WM_CREATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

PrintingForm::PrintingForm(BOOL bPrintSetupOnly, DWORD dwFlags, CWnd* pParentWnd) 
	:CPrintDialog(bPrintSetupOnly, dwFlags, pParentWnd){
	this->positionX = 0;
	this->positionY = 0;
	this->printWidth = A4WIDTH;
	this->printHeight = A4HEIGHT;
}

PrintingForm::~PrintingForm() {

}

int PrintingForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	//5. ���������� �޸� ��Ʈ������ ���� �����
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
	PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
	CRect pageWndRect;
	pageForm->GetWindowRect(&pageWndRect);
	//5.1. DC�����
	CDC *pDC = this->GetDC();
	//CDC bufferPageDC;
	this->bufferPageDC.CreateCompatibleDC(pDC);
	//5.2 �޸� ��Ʈ�� ����
	//CBitmap bufferPageBmp;	
	this->bufferPageBmp.CreateCompatibleBitmap(pDC, pageWndRect.Width(), pageWndRect.Height());
	//5.3. ���� ��Ʈ�� �����
	CBitmap *pOldBitmap = (CBitmap*)bufferPageDC.SelectObject(&this->bufferPageBmp);
	//5.4. ������ ���ߴ� �۾��ϱ�(���ĥ�ϱ�)
	CRect bgRect(0, 0, pageWndRect.Width(), pageWndRect.Height());
	this->bufferPageDC.FillSolidRect(bgRect, RGB(255, 255, 255));
	//5.5. �޸𰳼���ŭ �׸���.
	Long i = 0;
	while (i < pageForm->GetLength()) {
		MemoForm *memoForm = pageForm->GetMemoForm(i);
		Memo *memo = static_cast<Page*>(pageForm->GetContents())->GetMemo(i);
		CRect memoWndRect;
		memoForm->GetWindowRect(&memoWndRect);
		Long distanceFromPageX = memoWndRect.left - pageWndRect.left;
		Long distanceFromPageY = memoWndRect.top - pageWndRect.top;
		Long width = memoForm->GetMaxWidth();
		Long height = memoForm->GetMaxHeight();

		PaintVisitor paintVisitor(&this->bufferPageDC, &CRect(distanceFromPageX, distanceFromPageY, distanceFromPageX + width, distanceFromPageY + height));
		memo->Accept(&paintVisitor);

		HighLightVisitor highLightVisitor(&this->bufferPageDC, &CRect(distanceFromPageX, distanceFromPageY, distanceFromPageX + width, distanceFromPageY + height));
		memo->Accept(&highLightVisitor);
		i++;
	}
	return 0;
}

#include "HighLightVisitor.h"
void PrintingForm::OnPrint(CDC *pDC, CPrintInfo *pInfo) {
	//sample
	/*CRect rect(100, 100, 200, 200);
	pDC->FillSolidRect(&rect, RGB(120, 120, 120));*/

	/*CBitmap bufferPageBmp;
	CDC bufferPageDC;
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
	PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
	CRect pageWndRect;
	pageForm->GetWindowRect(&pageWndRect);

	bufferPageDC.CreateCompatibleDC(pDC);

	bufferPageBmp.CreateCompatibleBitmap(pDC, pageWndRect.Width(), pageWndRect.Height());

	CBitmap *pOldBitmap = (CBitmap*)bufferPageDC.SelectObject(&bufferPageBmp);
	CRect bgRect(0, 0, pageWndRect.Width(), pageWndRect.Height());
	bufferPageDC.FillSolidRect(bgRect, RGB(255, 255, 255));
	Long i = 0;
	while (i < pageForm->GetLength()) {
		MemoForm *memoForm = pageForm->GetMemoForm(i);
		Memo *memo = static_cast<Page*>(pageForm->GetContents())->GetMemo(i);
		CRect memoWndRect;
		memoForm->GetWindowRect(&memoWndRect);
		Long distanceFromPageX = memoWndRect.left - pageWndRect.left;
		Long distanceFromPageY = memoWndRect.top - pageWndRect.top;
		Long width = memoForm->GetMaxWidth();
		Long height = memoForm->GetMaxHeight();

		PaintVisitor paintVisitor(&bufferPageDC, &CRect(distanceFromPageX, distanceFromPageY, distanceFromPageX + width, distanceFromPageY + height));
		memo->Accept(&paintVisitor);

		HighLightVisitor highLightVisitor(&bufferPageDC, &CRect(distanceFromPageX, distanceFromPageY, distanceFromPageX + width, distanceFromPageY + height));
		memo->Accept(&highLightVisitor);
		i++;
	}*/

	pDC->SetMapMode(MM_LOMETRIC);//0.1mm 1cm = 100, 21cm = 2100
	//pDC->StretchBlt(0, 0, 2100, -2970, &this->bufferPageDC, 0, 0, 1190, 1683, SRCCOPY);
	pDC->StretchBlt(0, 0, 2100, -2970, &this->bufferPageDC, this->positionX, this->positionY, this->printWidth, this->printHeight, SRCCOPY);
}

void PrintingForm::Print() {
	//2. printer DC�� ����
	CDC dc;
	dc.Attach(this->GetPrinterDC());
	dc.m_bPrinting = TRUE;

	//3. �μ�� ��ť��Ʈ�� ���� ���� ����
	//DOCINFO docinfo;
	CString title;
	title.LoadString(AFX_IDS_APP_TITLE);

	//4. ��ť��Ʈ �μ� ����
	BOOL bPrintingOK = dc.StartDoc(title);

	//5. CprintInfo����
	CPrintInfo info;
	info.m_rectDraw.SetRect(0, 0, dc.GetDeviceCaps(HORZRES), dc.GetDeviceCaps(VERTRES));
	info.SetMaxPage(this->GetMaxPages());

	//6.
	UINT page = info.GetMinPage();
	while (page <= info.GetMaxPage() && bPrintingOK) {
		dc.StartPage();
		info.m_nCurPage = page;
		//OnPrint(&dc, &info);
		this->OnPrint(&dc, &info);

		//
		//2. ���������� ������ ���Ѵ�.
		//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
		OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
		PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
		CRect pageWndRect;
		pageForm->GetWindowRect(&pageWndRect);

		//3. �̸������� ������ ��Ʈ�ʿ��� ���ϰ� paper�� �ٽ� �׸���.
		if (this->positionX < pageWndRect.Width() && this->positionY < pageWndRect.Height()) {
			if (this->positionX + this->printWidth > pageWndRect.Width() && this->positionY + this->printHeight <= pageWndRect.Height()) {
				this->positionX = 0;
				this->positionY += this->printHeight;
			}
			else if (positionX + this->printWidth <= pageWndRect.Width()) {
				this->positionX += this->printWidth;
			}
		}
		//

		bPrintingOK = (dc.EndPage() > 0);
		page++;
	}

	if (bPrintingOK) {
		dc.EndDoc();
	}
	else {
		dc.AbortDoc();
	}

	dc.Detach();
}

void PrintingForm::OnClose() {
	//1010 �״� �̽� �߻�
	//�̸����⿡�� �ݰ� ���α׷� �����ϸ� �״��̽�
	//0xC000041D ���� �ڵ�
	CPrintDialog::OnClose();
	//CPrintDialog::EndDialog();
}

Long PrintingForm::GetMaxPages() {
	Long ret = 0;
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(FindWindow("OtherNote", NULL));
	PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
	CRect pageWndRect;
	pageForm->GetWindowRect(&pageWndRect);

	Long row = (pageWndRect.Width() / A4WIDTH) + 1;
	if (pageWndRect.Width() % A4WIDTH == 0) {
		row -= 1;
	}
	Long column = (pageWndRect.Height() / A4HEIGHT) + 1;
	if (pageWndRect.Height() % A4HEIGHT == 0) {
		column -= 1;
	}
	ret = row * column;
	
	return ret;
}