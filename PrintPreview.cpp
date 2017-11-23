//PrintPreview.c

#include "PrintPreview.h"
#include "PrintPreviewPaper.h"
#include "OtherNoteForm.h"
#include "Note.h"
#include "PageForm.h"
#include "Page.h"
#include "MemoForm.h"
#include "Memo.h"
#include "PaintVisitor.h"
#include "HighLightVisitor.h"

#define PRINT_PREVIEW_PRINT_BUTTON 20001
#define PRINT_PREVIEW_PREVIOUS_BUTTON 20002
#define PRINT_PREVIEW_NEXT_BUTTON 20003
#define PRINT_PREVIEW_CLOSE_BUTTON 20004

BEGIN_MESSAGE_MAP(PrintPreview, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_BN_CLICKED(PRINT_PREVIEW_PREVIOUS_BUTTON, OnPreviousButtonClicked)
	ON_BN_CLICKED(PRINT_PREVIEW_NEXT_BUTTON, OnNextButtonClicked)
	ON_BN_CLICKED(PRINT_PREVIEW_CLOSE_BUTTON, OnCloseButtonClicked)
	ON_BN_CLICKED(PRINT_PREVIEW_PRINT_BUTTON, OnPrintButtonClicked)
END_MESSAGE_MAP()

PrintPreview::PrintPreview(){
	this->previewPaper = new PrintPreviewPaper;
	this->printButton = new CButton;
	this->previousButton = new CButton;
	this->nextButton = new CButton;
	this->closeButton = new CButton;
	this->systemCX = GetSystemMetrics(SM_CXFULLSCREEN);	//2160
	this->systemCY = GetSystemMetrics(SM_CYFULLSCREEN);	//1357
	this->a4Width = 0; //(8.267f * xDPI);	//1190
	this->a4Height = 0; //(11.692f * yDPI);	//1683
}

PrintPreview::~PrintPreview() {
	if (this->printButton != 0) {
		delete this->printButton;
	}
	if (this->previousButton != 0) {
		delete this->previousButton;
	}
	if (this->nextButton != 0) {
		delete this->nextButton;
	}
	if (this->closeButton != 0) {
		delete this->closeButton;
	}
	/*if (this->previewPaper != 0) {
		delete this->previewPaper;
	}*/
}

PrintPreview::PrintPreview(const PrintPreview& source) {
	this->previewPaper = source.previewPaper;
	this->printButton = new CButton;
	this->previousButton = new CButton;
	this->nextButton = new CButton;	
	this->closeButton = new CButton;

	this->systemCX = source.systemCX;
	this->systemCY = source.systemCY;
	this->a4Width = source.a4Width;
	this->a4Height = source.a4Height;
}

PrintPreview& PrintPreview::operator=(const PrintPreview& source) {
	this->previewPaper = source.previewPaper;
	this->printButton = new CButton;
	this->previousButton = new CButton;
	this->nextButton = new CButton;
	this->closeButton = new CButton;

	this->systemCX = source.systemCX;
	this->systemCY = source.systemCY;
	this->a4Width = source.a4Width;
	this->a4Height = source.a4Height;
	return *this;
}

//int PrintPreview::OnCreate(LPCREATESTRUCT lpCreateStruct) {
//	CFrameWnd::OnCreate(lpCreateStruct);
//
//	/*CRect printClientRect;
//	this->GetClientRect(&printClientRect);*/
//
//	//0. 버튼 생성
//	/*this->printButton->Create(_T("인쇄"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(10, 0, 100, 30), this, PRINT_PREVIEW_PRINT_BUTTON);
//	this->previousButton->Create(_T("이전"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(110, 0, 200, 30), this, PRINT_PREVIEW_PREVIOUS_BUTTON);
//	this->nextButton->Create(_T("다음"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(210, 0, 300, 30), this, PRINT_PREVIEW_NEXT_BUTTON);
//	this->closeButton->Create(_T("닫기"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(310, 0, 400, 30), this, PRINT_PREVIEW_CLOSE_BUTTON);*/
//	
//	//1. 배율 정하기
//	double magnification = 0.7;
//	
//	//2. 모니터사이즈 구하기
//	int systemCX = GetSystemMetrics(SM_CXFULLSCREEN);	//2160
//	int systemCY = GetSystemMetrics(SM_CYFULLSCREEN);	//1357
//	
//	//1010
//	CDC *pDC = CWnd::GetDC();
//	Long xDPI = pDC->GetDeviceCaps(LOGPIXELSX);	//144
//	Long yDPI = pDC->GetDeviceCaps(LOGPIXELSY);	//144
//	
//	//Long a4Width = (8.267 * xDPI);		//1190
//	//Long a4Height = (11.692 * yDPI);	//1683
//	double a4Width = (8.267 * xDPI);		//1190
//	double a4Height = (11.692 * yDPI);	//1683
//	//1010
//
//	//3. 종이 사이즈 정하기
//	CRect paperRect(300, 300, 1190, 1683);
//	//paperRect.left = (int)(systemCX / 2 - (1190 * magnification) / 2);	//663
//	//paperRect.right = (int)(paperRect.left + (1190 * magnification));	//1496
//	//paperRect.top = (int)(systemCY / 2 - (1683 * magnification) / 2);	//88
//	//paperRect.bottom = (int)(paperRect.top + (1683 * magnification));	//1226
//	paperRect.left = (int)(systemCX / 2 - (a4Width * magnification) / 2);	//663
//	paperRect.right = (int)(paperRect.left + (a4Width * magnification));	//1496
//	paperRect.top = (int)(systemCY / 2 - (a4Height * magnification) / 2);	//88
//	paperRect.bottom = (int)(paperRect.top + (a4Height * magnification));	//1226
//	//paperRect(663, 88, 1496, 1266) [833 * 1178]
//
//	//4. 종이 윈도우 생성하기
//	CString strMyClass = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW, NULL, (HBRUSH)GetStockObject(WHITE_BRUSH), NULL);
//	this->previewPaper->CreateEx(0, strMyClass, "paper", WS_BORDER | WS_CHILD | WS_VISIBLE, paperRect, this , 0, NULL);
//	
//	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
//
//	//5. 페이지폼을 메모리 비트맵으로 한장 만들기
//	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
//	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
//	PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
//	CRect pageWndRect;
//	pageForm->GetWindowRect(&pageWndRect);
//	//5.1. DC만들기
//	//CDC *pDC = this->GetDC();
//	pDC = this->GetDC();
//	//CDC bufferPageDC;
//	bufferPageDC.CreateCompatibleDC(pDC);
//	//5.2 메모리 비트맵 생성
//	//CBitmap bufferPageBmp;	
//	bufferPageBmp.CreateCompatibleBitmap(pDC, pageWndRect.Width(), pageWndRect.Height());
//	//5.3. 예전 비트맵 만들기
//	CBitmap *pOldBitmap = (CBitmap*)bufferPageDC.SelectObject(&bufferPageBmp);
//	//5.4. 페이지 본뜨는 작업하기(배경칠하기)
//	CRect bgRect(0, 0, pageWndRect.Width(), pageWndRect.Height());
//	bufferPageDC.FillSolidRect(bgRect, RGB(255, 255, 255));
//	//5.5. 메모개수만큼 그린다.
//	Long i = 0;
//	while (i < pageForm->GetLength()) {
//		MemoForm *memoForm = pageForm->GetMemoForm(i);
//		Memo *memo = static_cast<Page*>(pageForm->GetContents())->GetMemo(i);
//		CRect memoWndRect;
//		memoForm->GetWindowRect(&memoWndRect);
//		Long distanceFromPageX = memoWndRect.left - pageWndRect.left;
//		Long distanceFromPageY = memoWndRect.top - pageWndRect.top;
//		Long width = memoForm->GetMaxWidth();
//		Long height = memoForm->GetMaxHeight();
//
//		PaintVisitor paintVisitor(&bufferPageDC, &CRect(distanceFromPageX, distanceFromPageY, distanceFromPageX + width, distanceFromPageY + height));
//		memo->Accept(&paintVisitor);
//
//		HighLightVisitor highLightVisitor(&bufferPageDC, &CRect(distanceFromPageX, distanceFromPageY, distanceFromPageX + width, distanceFromPageY + height));
//		memo->Accept(&highLightVisitor);
//		i++;
//	}
//
//	//5.6. DC복원
//	//bufferPageDC.SelectObject(pOldBitmap);
//
//	//6. button
//	Long buttonWidth = (Long)((paperRect.right - paperRect.left) / 5);	//176
//	Long buttonHeight = 50;
//	Long buttonMargin = (Long)(buttonWidth / 3);	//43
//	Long buttonLeft = paperRect.left;
//	Long buttonRight = buttonLeft + buttonWidth;
//	Long buttonTop = (paperRect.top / 2) - (buttonHeight / 2);
//
//	this->printButton->Create(_T("인쇄"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(buttonLeft, buttonTop, buttonRight, buttonTop + buttonHeight), this, PRINT_PREVIEW_PRINT_BUTTON);
//	buttonLeft = buttonLeft + buttonWidth + buttonMargin;
//	buttonRight = buttonLeft + buttonWidth;
//	this->previousButton->Create(_T("이전"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(buttonLeft, buttonTop, buttonRight, buttonTop + buttonHeight), this, PRINT_PREVIEW_PREVIOUS_BUTTON);
//	buttonLeft = buttonLeft + buttonWidth + buttonMargin;
//	buttonRight = buttonLeft + buttonWidth;
//	this->nextButton->Create(_T("다음"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(buttonLeft, buttonTop, buttonRight, buttonTop + buttonHeight), this, PRINT_PREVIEW_NEXT_BUTTON);
//	buttonLeft = buttonLeft + buttonWidth + buttonMargin;
//	buttonRight = buttonLeft + buttonWidth;
//	this->closeButton->Create(_T("닫기"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(buttonLeft, buttonTop, buttonRight, buttonTop + buttonHeight), this, PRINT_PREVIEW_CLOSE_BUTTON);
//
//	//7. 끝내기
//	return 0;
//}

//PrintPrivew 다시 구현 10/30
int PrintPreview::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct);

	//1. DPI 구하기
	CDC *pDC = CWnd::GetDC();
	Long xDPI = pDC->GetDeviceCaps(LOGPIXELSX);	//144
	Long yDPI = pDC->GetDeviceCaps(LOGPIXELSY);	//144
	this->a4Width = (8.267 * xDPI);	//1190
	this->a4Height = (11.692 * yDPI);	//1683

	//2. magnification
	this->SetMagnification();

	//3. left, right 구하기
	Long left = (Long)(this->systemCX / 2 - (this->a4Width * this->magnification) / 2);
	Long right = left + (Long)(this->a4Width * this->magnification);

	//4. buttonLayer 설정
	CRect buttonLayer(left, 0, right, PREVIEW_MARGIN_HEIGHT * 2 + PREVIEW_BUTTON_HEIGHT);
	
	//5. button 설정
	this->CreateButtons(buttonLayer);

	//6. PaperLayer 설정
	CRect paperLayer(left, buttonLayer.bottom, right, this->systemCY - PREVIEW_MARGIN_HEIGHT);

	//7. paper 윈도우 만들기
	Long paperBottom = (int)(paperLayer.top + (this->a4Height * this->magnification));
	CRect paperRect(paperLayer.left, paperLayer.top, paperLayer.right, paperBottom);
	CString strMyClass = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW, NULL, (HBRUSH)GetStockObject(WHITE_BRUSH), NULL);
	this->previewPaper->CreateEx(0, strMyClass, "paper", WS_BORDER | WS_CHILD | WS_VISIBLE, paperRect, this, 0, NULL);

	//8. 페이지폼을 메모리 비트맵으로 한장 만들기
	this->CreateBitmapFromPageForm();

	//9. 화면에 그리기
	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);

	//10. 끝내기
	return 0;
}

