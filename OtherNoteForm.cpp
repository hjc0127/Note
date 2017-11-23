//OtherNoteForm.cpp

#include "OtherNoteForm.h"
#include "TabCtrl.h"
#include "PageForm.h"
#include "MemoForm.h"
#include "Contents.h"
#include "Note.h"
#include "Page.h"
#include "Memo.h"
#include "Line.h"
#include "SingleCharacter.h"
#include "DoubleCharacter.h"
#include "CharacterFaces.h"
#include "Visitor.h"
#include "MakeStringVisitor.h"
#include "HorizontalScroll.h"
#include "VerticalScroll.h"
#include "HScrollActionCreator.h"
#include "VScrollActionCreator.h"
#include "ScrollAction.h"
#include "MouseActionCreator.h"
#include "MouseAction.h"
#include <afxdlgs.h>
#include <afxcmn.h>
#include <WinUser.h>
#include <fstream>

using namespace std;

UINT OtherNoteForm::WM_FIND = RegisterWindowMessage(FINDMSGSTRING);

BEGIN_MESSAGE_MAP(OtherNoteForm, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SIZE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_COMMAND(ID_MENU_NEWFILE, &OtherNoteForm::OnMenuNewFile)
	ON_COMMAND(ID_MENU_EXIT, &OtherNoteForm::OnMenuExit)
	ON_COMMAND(ID_MENU_LOAD, &OtherNoteForm::OnMenuOpen)
	ON_COMMAND(ID_MENU_SAVE, &OtherNoteForm::OnMenuSave)
	ON_COMMAND(ID_MENU_SAVEAS, &OtherNoteForm::OnMenuSaveAs)
	ON_COMMAND(ID_MENU_FINDINGOTHERNOTE, &OtherNoteForm::OnMenuFindOtherNote)
	ON_COMMAND(ID_MENU_FINDINGPAGE, &OtherNoteForm::OnMenuFindPage)
	ON_COMMAND(ID_MENU_PREVIEW, &OtherNoteForm::OnFilePrintPreview)
	ON_COMMAND(ID_MENU_PRINT, &OtherNoteForm::OnFilePrint)
	ON_COMMAND(ID_MENU_INFORMATION, &OtherNoteForm::OnMenuInformation)
	ON_REGISTERED_MESSAGE(WM_FIND, &OtherNoteForm::OnFind)
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

OtherNoteForm::OtherNoteForm(Contents *contents, Long capacity) 
	:CompositeForm(contents, capacity) {
	this->tabCtrl = new TabCtrl;
	this->documentWnd = new CFrameWnd;
	this->horizontalScroll = NULL;
	this->verticalScroll = NULL;
	//this->fileName = "OtherNote";
	this->fileName = "�������";
	this->printingForm = NULL;
	this->printPreview = NULL;
	this->defaultMemoColor = MEMOFORM_COLOR_PURPLE;
	this->findingForm = NULL;
}

OtherNoteForm::~OtherNoteForm() 
{
	/*Long i = 0;
	while (i < this->length) {
		if (this->forms.GetAt(i) != 0) {
			delete this->forms.GetAt(i);
		}
		i++;
	}*/
	if (this->contents != 0) {
		delete this->contents;
	}

	if (this->tabCtrl != 0) {
		delete this->tabCtrl;
	}
	
	if (this->horizontalScroll != 0) {
		delete this->horizontalScroll;
	}

	if (this->verticalScroll != 0) {
		delete this->verticalScroll;
	}
}

OtherNoteForm::OtherNoteForm(const OtherNoteForm& source) 
	:CompositeForm(source){
	this->tabCtrl = new TabCtrl(*source.tabCtrl);
}

OtherNoteForm& OtherNoteForm::operator=(const OtherNoteForm& source) {
	CompositeForm::operator=(source);
	if (source.tabCtrl != 0) {
		delete source.tabCtrl;
	}
	this->tabCtrl = new TabCtrl(*source.tabCtrl);
	return *this;
}

/*
1. page���� AddPageForm�� ȣ���Ѵ�.
1.1. pageForm�� page�� �����ش�.
1.2. tabCtrl�� InsertItem�� ���ش�.
*/
#include "FindingForm.h"
Long OtherNoteForm::AddPageForm(Page *page, CString pageFormName) {	

	//1121 ã�� index ���� �ϱ�
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	FindingForm *findingForm = otherNoteForm->GetFindingForm();
	if (findingForm != NULL) {
		findingForm->ResetIndexes();
	}

	//1. make pageFormName
	if (pageFormName.Compare(CString("")) == 0) {
		CString page("   Page");//3ĭ ����
		pageFormName += page;
		CString pageFormNumber;
		pageFormNumber.Format("%d", this->GetLength());
		pageFormName += pageFormNumber;
		pageFormName += "   ";//3ĭ ����
	}	
	
	//2. add pageForm
	Long index = this->CompositeForm::Add(new PageForm(page, 64, (LPCTSTR)pageFormName));	
	PageForm *pageForm = static_cast<PageForm*>(this->CompositeForm::GetAt(index));
	
	//3. insert tab
	this->tabCtrl->InsertItem(this->GetLength(), pageFormName);
	
	CRect docWndRect;
	this->documentWnd->GetClientRect(docWndRect);

	//4. Create pageForm
	CString strMyClass = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW, NULL, (HBRUSH)GetStockObject(WHITE_BRUSH), NULL);
	pageForm->CreateEx(0, strMyClass, "Page", WS_CLIPCHILDREN | WS_CHILD | WS_VISIBLE, docWndRect, this->documentWnd, 0, NULL);
	pageForm->UpdateScrinfo();
	pageForm->ShowWindow(SW_HIDE);
	
	return index;
}

