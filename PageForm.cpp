//PageForm.cpp

#include "PageForm.h"
#include "MemoForm.h"
#include "Contents.h"
#include "Page.h"
#include "Memo.h"
#include "Visitor.h"
#include "ArrayIterator.h"
#include "MouseAction.h"
#include "MouseActionCreator.h"

BEGIN_MESSAGE_MAP(PageForm, CWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	//ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	//ON_WM_LBUTTONUP()
	ON_WM_SETFOCUS()
	ON_WM_MOUSEWHEEL()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

PageForm::PageForm(Contents *contents, Long capacity, string pageFormName)
	:CompositeForm(contents, capacity) {
	this->pageFormName = pageFormName;
	
}

PageForm::PageForm(const PageForm& source)
	: CompositeForm(source) {
	this->pageFormName = source.pageFormName;
}

PageForm::~PageForm() {
	
}

PageForm& PageForm::operator=(const PageForm& source) {
	CompositeForm::operator=(source);
	this->pageFormName = source.pageFormName;
	return *this;
}

int PageForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct);
	CRect pageFormRect;
	this->GetClientRect(&pageFormRect);
	this->hScrinfo.cbSize = sizeof(hScrinfo);
	this->hScrinfo.fMask = SIF_ALL;
	this->hScrinfo.nMin = 0;
	this->hScrinfo.nMax = pageFormRect.Width();//this->maxLineSize;//(rect.right / (characterFaces->GetCharacterSize(97).GetWidth())) - 1;	
	this->hScrinfo.nPage = 150;//this ->maxLineSize / rect.right; //5;
	this->hScrinfo.nPos = 0;

	this->vScrinfo.cbSize = sizeof(vScrinfo);
	this->vScrinfo.fMask = SIF_ALL;
	this->vScrinfo.nMin = 0;
	this->vScrinfo.nMax = pageFormRect.Height();//this->maxLineSize;//(rect.right / (characterFaces->GetCharacterSize(97).GetWidth())) - 1;	
	this->vScrinfo.nPage = 150;//this ->maxLineSize / rect.right; //5;
	this->vScrinfo.nPos = 0;
	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	this->focusedMemo = NULL;
	this->hoveredMemo = NULL;
	return 0;
}
#include "OtherNoteForm.h"
#include "Note.h"
void PageForm::OnClose() {
	CWnd::OnClose();
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)FindWindow(NULL, "OtherNote");
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)FindWindow("OtherNote", NULL);
	Long i = 0;
	while (otherNoteForm->GetPageForm(i) != this) {
		i++;
	}
	Note *note = (Note*)(otherNoteForm->GetContents());
	note->SetCurrent(i);
	otherNoteForm->RemovePageForm(note->GetCurrent());
	note->RemovePage();
	//여기까지 페이지 제거
	//이후 커런트가 -1일 때 length>0이면 current++, length==0이면 페이지, 페이지폼 추가 (후 커런트 옮기고 show해줌->페이지폼 추가에 포함돼있음)
}

#include "BufferDC.h"
void PageForm::OnPaint() {
	BufferDC dc(this);
	CRect rect;
	this->GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(255, 255, 255));
}


BOOL PageForm::OnEraseBkgnd(CDC *pDC) {
	return TRUE;
}

//수정필요
//void PageForm::OnSize(UINT nType, int cx, int cy) {
//	CRect rect;
//	this->GetClientRect(&rect);
//	rect.right = cx;
//	rect.bottom = cy;
//	this->MoveWindow(&rect, TRUE);
//
//	//this->ShowWindow(SW_SHOWMAXIMIZED);
//
//	CRect tabRect;
//	this->GetTabCtrl()->GetClientRect(&tabRect);
//	this->tabCtrl->AdjustRect(TRUE, &rect);
//	this->tabCtrl->MoveWindow(&rect, TRUE);
//
//	this->tabCtrl->AdjustRect(FALSE, &rect);
//	this->tabCtrl->MoveWindow(&rect, TRUE);
//}