void PrintPreview::CreateBitmapFromPageForm() {
	//8.2. 페이지폼을 메모리 비트맵으로 한장 만들기
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
	PageForm *pageForm = otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent());
	CRect pageWndRect;
	pageForm->GetWindowRect(&pageWndRect);
	//8.2.1. DC만들기
	CDC *pDC = this->GetDC();
	//pDC = this->GetDC();
	//CDC bufferPageDC;
	this->bufferPageDC.CreateCompatibleDC(pDC);
	//8.2.2 메모리 비트맵 생성
	//CBitmap bufferPageBmp;	
	this->bufferPageBmp.CreateCompatibleBitmap(pDC, pageWndRect.Width(), pageWndRect.Height());
	//8.2.3. 예전 비트맵 만들기
	CBitmap *pOldBitmap = (CBitmap*)this->bufferPageDC.SelectObject(&this->bufferPageBmp);
	//8.2.4. 페이지 본뜨는 작업하기(배경칠하기)
	CRect bgRect(0, 0, pageWndRect.Width(), pageWndRect.Height());
	this->bufferPageDC.FillSolidRect(bgRect, RGB(255, 255, 255));
	//8.2.5. 메모개수만큼 그린다.
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
}

void PrintPreview::CreateButtons(CRect buttonLayer) {
	//1. 버튼 생성 정보를 생성한다.
	Long buttonWidth = (Long)((buttonLayer.right - buttonLayer.left) / 5);
	Long buttonHeight = PREVIEW_BUTTON_HEIGHT;
	Long buttonMargin = (Long)(buttonWidth / 3);
	Long buttonLeft = buttonLayer.left;
	Long buttonRight = buttonLeft + buttonWidth;
	Long buttonTop = buttonLayer.top + PREVIEW_MARGIN_HEIGHT;

	//2. 버튼들을 생성한다.
	this->printButton->Create(_T("인쇄"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(buttonLeft, buttonTop, buttonRight, buttonTop + buttonHeight), this, PRINT_PREVIEW_PRINT_BUTTON);
	buttonLeft = buttonLeft + buttonWidth + buttonMargin;
	buttonRight = buttonLeft + buttonWidth;
	this->previousButton->Create(_T("이전"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(buttonLeft, buttonTop, buttonRight, buttonTop + buttonHeight), this, PRINT_PREVIEW_PREVIOUS_BUTTON);
	buttonLeft = buttonLeft + buttonWidth + buttonMargin;
	buttonRight = buttonLeft + buttonWidth;
	this->nextButton->Create(_T("다음"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(buttonLeft, buttonTop, buttonRight, buttonTop + buttonHeight), this, PRINT_PREVIEW_NEXT_BUTTON);
	buttonLeft = buttonLeft + buttonWidth + buttonMargin;
	buttonRight = buttonLeft + buttonWidth;
	this->closeButton->Create(_T("닫기"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(buttonLeft, buttonTop, buttonRight, buttonTop + buttonHeight), this, PRINT_PREVIEW_CLOSE_BUTTON);
}

void PrintPreview::SetMagnification() {
	double magnificationX = this->systemCX / this->a4Width;
	double magnificationY = (this->systemCY - (PREVIEW_MARGIN_HEIGHT * 2 + PREVIEW_BUTTON_HEIGHT) - PREVIEW_MARGIN_HEIGHT) / this->a4Height;
	this->magnification = 0.0f;
	if (magnificationX > magnificationY) {
		this->magnification = magnificationY;
	}
	else {
		this->magnification = magnificationX;
	}
}

void PrintPreview::OnClose() {
	/*if (this->printButton != 0) {
		delete this->printButton;
	}
	if (this->previousButton != 0) {
		delete this->previousButton;
	}
	if (this->nextButton != 0) {
		delete this->nextButton;
	}
	if (this->closeButton != 0) {
		delete this->closeButton;
	}*/
	if (this->previewPaper != 0) {
		this->previewPaper->OnClose();
	}
	CFrameWnd::OnClose();
}

void PrintPreview::OnPrintButtonClicked() {
	//Todo 1008
	this->OnClose();
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(FindWindow("OtherNote", NULL));
	otherNoteForm->OnFilePrint();
}

void PrintPreview::OnPreviousButtonClicked() {
	this->previewPaper->movePreviousPaper();
}

void PrintPreview::OnNextButtonClicked() {
	this->previewPaper->moveNextPaper();
}

void PrintPreview::OnCloseButtonClicked() {
	//delete this;
	this->OnClose();
}

void PrintPreview::OnPaint() {
	CFrameWnd::OnPaint();

	////2. 해당 윈도우에 페이지를 그린다.
	//CClientDC previewDC(this);

	//CDC bufferDC;
	//bufferDC.CreateCompatibleDC(&previewDC);

	//CBitmap bmpBuffer;
	//bmpBuffer.CreateCompatibleBitmap(&previewDC, 200, 200);

	//CBitmap *pOldBitmap = (CBitmap*)bufferDC.SelectObject(&bmpBuffer);

	//bufferDC.Rectangle(0, 0, 200, 200);
	//(&previewDC)->BitBlt(0, 0, 200, 200, &bufferDC, 0, 0, SRCCOPY);

	//bufferDC.SelectObject(pOldBitmap);

	//CRect rect;
	//GetClientRect(&rect);
	//CClientDC previewDC(this);

	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
	//CClientDC noteDC(otherNoteForm);
	//CRect noteRect;
	//otherNoteForm->GetClientRect(&noteRect);
	//CClientDC boardDC(this->previewBoard);
	//boardDC.SetMapMode(MM_HIMETRIC);


	////noteDC.SetMapMode(MM_HIMETRIC);

	////(&previewDC)->BitBlt(0, 0, rect.Width(), rect.Height(), &noteDC, 100, 100, SRCCOPY);
	////(&previewDC)->BitBlt(0, 0, rect.Width(), rect.Height(), &noteDC, 100, 100, SRCCOPY);
	////(&previewDC)->StretchBlt(0, 0, 500, 500, &noteDC, 0, 0, noteRect.Width(), noteRect.Height(), SRCCOPY);
	////(&previewDC)->StretchBlt(0, 0, 2000, 1300, &noteDC, 0, 0, 21000, -29700, SRCCOPY);
	////boardDC.StretchBlt(0, 0, boardDC.GetDeviceCaps(HORZSIZE), boardDC.GetDeviceCaps(VERTSIZE), &noteDC, 0, 0, 21000, -29700, SRCCOPY);
	//Long sizeX = boardDC.GetDeviceCaps(HORZSIZE);
	//Long sizeY = boardDC.GetDeviceCaps(VERTSIZE);
	//
	//boardDC.StretchBlt(0, 0, boardDC.GetDeviceCaps(HORZSIZE), boardDC.GetDeviceCaps(VERTSIZE), &noteDC, 0, 0, 21000, -29700, SRCCOPY);
	this->previewPaper->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
}