Long OtherNoteForm::AddPageForm(PageForm *pageForm) {
	//1121 ã�� index ���� �ϱ�
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	FindingForm *findingForm = otherNoteForm->GetFindingForm();
	if (findingForm != NULL) {
		findingForm->ResetIndexes();
	}

	//1. make pageFormName
	CString pageFormName;
	pageFormName = pageForm->GetPageFormName().c_str();
	pageFormName += "Copy";
	pageFormName += "   ";//3ĭ
	pageForm->SetPageFormName((LPCTSTR)pageFormName);

	//2. add pageForm
	Long index = this->CompositeForm::Add(pageForm);
	
	//3. insert tab
	this->tabCtrl->InsertItem(this->GetLength(), pageFormName);
	
	CRect docWndRect;
	this->documentWnd->GetClientRect(docWndRect);

	//4. Create pageForm
	CString strMyClass = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW, NULL, (HBRUSH)GetStockObject(WHITE_BRUSH), NULL);
	pageForm->CreateEx(0, strMyClass, "Page", WS_CLIPCHILDREN |WS_CHILD | WS_VISIBLE, docWndRect, this->documentWnd, 0, NULL);
	pageForm->UpdateScrinfo();
	pageForm->ShowWindow(SW_HIDE);
	
	return index;
}

PageForm* OtherNoteForm::GetPageForm(Long index) {
	return static_cast<PageForm*>(CompositeForm::GetAt(index));
}

Long OtherNoteForm::RemovePageForm(Long index) {
	this->tabCtrl->DeleteItem(index);
	return CompositeForm::Remove(index);
}

PageForm* OtherNoteForm::operator[](Long index) {
	return static_cast<PageForm*>(this->forms[index]);
}

Form* OtherNoteForm::Clone() const{
	return new OtherNoteForm(*this);
}

ArrayIterator<Form*>* OtherNoteForm::CreateIterator() const{
	return const_cast<ArrayIterator<Form*>*>(new ArrayIterator<Form*>(&this->forms));
}

void OtherNoteForm::Accept(Visitor *visitor) {
	visitor->Visit(this);
}

BOOL OtherNoteForm::PreTranslateMessage(MSG* pMsg) {
	if (::TranslateAccelerator(this->m_hWnd, m_accelerators_key, pMsg)) {
		return TRUE;
	}

	return CFrameWnd::PreTranslateMessage(pMsg);
}

int OtherNoteForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CFrameWnd::OnCreate(lpCreateStruct);
	
	//1. icon ����
	HICON icon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON_OTHERNOTE));
	this->SetIcon(icon, FALSE);
	
	//2. Accelerator ����
	this->m_accelerators_key = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR_OTHERNOTE));

	//3. cursor ����
	SetCursor(LoadCursor(NULL, IDC_ARROW));

	//3 tab �߰�
	CRect rect;
	this->GetClientRect(&rect);
	this->tabCtrl->Create(WS_CHILD | WS_VISIBLE | TCS_TABS, rect, this, 0);

	//size ����
	CRect itemRect;
	this->tabCtrl->GetItemRect(0, &itemRect);
	CSize size;
	size.cx = itemRect.Width();
	size.cy = itemRect.Height() + 4;
	this->tabCtrl->SetItemSize(size);

	CRect tabRect;
	this->tabCtrl->GetItemRect(0, &tabRect);
	CRect docRect;
	this->GetClientRect(docRect);
	docRect.right -= 20;
	docRect.top = tabRect.bottom;
	docRect.bottom -= 20;
	CString strMyClass = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW, NULL, (HBRUSH)GetStockObject(WHITE_BRUSH), NULL);
	this->documentWnd->CreateEx(0, strMyClass, "document", WS_CHILD | WS_VISIBLE, docRect, this, 0, NULL);
	
//	this->Load();
	if (this->GetLength() == 0) {
		CPaintDC dc(this->documentWnd);
		CharacterFaces *characterFaces = CharacterFaces::Instance(&dc);
		Long index = static_cast<Note*>(this->contents)->AddPage();
		this->AddPageForm(static_cast<Page*>(static_cast<Note*>(this->contents)->GetAt(index)));
	}

	static_cast<Note*>(this->contents)->SetCurrent(0);

	static_cast<PageForm*>(this->GetPageForm(0))->ShowWindow(SW_SHOW);
	this->horizontalScroll = new HorizontalScroll(this);
	this->verticalScroll = new VerticalScroll(this);
	DestroyCaret();
	
	this->SetFocus();
	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	return 0;
}