//Long PageForm::AddMemoForm(Memo *memo, CPoint point) {
#include "FindingForm.h"
Long PageForm::AddMemoForm(Memo *memo, CRect rect, Long color) {

	//1121 찾은 index 해제 하기
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	FindingForm *findingForm = otherNoteForm->GetFindingForm();
	if (findingForm != NULL) {
		findingForm->ResetIndexes();
	}

	Long current = CompositeForm::Add(new MemoForm(memo, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, color));
	CString strMyClass = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW, NULL, (HBRUSH)GetStockObject(WHITE_BRUSH), NULL);
	MemoForm *memoForm = this->GetMemoForm(current);
	memoForm->CreateEx(0, strMyClass, _T("Memo"), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, rect, this, 0, NULL);
	memoForm->BringWindowToTop();
	this->focusedMemo = memoForm;
	return current;
}

Long PageForm::AddMemoForm(MemoForm *memoForm) {
	//1121 찾은 index 해제 하기
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	FindingForm *findingForm = otherNoteForm->GetFindingForm();
	if (findingForm != NULL) {
		findingForm->ResetIndexes();
	}

	Long current = CompositeForm::Add(memoForm);
	CString strMyClass = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW, NULL, (HBRUSH)GetStockObject(WHITE_BRUSH), NULL);
	//memoForm = this->GetMemoForm(current);
	//memoForm->CreateEx(0, strMyClass, _T("Memo"), WS_OVERLAPPEDWINDOW | WS_CHILD | WS_VISIBLE, CRect(point.x, point.y, point.x + 300, point.y + 200), this, 0, NULL);
	CRect rect;
	rect.left = memoForm->GetPositionX();
	rect.right = rect.left + memoForm->GetMaxWidth();
	rect.top = memoForm->GetPositionY();
	rect.bottom = rect.top + memoForm->GetMaxHeight();
	memoForm->CreateEx(0, strMyClass, _T("Memo"), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, rect, this, 0, NULL);
	this->focusedMemo = memoForm;
	//memoForm->SetWindowPos(&wndTop, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE);
	//memoForm->ShowWindow(SW_HIDE);
	return current;
}

void PageForm::OnLButtonDown(UINT nFlags, CPoint point) {
	CWnd::OnLButtonDown(nFlags, point);
	MouseActionCreator mouseActionCreator;
	MouseAction *mouseAction = mouseActionCreator.Create(this, nFlags, point, WM_LBUTTONDOWN);
	if (mouseAction != 0) {
		mouseAction->OnMouseAction(nFlags, point);
		delete mouseAction;
		mouseAction = 0;
	}
}

Long PageForm::RemoveMemoForm(Long index) {
	return CompositeForm::Remove(index);
}

MemoForm* PageForm::GetMemoForm(Long index) {
	return static_cast<MemoForm*>(CompositeForm::GetAt(index));
}

MemoForm* PageForm::operator[](Long index) {
	return static_cast<MemoForm*>(CompositeForm::GetAt(index));
}

Form* PageForm::Clone() const {
	return new PageForm(*this);
}

void PageForm::Accept(Visitor* visitor) {
	visitor->Visit(this);
}

ArrayIterator<Form*>* PageForm::CreateIterator() const {
	return const_cast<ArrayIterator<Form*>*>(new ArrayIterator<Form*>(&this->forms));
}

#include "Line.h"
bool PageForm::CleanUpMemoForms(){
	bool ret = false;
	//1. 페이지폼의 페이지를 가져온다.
	Page *page = static_cast<Page*>(this->GetContents());

	//2. 빈메모를 찾는다.
	Memo *memo;
	Long i = 0;
	while (i < page->GetLength()) {
		memo = page->GetMemo(i);
		Line *line;
		line = memo->GetLine(0);
		//3. 빈메모를 지운다.
		if (memo->GetLength() == 1 && line->GetLength() == 0) {
			ret = true;
			this->GetMemoForm(i)->OnClose();
		}
		i++;
	}
	return ret;
}

//void PageForm::SetPageFormName(const string& pageFormName) {
void PageForm::SetPageFormName(string pageFormName) {
	this->pageFormName = pageFormName;
}

void PageForm::SetHScrinfo(SCROLLINFO hScrinfo) {
	this->hScrinfo = hScrinfo;
}

void PageForm::SetVScrinfo(SCROLLINFO vScrinfo) {
	this->vScrinfo = vScrinfo;
}

