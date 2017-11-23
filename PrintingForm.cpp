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
	//5. 페이지폼을 메모리 비트맵으로 한장 만들기
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
	PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
	CRect pageWndRect;
	pageForm->GetWindowRect(&pageWndRect);
	//5.1. DC만들기
	CDC *pDC = this->GetDC();
	//CDC bufferPageDC;
	this->bufferPageDC.CreateCompatibleDC(pDC);
	//5.2 메모리 비트맵 생성
	//CBitmap bufferPageBmp;	
	this->bufferPageBmp.CreateCompatibleBitmap(pDC, pageWndRect.Width(), pageWndRect.Height());
	//5.3. 예전 비트맵 만들기
	CBitmap *pOldBitmap = (CBitmap*)bufferPageDC.SelectObject(&this->bufferPageBmp);
	//5.4. 페이지 본뜨는 작업하기(배경칠하기)
	CRect bgRect(0, 0, pageWndRect.Width(), pageWndRect.Height());
	this->bufferPageDC.FillSolidRect(bgRect, RGB(255, 255, 255));
	//5.5. 메모개수만큼 그린다.
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
	//2. printer DC를 얻음
	CDC dc;
	dc.Attach(this->GetPrinterDC());
	dc.m_bPrinting = TRUE;

	//3. 인쇄될 도큐먼트에 관한 정보 설정
	//DOCINFO docinfo;
	CString title;
	title.LoadString(AFX_IDS_APP_TITLE);

	//4. 토큐먼트 인쇄 시작
	BOOL bPrintingOK = dc.StartDoc(title);

	//5. CprintInfo설정
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
		//2. 페이지폼의 영역을 구한다.
		//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
		OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
		PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
		CRect pageWndRect;
		pageForm->GetWindowRect(&pageWndRect);

		//3. 미리보기할 영역을 비트맵에서 구하고 paper를 다시 그린다.
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
	//1010 죽는 이슈 발생
	//미리보기에서 닫고 프로그램 종료하면 죽는이슈
	//0xC000041D 에러 코드
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