void OtherNoteForm::OnSize(UINT nType, int cx, int cy) {
	CFrameWnd::OnSize(nType, cx, cy);
	CRect noteClientRect;
	this->GetClientRect(&noteClientRect);
	this->horizontalScroll->GetScrollBar()->MoveWindow(noteClientRect.left, noteClientRect.bottom-20, noteClientRect.Width()-20, 20, 1);
	this->verticalScroll->GetScrollBar()->MoveWindow(noteClientRect.right-20, noteClientRect.top+27+4, 20, noteClientRect.Height()-50 - 4, 1);
	this->tabCtrl->MoveWindow(0, 1, noteClientRect.Width(), noteClientRect.Height(), true);
	
	CRect tabItemRect;
	this->tabCtrl->GetItemRect(0, &tabItemRect);
	this->documentWnd->MoveWindow(1, tabItemRect.bottom+3, noteClientRect.Width()-21, noteClientRect.Height()-tabItemRect.bottom-23, true);
	PageForm *pageForm = this->GetPageForm(0);
	CRect pageFormRect;
	pageForm->GetClientRect(&pageFormRect);
	CRect docFormRect;
	this->documentWnd->GetClientRect(&docFormRect);
	if (pageFormRect.Width() < docFormRect.Width() && pageFormRect.Height() < docFormRect.Height()) {
		pageFormRect.left = docFormRect.left;
		pageFormRect.top = docFormRect.left;
		pageFormRect.right = docFormRect.right;
		pageFormRect.bottom = docFormRect.bottom;
		pageForm->SetWindowPos(0, 0, 0, pageFormRect.Width(), pageFormRect.Height(), SWP_NOZORDER);
		this->GetPageForm(0)->UpdateScrinfo();
		this->horizontalScroll->SetCurrent(static_cast<Note*>(this->GetContents())->GetCurrent());
		this->verticalScroll->SetCurrent(static_cast<Note*>(this->GetContents())->GetCurrent());
	}

	Long i = 0;
	while (i < this->GetLength()) {
		this->GetPageForm(i)->UpdateScrinfo();
		i++;
	}
	this->horizontalScroll->SetCurrent(static_cast<Note*>(this->GetContents())->GetCurrent());
	this->verticalScroll->SetCurrent(static_cast<Note*>(this->GetContents())->GetCurrent());
	
	this->documentWnd->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	this->horizontalScroll->GetScrollBar()->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	this->verticalScroll->GetScrollBar()->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
}

//To do
#include "PrintingForm.h"
void OtherNoteForm::OnClose() {
	//Caret *caret = Caret::Instance(this);
	//if (caret != 0) {
	//	delete caret;
	//}
	this->SetFocus();
	//this->Save();
	/*Long i = 0;
	while (i < this->length) {
		if (this->forms.GetAt(i) != 0) {
			delete this->forms.GetAt(i);
		}
		i++;
	}*/

	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	if (characterFaces != 0) {
		delete characterFaces;
	}

	/*if (this->memo != 0) {/////����
		delete this->memo;
	}*/

	//if (this->tabCtrl != 0) {
	//	delete this->tabCtrl;
	//}

	//destructor���� ���Ϸ� ����
	/*while (this->length > 0) {
		static_cast<Note*>(this->contents)->SetCurrent(0);
		this->RemovePageForm(0);
	}*/
	
	if (this->printingForm != 0) {
		this->printingForm->OnClose();
		this->printingForm = NULL;
		//this->printingForm->CloseWindow();
	}
	CFrameWnd::OnClose();
}

#include "PaintVisitor.h"
#include "ArrayIterator.h"

//To do
void OtherNoteForm::OnPaint() {
	CFrameWnd::OnPaint();
	//1022���� ���� : ���α׷� �����, vertical�� ĳ�� ������ ����
	//����1 : ���α׷� ���� > �� �޸� ���� > �ϴ� app icon Ŭ��(�ּ�ȭ Ŭ��) > �ϴ� app icon Ŭ��(�ִ�ȭ)
	//����2 : ���α׷� ���� > �� �޸� ���� > �޴� > �̸����� > �̸����� �ݱ�
	PageForm *pageForm = this->GetPageForm(static_cast<Note*>(this->GetContents())->GetCurrent());
	Long index;
	index = pageForm->GetLength();
	if (index > 0) {
		pageForm->GetMemoForm(index - 1)->SetFocus();
	}
	else {
		pageForm->SetFocus();
	}
}

#include "LoadVisitor.h"
void OtherNoteForm::Load(LPTSTR lpstrFile) {
	//1. �Է¹��� ������ �д´�.
	LoadVisitor loadVisitor(lpstrFile);
	this->Accept(&loadVisitor);
	
	//2. �������� ����� �����Ѵ�.
	//LoadVisior���� ���ִ� �ɷ� ���� 11/12
	PageForm *pageForm;
	/*Long i = 0;
	while (i < static_cast<Note*>(this->GetContents())->GetLength()) {
		pageForm = this->GetPageForm(i);
		Long j = 0;
		while (j < static_cast<Page*>(pageForm->GetContents())->GetLength()) {
			pageForm->UpdateSize(pageForm->GetMemoForm(j));
			j++;
		}
		i++;
	}*/

	////3. 0�� �������� ������ �޸� ��ũ���� �̵��Ѵ�.(-�� �������� ���)
	//pageForm = this->GetPageForm(0);
	//pageForm->UpdatePageForm();

	/////////////////////////////////////////////////////////////////////
	//11/11
	//3. �ҷ��� tab���� �����Ѵ�.
	this->SelectTabItem(static_cast<Note*>(this->GetContents())->GetCurrent());

	//4. ��ũ���� �ش� �������� �����Ѵ�.
	this->GetHorizontalScroll()->SetCurrent(static_cast<Note*>(this->GetContents())->GetCurrent());
	this->GetVerticalScroll()->SetCurrent(static_cast<Note*>(this->GetContents())->GetCurrent());

	//5. ���õ� tab�� ǥ���ϱ�
	static_cast<TabCtrl*>(this->GetTabCtrl())->SetCurSel(static_cast<Note*>(this->GetContents())->GetCurrent());
	static_cast<TabCtrl*>(this->GetTabCtrl())->DrawTabItem();

	//3. 0�� �������� ������ �޸� ��ũ���� �̵��Ѵ�.(-�� �������� ���)
	pageForm = this->GetPageForm(static_cast<Note*>(this->GetContents())->GetCurrent());
	pageForm->UpdatePageForm();
	/////////////////////////////////////////////////////////////////////
	
	//������ ��Ŀ�� ����� �����ش�.
	MemoForm *memoForm = pageForm->GetMemoForm(pageForm->GetLength() - 1);
	memoForm->SetFocusType(MEMOFORM_FOCUS_CAPTION);
	memoForm->SetFocus();
}