void PageForm::UpdateScrinfo() {
	CRect parentRect;
	this->GetParent()->GetClientRect(&parentRect);
	CRect pageFormRect;
	this->GetClientRect(&pageFormRect);
	
	this->hScrinfo.cbSize = sizeof(this->hScrinfo);
	this->hScrinfo.fMask = SIF_ALL;
	this->hScrinfo.nMin = 0;
	this->hScrinfo.nMax = pageFormRect.Width();	
	this->hScrinfo.nPage = parentRect.Width();
	//this->hScrinfo.nPos = 0;

	this->vScrinfo.cbSize = sizeof(this->vScrinfo);
	this->vScrinfo.fMask = SIF_ALL;
	this->vScrinfo.nMin = 0;
	this->vScrinfo.nMax = pageFormRect.Height();
	this->vScrinfo.nPage = parentRect.Height();
	//this->vScrinfo.nPos = 0;
}

void PageForm::ResizeWindow(Long width, Long height) {
	CRect pageFormRect;
	this->GetClientRect(&pageFormRect);

	//
	Long pageFormWidth = pageFormRect.Width() + width;
	if (pageFormRect.Width() + width > PAGEFORM_MAX_WIDTH) {
		pageFormWidth -= pageFormRect.Width() + width - PAGEFORM_MAX_WIDTH;
	}

	Long pageFormHeight = pageFormRect.Height() + height;
	if (pageFormRect.Height() + height > PAGEFORM_MAX_HEIGHT) {
		pageFormHeight -= pageFormRect.Height() + height - PAGEFORM_MAX_HEIGHT;
	}
	//
	//this->SetWindowPos(0, 0, 0, pageFormRect.Width() + width, pageFormRect.Height() + height, SWP_NOMOVE | SWP_NOZORDER);
	this->SetWindowPos(0, 0, 0, pageFormWidth, pageFormHeight, SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW);
	this->UpdateScrinfo();
}

#include "Caret.h"
#include "CharacterFaces.h"
#include "HorizontalScroll.h"
#include "VerticalScroll.h"
void PageForm::UpdateSize(MemoForm* memoForm) {
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(FindWindow("OtherNote", NULL));
	CRect docWndRect;
	otherNoteForm->GetDocumentWnd()->GetWindowRect(&docWndRect);
	CRect memoFormRect;
	memoForm->GetWindowRect(&memoFormRect);
	CRect pageFormWndRect;
	this->GetWindowRect(&pageFormWndRect);

	//horizontal scroll
	if (memoFormRect.right > pageFormWndRect.right) {
		this->ResizeWindow(memoFormRect.right - docWndRect.right, 0);
		otherNoteForm->GetHorizontalScroll()->UpdateScrinfo(this->GetHScrinfo());
	}

	//vertical scroll
	CPoint point;
	point.x = memoForm->GetCaret()->GetXPosition();
	point.y = memoForm->GetCaret()->GetYPosition();
	memoForm->ClientToScreen(&point);
	if (memoFormRect.bottom > pageFormWndRect.bottom) {
		this->ResizeWindow(0, memoFormRect.bottom - docWndRect.bottom);
		otherNoteForm->GetVerticalScroll()->UpdateScrinfo(this->GetVScrinfo());
	}

	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	Long heightOfMemoForm = characterFaces->GetCharacterSize(97).GetHeight();
	if (point.y + 10 + heightOfMemoForm> docWndRect.bottom) {
		otherNoteForm->GetVerticalScroll()->ScrollNext(heightOfMemoForm);
	}
}

#include "HorizontalScroll.h"
#include "VerticalScroll.h"
void PageForm::OnSetFocus(CWnd *pOldWnd) {
	CWnd::OnSetFocus(pOldWnd);
	//this->caret->ShowCaret();
	//this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
	Note *note = (Note*)(otherNoteForm->GetContents());
	Long current = note->GetCurrent();

	otherNoteForm->GetHorizontalScroll()->SetCurrent(current);
	otherNoteForm->GetVerticalScroll()->SetCurrent(current);

	//this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	this->Redraw();
	//this->GetMemoForm(this->GetLength() - 1)->RedrawWindow(NULL, NULL, RDW_INVALIDATE);
}

void PageForm::OnEraseFindIndexes() {
	Long i = 0;
	while (i < this->GetLength()) {
		this->GetMemoForm(i)->OnEraseFindIndexes();
		i++;
	}
}