#include "SaveVisitor.h"
void OtherNoteForm::Save(LPTSTR lpstrFile) {
	SaveVisitor saveVisitor(lpstrFile);
	this->Accept(&saveVisitor);
}

void OtherNoteForm::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	HScrollActionCreator hScrollActionCreator;
	ScrollAction *scrollAction = hScrollActionCreator.Create(this->horizontalScroll, nSBCode, nPos, pScrollBar);

	if(scrollAction != 0) {
		scrollAction->Action(nSBCode, nPos, pScrollBar);
	}
}

void OtherNoteForm::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) {
	VScrollActionCreator vScrollActionCreator;
	ScrollAction *scrollAction = vScrollActionCreator.Create(this->verticalScroll, nSBCode, nPos, pScrollBar);
	
	if(scrollAction != 0) {
		scrollAction->Action(nSBCode, nPos, pScrollBar);
	}
}

void OtherNoteForm::OnLButtonDblClk(UINT nFlags, CPoint point) {
	CFrameWnd::OnLButtonDblClk(nFlags, point);
	MouseActionCreator mouseActionCreator;
	MouseAction *mouseAction = mouseActionCreator.Create(this, nFlags, point, WM_LBUTTONDBLCLK);
	if (mouseAction != 0) {
		mouseAction->OnMouseAction(nFlags, point);
		delete mouseAction;
		mouseAction = 0;
	}
}

void OtherNoteForm::SelectTabItem(Long index) {
	//1. page ��ġ�� �������ش�.
	static_cast<Note*>(this->contents)->SetCurrent(index);
	//2. page ��ġ�� for�� �����´�.
	PageForm *pageForm = this->GetPageForm(index);
	//3. page���� �����ش�.
	pageForm->ShowWindow(SW_SHOW);
	//4. page���� ��Ŀ���� �����Ѵ�.
	pageForm->SetFocus();
}

void OtherNoteForm::OnMenuExit() {
	this->OnClose();
}

void OtherNoteForm::OnMenuNewFile() {
	this->GetDocumentWnd()->SetFocus();
	//1. ������ load�ϰų� �������� ���� ����
	NewFileDialog newFileDialog(IDD_DIALOG_NEWFILE);
	newFileDialog.DoModal();
	this->SetFileName(CString("�������"));
	this->SetWindowText(this->fileName);

}

void OtherNoteForm::SetFileName(CString& fileName) {
	this->fileName = fileName;
}

void OtherNoteForm::Reset() {
	this->ClearPageForms();
	if (this->GetLength() == 0) {
		CPaintDC dc(this->GetDocumentWnd());
		CharacterFaces *characterFaces = CharacterFaces::Instance(&dc);
		Long index = static_cast<Note*>(this->GetContents())->AddPage();
		this->AddPageForm(static_cast<Page*>(static_cast<Note*>(this->GetContents())->GetAt(index)));

		//1027�������� ���� ����
		this->GetHorizontalScroll()->SetCurrent(index);
		this->GetVerticalScroll()->SetCurrent(index);

	}
	static_cast<Note*>(this->GetContents())->SetCurrent(0);
	static_cast<PageForm*>(this->GetPageForm(0))->ShowWindow(SW_SHOW);
	/*this->horizontalScroll = new HorizontalScroll(this);
	this->verticalScroll = new VerticalScroll(this);*/
}

void OtherNoteForm::OnMenuOpen()
{
	this->GetDocumentWnd()->SetFocus();
	TCHAR szFilters[] = _T("Text files (*.txt)|*.txt|All files (*.*)|*.*||");
	CFileDialog fileDialog(TRUE, _T("txt"), _T("*.txt"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);
	OPENFILENAME& ofn = fileDialog.GetOFN();

	//ȭ�鿡 ���̾�α׸� �����ϰ� �ϱ�
	if (fileDialog.DoModal() == IDOK) {
		//���� ���������� ���� �� ���õ� ���� ����
		this->ClearPageForms();
		this->Load(ofn.lpstrFile);

		//0�� �������� ���� �� 0�� ������ ȭ�鿡 �����ֱ�
		/*static_cast<Note*>(this->contents)->SetCurrent(0);
		static_cast<PageForm*>(this->GetPageForm(0))->ShowWindow(SW_SHOW);*/
		//����� ������ �����ֱ�
		this->GetPageForm(static_cast<Note*>(this->GetContents())->GetCurrent())->ShowWindow(SW_SHOW);

		//�������� ��ġ ���߱�
		this->GetDocumentWnd()->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		this->GetHorizontalScroll()->GetScrollBar()->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		this->GetVerticalScroll()->GetScrollBar()->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

		//���� ��Ī �����ϱ�
		this->fileName = CString(ofn.lpstrFile);
		this->SetTitle(this->fileName);
		//this->SetWindowText(this->fileName);	
		this->SetWindowText(ofn.lpstrFileTitle);
	}
}

#include "Caret.h"
void OtherNoteForm::OnMenuSave()
{
	// 11/11 ���� �޸����� ��Ŀ�� �ְ�, ĳ��
	Note *note = static_cast<Note*>(this->GetContents());
	Page *page = note->GetPage(note->GetCurrent());
	Memo *memo = page->GetMemo(page->GetCurrent());
	Line *line = memo->GetLine(memo->GetRow());
	
	Long pageIndex = note->GetCurrent();
	Long memoIndex = page->GetCurrent();
	Long row = memo->GetRow();
	Long column = line->GetColumn();
	//////////////////////////////////////

	this->GetDocumentWnd()->SetFocus();
	//1. ���� ������ ������ ��� 
	CString fileName = this->GetFileName();
	//if (fileName.Compare("OtherNote") == 0) {
	if (fileName.Compare("�������") == 0) {
		//1. 1. Save As�� ���� ���� �����ϱ�
		TCHAR szFilters[] = _T("Text files (*.txt)|*.txt|All files (*.*)|*.*||");
		//CFileDialog fileDialog(FALSE, _T("txt"), _T("OtherNote.txt"), 0, szFilters);
		CFileDialog fileDialog(FALSE, _T("txt"), _T("*.txt"), 0, szFilters);
		OPENFILENAME& ofn = fileDialog.GetOFN();
		
		if (fileDialog.DoModal() == IDOK) {
			this->Save(ofn.lpstrFile);

			//1. 2. ������ ���Ϸ� �ٽ� �ε��ϱ�
			this->ClearPageForms();
			this->Load(ofn.lpstrFile);

			// 11/11
			/*static_cast<Note*>(this->contents)->SetCurrent(0);
			static_cast<PageForm*>(this->GetPageForm(0))->ShowWindow(SW_SHOW);*/
			//����� ������ �����ֱ�
			this->GetPageForm(static_cast<Note*>(this->GetContents())->GetCurrent())->ShowWindow(SW_SHOW);

			this->GetDocumentWnd()->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOREDRAW);
			this->GetHorizontalScroll()->GetScrollBar()->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE |SWP_NOREDRAW);
			this->GetVerticalScroll()->GetScrollBar()->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOREDRAW);

			this->fileName = CString(ofn.lpstrFile);
			this->SetTitle(this->fileName);
			//this->SetWindowText(this->fileName);
			this->SetWindowText(ofn.lpstrFileTitle);

		}		
	}
	else {
		//2. ����� ������ �ε�� ��Ȳ���� ���� ���Ͽ� �����ϱ�
		this->Save(fileName.GetBuffer(0)); //(LPTSTR)(fileName)
	}

	// 11/12 ���� �޸����� ��Ŀ�� �ְ�, ĳ��
	PageForm *pageForm = this->GetPageForm(pageIndex);
	MemoForm *memoForm = pageForm->GetMemoForm(memoIndex);
	memo = static_cast<Memo*>(memoForm->GetContents());
	line = memo->GetLine(row);
	memoForm->SetFocus();
	memo->SetRow(row);
	line->SetColumn(column);
	memoForm->GetCaret()->UpdateCaret();
}

void OtherNoteForm::OnMenuSaveAs()
{
	// 11/11 ���� �޸����� ��Ŀ�� �ְ�, ĳ��
	Note *note = static_cast<Note*>(this->GetContents());
	Page *page = note->GetPage(note->GetCurrent());
	Memo *memo = page->GetMemo(page->GetCurrent());
	Line *line = memo->GetLine(memo->GetRow());

	Long pageIndex = note->GetCurrent();
	Long memoIndex = page->GetCurrent();
	Long row = memo->GetRow();
	Long column = line->GetColumn();
	//////////////////////////////////////

	this->GetDocumentWnd()->SetFocus();
	TCHAR szFilters[] = _T("Text files (*.txt)|*.txt|All files (*.*)|*.*||");
	CFileDialog fileDialog(FALSE, _T("txt"), _T("*.txt"), 0, szFilters);
	//CFileDialog fileDialog(FALSE, _T("txt"), _T(this->fileName), 0, szFilters);
	OPENFILENAME& ofn = fileDialog.GetOFN();

	if (fileDialog.DoModal() == IDOK) {
		//this->Save(ofn.lpstrFile);
		this->Save(ofn.lpstrFile);

		//1. 2. ������ ���Ϸ� �ٽ� �ε��ϱ�
		this->ClearPageForms();
		this->Load(ofn.lpstrFile);

		// 11/11
		//static_cast<Note*>(this->contents)->SetCurrent(0);
		//static_cast<PageForm*>(this->GetPageForm(0))->ShowWindow(SW_SHOW);
		//����� ������ �����ֱ�
		this->GetPageForm(static_cast<Note*>(this->GetContents())->GetCurrent())->ShowWindow(SW_SHOW);

		this->GetDocumentWnd()->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		this->GetHorizontalScroll()->GetScrollBar()->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		this->GetVerticalScroll()->GetScrollBar()->SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

		this->fileName = CString(ofn.lpstrFile);
		this->SetTitle(this->fileName);
		//this->SetWindowText(this->fileName);
		this->SetWindowText(ofn.lpstrFileTitle);
	}

	// 11/12 ���� �޸����� ��Ŀ�� �ְ�, ĳ��
	PageForm *pageForm = this->GetPageForm(pageIndex);
	MemoForm *memoForm = pageForm->GetMemoForm(memoIndex);
	memo = static_cast<Memo*>(memoForm->GetContents());
	line = memo->GetLine(row);
	memoForm->SetFocus();
	memo->SetRow(row);
	line->SetColumn(column);
	memoForm->GetCaret()->UpdateCaret();
}