void PageForm::UpdatePageForm() {
	//페이지폼 확대 및 스크롤
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(FindWindow(NULL, "OtherNote"));
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(FindWindow("OtherNote", NULL));
	CRect docWndRect;
	otherNoteForm->GetDocumentWnd()->GetWindowRect(&docWndRect);

	//메모폼들 중에서 가장 긴 x지점을 찾는다.
	//메모폼들 중에서 가장 긴 y지점을 찾는다.
	Long maxY = 0;
	Long maxX = 0;
	Long i = 0;
	while (i < static_cast<Page*>(this->GetContents())->GetLength()) {
		MemoForm *memoForm = this->GetMemoForm(i);
		if (maxX < memoForm->GetMaxWidth() + memoForm->GetPositionX()) {
			maxX = memoForm->GetMaxWidth() + memoForm->GetPositionX();
		}
		if (maxY < memoForm->GetMaxHeight() + memoForm->GetPositionY()) {
			maxY = memoForm->GetMaxHeight() + memoForm->GetPositionY();
		}
		i++;
	}
	CRect pageFormWndRect;
	this->GetWindowRect(&pageFormWndRect);

	//width 부분 확대 및 스크롤
	if (maxX > docWndRect.right) {
		if (pageFormWndRect.right + 2 == docWndRect.right) {
			this->ResizeWindow(maxX - docWndRect.right + 150, 0);
			otherNoteForm->GetHorizontalScroll()->UpdateScrinfo(this->GetHScrinfo());
		}
		otherNoteForm->GetHorizontalScroll()->ScrollNext(maxX - docWndRect.right + 150);
	}

	//height 부분 확대 및 스크롤
	if (maxY > docWndRect.bottom) {
		//1. 페이지폼 증가 상황
		if (pageFormWndRect.bottom + 2 == docWndRect.bottom) {
			this->ResizeWindow(0, maxY - docWndRect.bottom + 150);
			otherNoteForm->GetVerticalScroll()->UpdateScrinfo(this->GetVScrinfo());
		}
		//2. 스크롤 아래쪽을 이동
		otherNoteForm->GetVerticalScroll()->ScrollNext(maxY - docWndRect.bottom + 150);
	}
}

BOOL PageForm::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) {
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CWnd::FindWindow("OtherNote", NULL));
	if (nFlags == MK_SHIFT) {
		if (zDelta <= 0) {
			otherNoteForm->GetHorizontalScroll()->ScrollNextLine();
		}
		else {
			otherNoteForm->GetHorizontalScroll()->ScrollPreviousLine();
		}
	}
	else {
		if (zDelta <= 0) {
			otherNoteForm->GetVerticalScroll()->ScrollNextLine();
		}
		else {
			otherNoteForm->GetVerticalScroll()->ScrollPreviousLine();
		}
	}
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

BOOL PageForm::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) {
	SetCursor(LoadCursor(NULL, IDC_ARROW));
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

#include "Page.h"
#include "Memo.h"
#include "Contents.h"
void PageForm::FocusMemo(MemoForm *focusedMemo) {
	Long i = 0;
	MemoForm *memoForm = this->GetMemoForm(i);
	while (i < this->GetLength() && focusedMemo != memoForm) {
		i++;
		memoForm = this->GetMemoForm(i);
	}
	Page *page = static_cast<Page*>(this->GetContents());
	Memo *memo = page->GetMemo(i);
	page->Delete(i);
	page->Add(memo);
	CompositeForm::Delete(i);
	CompositeForm::Add(focusedMemo);
	this->focusedMemo = focusedMemo;
}

void PageForm::HoverMemo(MemoForm *memoForm) {
	this->hoveredMemo = memoForm;
}

void PageForm::OnMouseMove(UINT nFlags, CPoint point) {
	CWnd::OnMouseMove(nFlags, point);
	if (this->hoveredMemo != NULL) {
		this->hoveredMemo->SetIsHovered(FALSE);
		this->hoveredMemo->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_NOERASE);
		this->hoveredMemo = NULL;
	}
}

void PageForm::Redraw() {
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CWnd::FindWindow("OtherNote", NULL));
	CRect docRect;
	otherNoteForm->GetDocumentWnd()->GetWindowRect(&docRect);
	this->ScreenToClient(&docRect);
	this->RedrawWindow(&docRect, NULL, RDW_INVALIDATE);
}