#include "TabCtrl.h"
void OtherNoteForm::ClearPageForms() {
	Long i = 0;
	Long count = static_cast<Note*>(this->GetContents())->GetLength() - 1;
	while (count >= 0) {
		//remove pageForm
		this->RemovePageForm(count);
		//remove page
		static_cast<Note*>(this->GetContents())->SetCurrent(count);
		static_cast<Note*>(this->GetContents())->RemovePage(); //1106 save�� �״� ���� �߻�
		count--;
	}
}

FindingForm* OtherNoteForm::SetFindingForm(FindingForm *findingForm) {
	this->findingForm = findingForm;
	return this->findingForm;
}

#include "FindingFormActionCreator.h"
#include "FindingFormAction.h"
#include "FindingForm.h"
void OtherNoteForm::OnMenuFindOtherNote() {
	this->GetDocumentWnd()->SetFocus();
	this->findingForm = new FindingForm(this->GetContents());
	findingForm->Create(this);
}

#include "Note.h"
void OtherNoteForm::OnMenuFindPage() {
	this->GetDocumentWnd()->SetFocus();
	Note *note = static_cast<Note*>(this->GetContents());
	Page *page = note->GetPage(note->GetCurrent());
	this->findingForm = new FindingForm(page);
	findingForm->Create(this);
}

#include "FindingFormActionCreator.h"
#include "FindingFormAction.h"
LRESULT OtherNoteForm::OnFind(WPARAM wParam, LPARAM lParam) {
	FindingFormActionCreator findingFormActionCreator;
	FindingFormAction *findingFormAction = findingFormActionCreator.Create(this, wParam, lParam);
	if (findingFormAction != 0) {
		findingFormAction->OnFindingFormButtonClicked(wParam, lParam);
		delete findingFormAction;
		findingFormAction = 0;
	}

	//1104 �޸� �� �߻�
	/*if (this->findingForm->IsTerminating() == TRUE) {
		if (this->findingForm != NULL) {
			this->findingForm->DestroyWindow();
			delete this->findingForm;
			this->findingForm = NULL;
		}		
	}*/

	//0920������
	//this->ScrollToFindIndex(&this->GetFindingForm()->GetIndexes().GetAt(this->GetFindingForm()->GetCurrent()));
	return 0;
}

//#include "FindIndex.h"
//void OtherNoteForm::ScrollToFindIndex(FindIndex *findIndex) {
//	//1. �������� �����Ѵ�.
//	PageForm *pageForm = this->GetPageForm((static_cast<Note*>(this->GetContents()))->GetCurrent());
//	MemoForm *memoForm = pageForm->GetMemoForm((static_cast<Page*>(pageForm->GetContents()))->GetCurrent());
//	if (findIndex->GetPageIndex() != static_cast<Note*>(this->GetContents())->GetCurrent()) {
//		//1.1. ���������� �����.
//		pageForm->CleanUpMemoForms();
//		pageForm->ShowWindow(SW_HIDE);
//
//		//1.2. ã�� �������� �����Ѵ�.
//		static_cast<TabCtrl*>(this->GetTabCtrl())->SetCurSel(findIndex->GetPageIndex());
//		this->SelectTabItem(findIndex->GetPageIndex());
//		this->GetHorizontalScroll()->SetCurrent(findIndex->GetPageIndex());
//		this->GetVerticalScroll()->SetCurrent(findIndex->GetPageIndex());
//		
//		//note�� Ŀ��Ʈ ���� 1029
//		static_cast<Note*>(this->GetContents())->SetCurrent(findIndex->GetPageIndex());
//		pageForm = this->GetPageForm((static_cast<Note*>(this->GetContents()))->GetCurrent());
//		static_cast<Page*>(pageForm->GetContents())->SetCurrent(findIndex->GetMemoIndex());
//		memoForm = pageForm->GetMemoForm(static_cast<Page*>(pageForm->GetContents())->GetCurrent());
//	}
//
//	Long position = 0;
//	CRect docWndRect;
//	this->GetDocumentWnd()->GetWindowRect(&docWndRect);
//
//	//MemoForm *memoForm = pageForm->GetMemoForm((static_cast<Page*>(pageForm->GetContents()))->GetCurrent());
//	Memo *memo = static_cast<Memo*>(memoForm->GetContents());
//	Line *line = memo->GetLine(memo->GetRow());
//	CRect memoFormWndRect;
//	memoForm->GetWindowRect(&memoFormWndRect);
//
//	Long length = this->findingForm->GetKey().GetLength();
//	Long row = findIndex->GetRow();
//	Long column = findIndex->GetColumn();
//	column = column + length - 1;
//
//	Long xPosition = memoFormWndRect.left + memoForm->GetMarginWidth();
//	Long yPosition = memoFormWndRect.top + memoForm->GetMarginHeight() + memoForm->GetCaptionHeight();
//	CharacterFaces *characterFaces = CharacterFaces::Instance(memoForm->GetDC());
//	CharacterSize characterSize = characterFaces->GetCharacterSize(97);
//	Long height = characterSize.GetHeight();
//
//	Long i = 0;
//	while (i < row) {
//		yPosition += height;
//		i++;
//	}
//
//	i = 0;
//	while (i < column) {
//		xPosition += line->GetCharacter(i)->GetWidth();//1028 ã�� ������� ����
//		i++;
//	}
//
//	CRect pageFormWndRect;
//	pageForm->GetWindowRect(&pageFormWndRect);
//
//	if (docWndRect.right < xPosition) {
//		position = xPosition - docWndRect.Width() + 50 - pageFormWndRect.left;
//		this->GetHorizontalScroll()->ScrollToPosition(position);
//	}
//
//	if (docWndRect.left > xPosition) {
//		position = xPosition - docWndRect.Width() + 50 - pageFormWndRect.left;
//		this->GetHorizontalScroll()->ScrollToPosition(position);
//	}
//	
//	if (docWndRect.top > yPosition) {
//		position = yPosition - docWndRect.Height() + height + 50 - pageFormWndRect.top;
//		this->GetVerticalScroll()->ScrollToPosition(position);
//	}
//
//	if (docWndRect.bottom < yPosition) {
//		position = yPosition - docWndRect.Height() + height + 50 - pageFormWndRect.top;
//		this->GetVerticalScroll()->ScrollToPosition(position);
//	}
//}

#include "FindIndex.h"
void OtherNoteForm::ScrollToFindIndex(FindIndex *findIndex) {
	PageForm *pageForm = this->GetPageForm(static_cast<Note*>(this->GetContents())->GetCurrent());
	if (findIndex->GetPageIndex() != static_cast<Note*>(this->GetContents())->GetCurrent()) {
		//pageForm->CleanUpMemoForms();
		pageForm->ShowWindow(SW_HIDE);

		static_cast<TabCtrl*>(this->GetTabCtrl())->SetCurSel(findIndex->GetPageIndex());
		this->SelectTabItem(findIndex->GetPageIndex());
		this->GetHorizontalScroll()->SetCurrent(findIndex->GetPageIndex());
		this->GetVerticalScroll()->SetCurrent(findIndex->GetPageIndex());
	}
	
	//1027 zorder
	Long memoFormIndex = 0;
	//PageForm *tempPageForm = this->GetPageForm((static_cast<Note*>(this->GetContents()))->GetCurrent());
	PageForm *tempPageForm = this->GetPageForm(findIndex->GetPageIndex());
	MemoForm *tempMemoForm = findIndex->GetMemoIndex();
	while (memoFormIndex < tempPageForm->GetLength()
		&& tempPageForm->GetMemoForm(memoFormIndex) != tempMemoForm) {
		memoFormIndex++;
	}
	//
	//static_cast<Page*>(this->GetPageForm((static_cast<Note*>(this->GetContents()))->GetCurrent())->GetContents())->SetCurrent(findIndex->GetMemoIndex());
	static_cast<Page*>(this->GetPageForm((static_cast<Note*>(this->GetContents()))->GetCurrent())->GetContents())->SetCurrent(memoFormIndex);
	pageForm = this->GetPageForm(static_cast<Note*>(this->GetContents())->GetCurrent());
	//MemoForm *memoForm = pageForm->GetMemoForm(findIndex->GetMemoIndex());
	MemoForm *memoForm = findIndex->GetMemoIndex();
	Memo *memo = static_cast<Memo*>(pageForm->GetMemoForm(static_cast<Page*>(pageForm->GetContents())->GetCurrent())->GetContents());
	memo->SetRow(findIndex->GetRow());
	Line *line = memo->GetLine(memo->GetRow());
	line->SetColumn(findIndex->GetColumn());

	//Long length = this->findingForm->GetKey().GetLength();
	Long length = this->findingForm->GetKeyLength();
	Long row = findIndex->GetRow();
	Long column = findIndex->GetColumn();
	column = column + length - 1;

	CRect memoFormWndRect;
	memoForm->GetWindowRect(&memoFormWndRect);
	pageForm->ScreenToClient(&memoFormWndRect);

	Long xPosition = memoFormWndRect.left + memoForm->GetMarginWidth() - 50;
	Long yPosition = memoFormWndRect.top + memoForm->GetMarginHeight() + memoForm->GetCaptionHeight() - 50;
	CharacterFaces *characterFaces = CharacterFaces::Instance(memoForm->GetDC());
	CharacterSize characterSize = characterFaces->GetCharacterSize(97);
	Long height = characterSize.GetHeight();

	Long i = 0;
	while (i < row) {
		yPosition += height;
		i++;
	}

	i = 0;
	while (i < column) {
		xPosition += line->GetCharacter(i)->GetWidth();
		i++;
	}

	this->GetHorizontalScroll()->ScrollToPosition(xPosition);
	this->GetVerticalScroll()->ScrollToPosition(yPosition);
}

#include "PrintPreview.h"
void OtherNoteForm::OnFilePrintPreview() {
	//1022 VerticalScroll ĳ�� ��� ���� ���1: ���α׷� ���� > �� �޸� ���� > �޴� > �̸����� > �̸����� �ݱ�
	this->GetDocumentWnd()->SetFocus();
	
	//1. �̸����⸦ ���� CFrameWnd�� �����Ѵ�.
	this->printPreview = new PrintPreview;

	int systemCX = GetSystemMetrics(SM_CXFULLSCREEN);	//2160
	int systemCY = GetSystemMetrics(SM_CYFULLSCREEN);	//1357

	CString printPreviewClass = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW, NULL, (HBRUSH)GetStockObject(WHITE_BRUSH), NULL);
	this->printPreview->CreateEx(0, printPreviewClass, "�μ�̸�����", WS_OVERLAPPEDWINDOW | WS_MAXIMIZE | WS_VISIBLE, CRect(0,0,systemCX,systemCY), this, 0, NULL);
	//this->printPreview->Create(NULL, "PrintPreview", WS_OVERLAPPEDWINDOW | WS_MAXIMIZE, CFrameWnd::rectDefault, NULL, 0, 0, NULL);
	
	this->printPreview->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
}

//�����͸� ĵ���ϰ� otherNote�� �����ϸ� �״´�.
#include "PrintingForm.h"
void OtherNoteForm::OnFilePrint() {	
	this->GetDocumentWnd()->SetFocus();
	//1. ���̾�α� �ڽ� ���
	//this->printingForm = new PrintingForm(FALSE, PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS
	//	| PD_HIDEPRINTTOFILE | PD_NOSELECTION, NULL);
	//if (printingForm->DoModal() == IDCANCEL) {
	//	this->printingForm->OnClose();
	//	//this->printingForm->CloseWindow();
	//	this->printingForm = NULL;
	//	return;
	//}
	//this->printingForm->Print();

	this->printingForm = new PrintingForm(FALSE, PD_ALLPAGES | PD_USEDEVMODECOPIES | PD_NOPAGENUMS
		| PD_HIDEPRINTTOFILE | PD_NOSELECTION, NULL);
	if (printingForm->DoModal() == IDCANCEL) {
		printingForm->OnClose();
		return;
	}
	this->printingForm->Print();

	/*CPrintDialog printDlg(FALSE);
	if (printDlg.DoModal() == IDCANCEL) {
		return;
	}*/
	//::DeleteDC(printDlg.m_pd.hDC);
	/*::GlobalFree(printDlg.m_pd.hDevMode);
	::GlobalFree(printDlg.m_pd.hDevNames);*/

	//printDlg.m_pd.hDC = NULL;
	/*printDlg.m_pd.hDevMode = NULL;
	printDlg.m_pd.hDevNames = NULL;*/
	
	//printDlg.EndDialog(IDCANCEL);
	//printDlg.CloseWindow();
	//if (printDlg.DoModal() == IDCANCEL) {
	//	//GlobalFree(printDlg);
	//	//DeleteDC(printDlg.GetPrinterDC());
	//	//DeleteDC(printDlg.m_pd.hDC);
	//}
}

BOOL OtherNoteForm::PreCreateWindow(CREATESTRUCT& cs) {
	CFrameWnd::PreCreateWindow(cs);
	WNDCLASS wndClass;
	::ZeroMemory(&wndClass, sizeof(WNDCLASS));
	::GetClassInfo(AfxGetInstanceHandle(), _T("#32770"), &wndClass);
	wndClass.lpszClassName = _T("OtherNote");
	AfxRegisterClass(&wndClass);
	return TRUE;
}

//--------------------------------------------
//<< OtherNote ���� >>
//--------------------------------------------
//�ΰ�
//Team.Avengers
//OtherNote Project Ver 1.0
//���2017 All rights reserved.
//
//                                 [Ȯ��]
//--------------------------------------------
#include <atlimage.h>
void OtherNoteForm::OnMenuInformation() {
	this->GetDocumentWnd()->SetFocus();
	CDialog information(IDD_DIALOG_INFORMATION);
	information.DoModal();
	
	/*CStatic *icon = (CStatic*)GetDlgItem(IDC_STATIC_LOGO);
	CImage CImg;
	icon->Create(_T("A bitmap static control (B)"),
		WS_CHILD | WS_BORDER | WS_VISIBLE | SS_BITMAP | SS_CENTERIMAGE, CRect(90, 16, 138, 64),
		this);
	CImg.Load(_T("Logo2_text.png"));
	if (icon->GetBitmap() == NULL)
		icon->SetBitmap(HBITMAP(CImg));*/

	//information.DoModal();
}

void OtherNoteForm::OnSetFocus(CWnd *pOldWnd) {
	CWnd::OnSetFocus(pOldWnd);

	/*PageForm *pageForm = this->GetPageForm(static_cast<Note*>(this->GetContents())->GetCurrent());
	pageForm->GetMemoForm(pageForm->GetLength() - 1)->RedrawWindow(NULL, NULL, RDW_INVALIDATE);*/
}

void OtherNoteForm::SetDefaultMemoColor(Long color) {
	this->defaultMemoColor = color;
}