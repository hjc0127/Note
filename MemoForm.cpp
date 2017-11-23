//MemoForm.cpp

#include "MemoForm.h"
#include "Form.h"
#include "Memo.h"
#include "Line.h"
#include "Character.h"
#include "Visitor.h"
#include "CharacterFaces.h"
#include "PaintVisitor.h"
#include "ArrayIterator.h"
#include "Caret.h"
#include "SelectedBuffer.h"
#include "MakeStringVisitor.h"
#include "HighLightVisitor.h"
#include "HorizontalScroll.h"
#include "VerticalScroll.h"
#include "KeyActionCreator.h"
#include "KeyAction.h"
#include "DeleteKey.h"
//#include "Mouse.h"

#define MEMOFORM_WIDTH 300
#define MEMOFORM_HEIGHT 200

BEGIN_MESSAGE_MAP(MemoForm, CWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	//ON_WM_SIZE()
	ON_WM_CHAR()
	ON_MESSAGE(WM_IME_COMPOSITION, OnImeComposition)
	ON_WM_KEYDOWN()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_MOUSEACTIVATE()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCRBUTTONDOWN()
	ON_COMMAND(ID_MEMOFORM_HIGHLIGHT, OnHighLight)
	ON_COMMAND(ID_MEMOFORM_UNHIGHLIGHT, OnUnHighLight)
	ON_COMMAND(ID_MEMOFORM_COLOR_PURPLE, ChangeColorToPurple)
	ON_COMMAND(ID_MEMOFORM_COLOR_YELLOW, ChangeColorToYellow)
	ON_COMMAND(ID_MEMOFORM_COLOR_GREEN, ChangeColorToGreen)
	ON_COMMAND(ID_MEMOFORM_COLOR_BLUE, ChangeColorToBlue)
	ON_COMMAND(ID_MEMOFORM_COLOR_PINK, ChangeColorToPink)
	ON_COMMAND(ID_MEMOFORM_COLOR_GRAY, ChangeColorToGray)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOVING()
	ON_WM_MOVE()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

MemoForm::MemoForm(Contents* contents, Long positionX, Long positionY, Long width, Long height, Long color, Long highLightCapacity, Long marginWidth, Long marginHeight, Long captionHeight)
	:Form(contents), highLights(highLightCapacity) {
	this->endComposition = true;
	this->positionX = positionX;
	this->positionY = positionY;
	//this->caret = new Caret(this);
	this->caret = 0;
	this->selectedBuffer = 0;
	this->maxWidth = width;
	this->maxHeight = height;
	this->isCaption = false;
	this->highLightCapacity = 100;
	this->highLightLength = 0;
	this->marginWidth = marginWidth;
	this->marginHeight = marginHeight;
	this->captionHeight = captionHeight;
	this->isFocused = FALSE;
	this->isHovered = FALSE;
	//this->colorType = MEMOFORM_COLOR_PURPLE;
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
	if (color == -1) {
		this->colorType = otherNoteForm->GetDefaultMemoColor();
	}
	else {
		this->colorType = color;
	}
	//this->colorType = color;
	//this->colorType = color;
	this->focusType = MEMOFORM_FOCUS_CAPTION;
}

#include "OtherNoteForm.h"
MemoForm::~MemoForm() {
	if (this->caret != 0) {
		delete this->caret;
	}

	if (this->selectedBuffer != 0) {
		delete this->selectedBuffer;
	}
}

MemoForm::MemoForm(const MemoForm& source)
	:Form(source), highLights(source.highLightCapacity) {
	this->endComposition = source.endComposition;
	this->positionX = source.positionX;
	this->positionY = source.positionY;
	this->caret = 0;
	this->selectedBuffer = 0;
	this->maxWidth = source.maxWidth;
	this->maxHeight = source.maxHeight;
	this->isCaption = source.isCaption;
	this->marginWidth = source.marginWidth;
	this->marginHeight = source.marginHeight;
	this->captionHeight = source.captionHeight;
	this->highLightCapacity = source.highLightCapacity;
	this->highLightLength = source.highLightLength;

	/*this->isFocused = source.isFocused;
	this->isHovered = source.isHovered;
	this->focusType = source.focusType;*/
	this->colorType = source.colorType;

	Long i = 0;
	while (i < this->highLightLength) {
		this->highLights.Store(i, (const_cast<MemoForm&>(source)).highLights.GetAt(i));
		i++;
	}	
}

MemoForm& MemoForm::operator = (const MemoForm& source) {
	this->endComposition = source.endComposition;
	this->positionX = source.positionX;
	this->positionY = source.positionY;
	this->caret = 0;
	this->selectedBuffer = 0;
	this->maxWidth = source.maxWidth;
	this->maxHeight = source.maxHeight;
	this->isCaption = source.isCaption;
	this->marginWidth = source.marginWidth;
	this->marginHeight = source.marginHeight;
	this->captionHeight = source.captionHeight;
	this->highLightCapacity = source.highLightCapacity;
	this->highLightLength = source.highLightLength;
	this->colorType = source.colorType;

	Long i = 0;
	while (i < this->highLightLength) {
		if (this->highLights.GetAt(i) != 0) {
			delete this->highLights.GetAt(i);
		}
		i++;
	}
	this->highLights = source.highLights;
	i = 0;
	while (i < source.highLightLength) {
		this->highLights.Modify(i, (const_cast<MemoForm&>(source)).highLights.GetAt(i));
		i++;
	}
	
	return *this;
}

Form* MemoForm::Clone() const {
	return new MemoForm(*this);
}

void MemoForm::Accept(Visitor* visitor) {
	visitor->Visit(this);
}

int MemoForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct);

	if (this->caret == 0) {
		this->caret = new Caret(this);
	}
	
	if (this->selectedBuffer == 0) {
		this->selectedBuffer = new SelectedBuffer(this, 0, 0);
	}

	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	//this->caret->ShowCaret();
	return 0;
}

void MemoForm::SetSelectedBuffer(SelectedBuffer* selectedBuffer) {
	this->selectedBuffer = selectedBuffer;
}

#include "PageForm.h"
#include "Page.h"
#include "Note.h"
void MemoForm::OnClose() {
	CWnd::OnClose();
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
	Note *note = (Note*)(otherNoteForm->GetContents());
	PageForm *pageForm = static_cast<PageForm*>(this->GetParent());
	Page *page = static_cast<Page*>(pageForm->GetContents());
	Long i = 0;
	while (page->GetMemo(i) != static_cast<Memo*>(this->contents)) {
		i++;
	}

	page->SetCurrent(i);
	pageForm->RemoveMemoForm(page->GetCurrent());
	page->RemoveMemo();
	pageForm->HoverMemo(NULL);
}

#include "SelectedBuffer.h"
#include "PaintSelectionVisitor.h"
#include "SingleCharacter.h"
#include "DoubleCharacter.h"
#include "PaintFindIndexVisitor.h"
#include "BufferDC.h"
#include "FocusVisitor.h"
#include "HoverVisitor.h"
void MemoForm::OnPaint() {
	//this->ReSizeWindow();

	BufferDC dc(this);
	CRect rect;
	this->GetClientRect(&rect);

	PaintVisitor paintVisitor(&dc, &rect);
	this->contents->Accept(&paintVisitor);

	if (this->isFocused == TRUE) {
		FocusVisitor focusVisitor(&dc, &rect);
		this->contents->Accept(&focusVisitor);
	}

	else if (this->isHovered == TRUE) {
		HoverVisitor hoverVisitor(&dc, &rect);
		this->contents->Accept(&hoverVisitor);
	}
	
	PaintFindIndexVisitor paintFindIndexVisitor(&dc);
	this->GetContents()->Accept(&paintFindIndexVisitor);

	HighLightVisitor highLightVisitor(&dc, &rect);
	this->GetContents()->Accept(&highLightVisitor);
	
	PaintSelectionVisitor paintSelectionVisitor(&dc);
	this->Accept(&paintSelectionVisitor);

	//CWnd::OnPaint();
}

void MemoForm::CalculatePosition(Long *xPos, Long *yPos) {
	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	CharacterSize characterSize = characterFaces->GetCharacterSize(127);
	*xPos = 0;
	*yPos = 0;

	Long beginRow = this->selectedBuffer->GetBeginRow();
	Long i = 0;
	while (i < beginRow) {
		*yPos += characterSize.GetHeight();
		i++;
	}
	Line *beginLine = static_cast<Memo*>(this->GetContents())->GetLine(beginRow);
	Long beginColumn = this->selectedBuffer->GetBeginColumn();
	Long j = 0;
	while (j < beginColumn) {
		*xPos += beginLine->GetCharacter(j)->GetWidth();
		j++;
	}
}

void MemoForm::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar >= 32 && nChar <= 126) {
		KeyActionCreator keyActionCreator;
		KeyAction *keyAction = keyActionCreator.Create(this, nChar, nRepCnt, nFlags, WM_CHAR);
		if (keyAction != 0) {
			keyAction->OnKeyDown(nChar, nRepCnt, nFlags);
			delete keyAction;
			keyAction = 0;
		}
	}
}

Long MemoForm::UpdateMaxWidth() {
	Memo *memo = static_cast<Memo*>(this->GetContents());
	Long widthOfLine = 0;
	this->maxWidth = MEMOFORM_WIDTH;
	Long i = 0;
	while (i < memo->GetLength()) {
		widthOfLine = MEMOFORM_MARGIN_LEFT + MEMOFORM_MARGIN_RIGHT;
		Line *line = memo->GetLine(i);
		Long j = 0;
		while (j < line->GetLength()) {
			widthOfLine += line->GetCharacter(j)->GetWidth();
			j++;
		}
		if (this->maxWidth < widthOfLine) {
			this->maxWidth = widthOfLine;
		}
		i++;
	}
	if (this->maxWidth < MEMOFORM_WIDTH) {
		this->maxWidth = MEMOFORM_WIDTH;
	}

	return this->maxWidth;
}

Long MemoForm::UpdateMaxHeight() {
	Memo *memo = static_cast<Memo*>(this->GetContents());
	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	Long heightOfMemoForm = MEMOFORM_MARGIN_BOTTOM + MEMOFORM_MARGIN_TOP + MEMOFORM_CAPTION_HEIGHT; //1106
	this->maxHeight = MEMOFORM_HEIGHT;
	Long i = 0;
	while (i < memo->GetLength()) {
		heightOfMemoForm += characterFaces->GetCharacterSize(97).GetHeight();

		if (this->maxHeight < heightOfMemoForm) {
			this->maxHeight = heightOfMemoForm;
		}
		i++;
	}
	if (this->maxHeight < MEMOFORM_HEIGHT) {
		this->maxHeight = MEMOFORM_HEIGHT;
	}

	return this->maxHeight;
}

void MemoForm::ReSizeWindow() {
	CRect previousRect;
	this->GetWindowRect(&previousRect);
	this->UpdateMaxWidth();
	this->UpdateMaxHeight();

	this->SetWindowPos(0, this->GetPositionX(), this->GetPositionY(), this->maxWidth, this->maxHeight, SWP_NOMOVE | SWP_NOZORDER);
	//느림의 주인공 1109
	//static_cast<PageForm*>(this->GetParent())->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_NOERASE);
	//static_cast<PageForm*>(this->GetParent())->Redraw();
}

#include <imm.h>
LRESULT MemoForm::OnImeComposition(WPARAM wParam, LPARAM lParam) {
	this->SetFocusType(MEMOFORM_FOCUS_CLIENT);
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);
	Memo *tempMemo = static_cast<Memo*>(this->GetContents());
	Line *line = static_cast<Memo*>(this->GetContents())->GetLine(tempMemo->GetRow());
	Memo *copyMemo = static_cast<Memo*>(tempMemo->Clone());
	//if (this->isCaption == false) {
	if (this->selectedBuffer->GetIsSelecting() == true) {
		DeleteKey deleteKey = DeleteKey(this);
		deleteKey.OnKeyDown(0, 0, 0);
		this->selectedBuffer->SetIsSelecting(false);
	}

	char composition[2];
	composition[0] = HIBYTE(wParam);
	composition[1] = LOBYTE(wParam);

	Line *lineLink = static_cast<Memo*>(this->contents)->GetLine(static_cast<Memo*>(this->contents)->GetRow());

	//Caret *caret = Caret::Instance(0);
	//this->caret->ChangeImeCaret(); //1109
	this->caret->UpdateCaret();

	if (lParam & GCS_COMPSTR) {
		if (this->endComposition == false) {
			lineLink->Erase();
		}
		this->endComposition = false;
		if (!(composition[1] == '\x1b' && composition[0] == '\0')) {
			lineLink->Write(composition);
			this->caret->UpdateCaret(); // 1109
		}
		else {
			this->endComposition = true;
			//this->caret->ChangeCaret();
			this->caret->UpdateCaret(); //1109
		}
		this->AutoReturnIme();
		this->caret->UpdateCaret();

		Long heightOfMemoForm = MEMOFORM_MARGIN_BOTTOM + MEMOFORM_MARGIN_TOP + MEMOFORM_CAPTION_HEIGHT;
		CharacterFaces *characterFaces = CharacterFaces::Instance(0);
		Long characterHeight = characterFaces->GetCharacterSize(97).GetHeight();
		Long j = 0;
		while (j < tempMemo->GetLength()) {
			heightOfMemoForm += characterHeight;
			j++;
		}
		
		OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
		CRect memoFormWndRect;
		this->GetWindowRect(&memoFormWndRect);
		CRect pageFormWndRect;
		static_cast<PageForm*>(this->GetParent())->GetWindowRect(&pageFormWndRect);
		if (memoFormWndRect.top + heightOfMemoForm >= pageFormWndRect.top + PAGEFORM_MAX_HEIGHT) {
			delete this->GetContents();
			this->SetContents(copyMemo);
			/*Long row = static_cast<Memo*>(this->GetContents())->GetRow();
			Long column = static_cast<Memo*>(this->GetContents())->GetLine(row)->GetColumn();
			static_cast<Memo*>(this->GetContents())->GetLine(row)->SetColumn(column - 1);
			this->GetCaret()->UpdateCaret();
			static_cast<Memo*>(this->GetContents())->GetLine(row)->SetColumn(column);*/
			//this->
			this->caret->UpdateCaret();
		}
		else {
			// 스크롤 하는부분 ///////////////////////////////////////////////////////////////////////////////////////
			static_cast<PageForm*>(this->GetParent())->UpdateSize(this);
			CPoint point;
			//this->GetCaret()->UpdateCaret();
			/*point.x = this->GetCaret()->GetXPosition();
			point.y = this->GetCaret()->GetYPosition();*/
			this->GetCaretPos(&point.x, &point.y);
			CRect docWndRect;
			otherNoteForm->GetDocumentWnd()->GetWindowRect(&docWndRect);
			this->ClientToScreen(&point);
			if (point.x + 50 > docWndRect.right) {
				otherNoteForm->GetHorizontalScroll()->ScrollNext(point.x + 50 - docWndRect.right);
			}
			else if (point.x < docWndRect.left) {
				otherNoteForm->GetHorizontalScroll()->ScrollPrevious(docWndRect.left - point.x + 50);
			}
		}
	}
	if (lParam & GCS_RESULTSTR) {
		this->endComposition = true;
		lineLink->Erase();
		lineLink->Write(composition);
		//this->caret->MoveNextCharacter();
		this->caret->UpdateCaret();
		//this->caret->ChangeCaret();  1109
	}
	this->ReSizeWindow(); //11/12 한글입력시 리사이트 안되는 버그 수정

	////OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow(NULL, "OtherNote"));
	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
	//CRect docWndRect;
	//otherNoteForm->GetDocumentWnd()->GetWindowRect(&docWndRect);
	//CRect memoFormRect;
	//this->GetWindowRect(&memoFormRect);
	//CRect pageFormWndRect;
	//this->GetParent()->GetWindowRect(&pageFormWndRect);
	//if (memoFormRect.right > docWndRect.right) {
	//	if (pageFormWndRect.right + 2 == docWndRect.right) {
	//		static_cast<PageForm*>(this->GetParent())->ResizeWindow(150, 0);
	//		otherNoteForm->GetHorizontalScroll()->UpdateScrinfo(static_cast<PageForm*>(this->GetParent())->GetHScrinfo());
	//	}
	//	otherNoteForm->GetHorizontalScroll()->ScrollNext(150);
	//}
	//if (memoFormRect.bottom > docWndRect.bottom) {
	//	//1. 페이지폼 증가 상황
	//	if (pageFormWndRect.bottom + 2 == docWndRect.bottom) {
	//		static_cast<PageForm*>(this->GetParent())->ResizeWindow(0, 150);
	//		otherNoteForm->GetVerticalScroll()->UpdateScrinfo(static_cast<PageForm*>(this->GetParent())->GetVScrinfo());
	//	}
	//	//2. 스크롤 아래쪽을 이동
	//	otherNoteForm->GetVerticalScroll()->ScrollNext(150);
	//}

	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_NOERASE);
	//}
	return 0;
}

void MemoForm::AutoReturn() {
	Memo *tempMemo = static_cast<Memo*>(this->GetContents());
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	CRect memoFormWndRect;
	this->GetWindowRect(&memoFormWndRect);
	CRect pageFormWndRect;
	static_cast<PageForm*>(this->GetParent())->GetWindowRect(&pageFormWndRect);

	Long i = tempMemo->GetRow();
	Long row = tempMemo->GetRow();
	Line *line = static_cast<Memo*>(this->GetContents())->GetLine(i);
	Long currentColumn = line->GetColumn() - 1;
	//Memo *copyMemo = static_cast<Memo*>(tempMemo->Clone());
	//line->Write(nChar);

	Long lineWidth = line->GetWdith();
	while (memoFormWndRect.left + MEMOFORM_MARGIN_LEFT + lineWidth + MEMOFORM_MARGIN_RIGHT > pageFormWndRect.left + PAGEFORM_MAX_WIDTH) {
		while (memoFormWndRect.left + MEMOFORM_MARGIN_LEFT + lineWidth + MEMOFORM_MARGIN_RIGHT > pageFormWndRect.left + PAGEFORM_MAX_WIDTH) {
			Character *tempCharacter2 = static_cast<Character*>(line->GetCharacter(line->GetLength() - 1)->Clone());
			//SingleCharacter *tempCharacter = static_cast<SingleCharacter*>(line->GetCharacter(line->GetLength() - 1)->Clone());
			line->Erase(line->GetLength() - 1);
			CharacterFaces *characterFaces = CharacterFaces::Instance(0);
			Long characterHeight = characterFaces->GetCharacterSize(97).GetHeight();
			if (tempMemo->GetLength() == i + 1) {
				Long row = tempMemo->GetRow();
				Long index = tempMemo->AddLine();
				tempMemo->SetRow(row);
			}
			tempMemo->GetLine(i + 1)->SetColumn(0);
			if (dynamic_cast<SingleCharacter*>(tempCharacter2)) {
				tempMemo->GetLine(i + 1)->Write(static_cast<SingleCharacter*>(tempCharacter2)->GetValue());
			}
			else {
				tempMemo->GetLine(i + 1)->Write(static_cast<DoubleCharacter*>(tempCharacter2)->GetValue());
			}
			if (currentColumn - 1 == line->GetLength() - 1 && i == row) {
				tempMemo->SetRow(i + 1);
			}
			if (tempCharacter2 != 0) {
				delete tempCharacter2;
			}
			lineWidth = line->GetWdith();
		}
		i++;
		line = tempMemo->GetLine(i);
		lineWidth = line->GetWdith();
	}
}

void MemoForm::AutoReturnIme() {
	Memo *tempMemo = static_cast<Memo*>(this->GetContents());
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	CRect memoFormWndRect;
	this->GetWindowRect(&memoFormWndRect);
	CRect pageFormWndRect;
	static_cast<PageForm*>(this->GetParent())->GetWindowRect(&pageFormWndRect);

	Long i = tempMemo->GetRow();
	Long row = tempMemo->GetRow();
	Line *line = static_cast<Memo*>(this->GetContents())->GetLine(i);
	Long currentColumn = line->GetColumn() - 1;
	//Memo *copyMemo = static_cast<Memo*>(tempMemo->Clone());
	//line->Write(nChar);
	Long fixedRow = row;
	Long fixedColumn = line->GetColumn();
	Long lineWidth = line->GetWdith();
	bool flag1 = false;
	bool flag2 = false;

	if (memoFormWndRect.left + MEMOFORM_MARGIN_LEFT + lineWidth + MEMOFORM_MARGIN_RIGHT > pageFormWndRect.left + PAGEFORM_MAX_WIDTH) {
		flag1 = true;
		if (line->GetLength() == line->GetColumn()) {
			flag2 = true;
			fixedRow++;
			fixedColumn = 0;
		}
	}
	while (memoFormWndRect.left + MEMOFORM_MARGIN_LEFT + lineWidth + MEMOFORM_MARGIN_RIGHT > pageFormWndRect.left + PAGEFORM_MAX_WIDTH) {
		while (memoFormWndRect.left + MEMOFORM_MARGIN_LEFT + lineWidth + MEMOFORM_MARGIN_RIGHT > pageFormWndRect.left + PAGEFORM_MAX_WIDTH) {
			Character *tempCharacter2 = static_cast<Character*>(line->GetCharacter(line->GetLength() - 1)->Clone());
			//SingleCharacter *tempCharacter = static_cast<SingleCharacter*>(line->GetCharacter(line->GetLength() - 1)->Clone());
			line->Erase(line->GetLength() - 1);
			CharacterFaces *characterFaces = CharacterFaces::Instance(0);
			Long characterHeight = characterFaces->GetCharacterSize(97).GetHeight();
			if (tempMemo->GetLength() == i + 1) {
				Long row = tempMemo->GetRow();
				Long index = tempMemo->AddLine();
				//1106
				static_cast<Memo*>(this->GetContents())->GetLine(index)->MoveFirstColumn();
				this->GetCaret()->UpdateCaret();
				

				tempMemo->SetRow(row);
			}
			tempMemo->GetLine(i + 1)->SetColumn(0);
			if (dynamic_cast<SingleCharacter*>(tempCharacter2)) {
				tempMemo->GetLine(i + 1)->Write(static_cast<SingleCharacter*>(tempCharacter2)->GetValue());
			}
			else {
				/*Long column = tempMemo->GetLine(i + 1)->GetColumn();
				if (column > 0) {
					column -= 1;
				}
				tempMemo->GetLine(i + 1)->SetColumn(column);*/
				
				tempMemo->GetLine(i + 1)->Write(static_cast<DoubleCharacter*>(tempCharacter2)->GetValue());
			}
			if (currentColumn - 1 == line->GetLength() - 1 && i == row) {
				tempMemo->SetRow(i + 1);
			/*	if (tempMemo->GetLine(i + 1)->GetLength() != 1) {
					static_cast<Memo*>(this->GetContents())->GetLine(i + 1)->SetColumn(1);
					if (this->endComposition == TRUE) {
						static_cast<Memo*>(this->GetContents())->GetLine(i + 1)->SetColumn(0);
					}
					this->GetCaret()->UpdateCaret();
				}*/
			}
			if (tempCharacter2 != 0) {
				delete tempCharacter2;
			}
			lineWidth = line->GetWdith();
		}
		i++;
		line = tempMemo->GetLine(i);
		lineWidth = line->GetWdith();
	}
}

#include "FindingForm.h"
void MemoForm::OnSetFocus(CWnd *pOldWnd) {
	CWnd::OnSetFocus(pOldWnd);
	this->caret->ShowCaret();
	static_cast<PageForm*>(this->GetParent())->FocusMemo(this);
	this->isFocused = TRUE;
	this->BringWindowToTop();
	this->focusType = MEMOFORM_FOCUS_CAPTION;

	//
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
	FindingForm *findingForm = otherNoteForm->GetFindingForm();
	if (findingForm != NULL) {
		findingForm->SetIsEdited(true);
	}
}

void MemoForm::OnKillFocus(CWnd* pNewWnd) {
	CWnd::OnKillFocus(pNewWnd);
	//this->selectedBuffer->SetIsSelecting(false);
	this->caret->HideCaret();
	this->isFocused = FALSE;
	this->focusType = MEMOFORM_FOCUS_CLIENT;
	this->RedrawWindow();

	//
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
	FindingForm *findingForm = otherNoteForm->GetFindingForm();
	if (findingForm != NULL) {
		findingForm->SetIsEdited(false);
	}

	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
	Note *note = (Note*)(otherNoteForm->GetContents());
	PageForm *pageForm = otherNoteForm->GetPageForm(note->GetCurrent());
	Long lines = static_cast<Memo*>(this->GetContents())->GetLength();
	Long characters = static_cast<Memo*>(this->GetContents())->GetLine(0)->GetLength();
	//1022 전체 메모폼을 정리하기보단 해당 메모폼만 정리하는 방안으로 하는게 어떤지
	if (lines == 1 && characters == 0) {
		//pageForm->CleanUpMemoForms();
		this->OnClose();
	}
}

int MemoForm::OnMouseActivate(CWnd *pDesktopWnd, UINT nHitTest, UINT message) {
	this->SetFocus();
	
	return MA_ACTIVATE;
}

void MemoForm::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (nChar != VK_DELETE) {
		this->SetFocusType(MEMOFORM_FOCUS_CLIENT);
	}
	KeyActionCreator keyActionCreator;
	KeyAction *keyAction = keyActionCreator.Create(this, nChar, nRepCnt, nFlags, WM_KEYDOWN);
	if (keyAction != 0) {
		keyAction->OnKeyDown(nChar, nRepCnt, nFlags);
		delete keyAction;
		keyAction = 0;
	}
}

void MemoForm::SetPositionX(Long positionX) {
	this->positionX = positionX;
}

void MemoForm::SetPositionY(Long poisitionY) {
	this->positionY = poisitionY;
}

LRESULT MemoForm::OnNcHitTest(CPoint point) {
	CWnd::OnNcHitTest(point);
	CRect wndRect;
	this->GetWindowRect(&wndRect);
	if (point.y < wndRect.top + this->captionHeight && point.y > wndRect.top) {
		return HTCAPTION;
	}
	return HTCLIENT;
}

void MemoForm::SetIsCaption(bool isCaption) {
	this->isCaption = isCaption;
}

void MemoForm::SetMaxWidth(Long width) {
	this->maxWidth = width;
}

void MemoForm::SetMaxHeight(Long height) {
	this->maxHeight = height;
}

void MemoForm::OnNcRButtonDown(UINT nHitTest, CPoint point) {
	CMenu menu;
	menu.LoadMenu(IDR_MENU_MEMOFORM_COLOR);
	CMenu *popupMenu = menu.GetSubMenu(0);
	CPoint position;
	GetCursorPos(&position);
	popupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, position.x, position.y, this);
	menu.DestroyMenu();
}


void MemoForm::OnNcLButtonDown(UINT nHitTest, CPoint point) {
	//CWnd::OnNcLButtonDown(nHitTest, point);
	this->SetIsCaption(true);

	this->SetFocusType(MEMOFORM_FOCUS_CAPTION);
	//this->HideCaret();
	this->selectedBuffer->SetInitialPosition(0, 0);

	//자료구조 끝 계산
	Long endRow;
	Long endColumn;
	endRow = static_cast<Memo*>(this->GetContents())->GetLength() - 1;
	endColumn = static_cast<Memo*>(this->GetContents())->GetLine(endRow)->GetLength();

	//영역 복사해서 buffer에 저장
	this->selectedBuffer->CopyToBuffer(endRow, endColumn);
	//영역체크 유효화(선택보여주기)
	this->selectedBuffer->SetIsSelecting(true);

	//zorder 이슈 호출해준 부분
	//this->SetWindowPos(&wndBottom, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_NOERASE);

	//캐럿을 나중에 출력하기 위해서 제일 마지막에 둔다
	static_cast<PageForm*>(this->GetParent())->FocusMemo(this);
	this->SetFocus();

	static_cast<Memo*>(this->GetContents())->SetRow(endRow);
	static_cast<Line*>(static_cast<Memo*>(this->GetContents())->GetLine(endRow))->SetColumn(endColumn);

	this->caret->UpdateCaret();
	CWnd::OnNcLButtonDown(nHitTest, point);
}

void MemoForm::OnSetHighLight() {
	HighLight *highLight = new HighLight(this, this->selectedBuffer->GetBeginRow(), this->selectedBuffer->GetBeginColumn(), this->selectedBuffer->GetEndRow(), this->selectedBuffer->GetEndColumn());
	highLight->CopyToHighLightBuffer();

	Long index;
	if (this->highLightCapacity > this->highLightLength) {
		index = this->highLights.Store(this->highLightLength, highLight);
	}
	else {
		index = this->highLights.AppendFromRear(highLight);
		this->highLightCapacity++;
	}
	this->highLightLength++;

	this->RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_NOERASE);
}

void MemoForm::OnHighLight() {
	Long startColumn = this->selectedBuffer->GetBeginColumn();
	Long startRow = this->selectedBuffer->GetBeginRow();
	Long endColumn = this->selectedBuffer->GetEndColumn();
	Long endRow = this->selectedBuffer->GetEndRow();

	static_cast<Memo*>(this->contents)->SetHighLightMode(startRow, startColumn, endRow, endColumn, true);
	CDC *dc = this->GetDC();

	CRect rect;
	this->GetClientRect(&rect);
	HighLightVisitor highLightVisitor(dc, &rect);
	this->GetContents()->Accept(&highLightVisitor);
	ReleaseDC(dc);
	/*1. 강조하기 이후에 선택영역이 사라지지 않는다 - done
	2. 강조하기 위로는 선택영역 표시가 나타나지 않는다*/
}


#include "UnHighLightVisitor.h"
void MemoForm::OnUnHighLight() {
	Long startColumn = this->selectedBuffer->GetBeginColumn();
	Long startRow = this->selectedBuffer->GetBeginRow();
	Long endColumn = this->selectedBuffer->GetEndColumn();
	Long endRow = this->selectedBuffer->GetEndRow();

	static_cast<Memo*>(this->contents)->SetHighLightMode(startRow, startColumn, endRow, endColumn, false);

	CDC *dc = this->GetDC();
	UnHighLightVisitor unHighLightVisitor(dc);
	this->GetContents()->Accept(&unHighLightVisitor);
	ReleaseDC(dc);
	/*1. 강조하기 이후에 선택영역이 사라지지 않는다 - done
	2. 강조하기 위로는 선택영역 표시가 나타나지 않는다*/
}

void MemoForm::UpdateIndex(CPoint point) {
	Memo *memo = static_cast<Memo*>(this->contents);
	memo->MoveFirstRow();
	Long height = this->captionHeight + this->marginHeight;
	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	//Todo : 버그 수정, 1010 0x208에러 발생 GetHeight()에서....
	Long characterHeight = characterFaces->GetCharacterSize(97).GetHeight();

	while (height < (point.y - this->caret->GetHeight()) && memo->GetRow() < memo->GetLength() - 1) {
		memo->MoveNextRow();
		height += characterHeight;
	}

	Line *line = memo->GetLine(memo->GetRow());
	line->MoveFirstColumn();
	Long previousXPos = this->marginWidth;
	Long currentXPos = this->marginWidth;
	while (currentXPos < point.x && line->GetColumn() < line->GetLength()) {
		previousXPos = currentXPos;
		currentXPos += line->GetCharacter(line->GetColumn())->GetWidth();
		line->MoveNextColumn();
	}

	if (currentXPos - point.x >= point.x - previousXPos && line->GetColumn() > 0) {
		line->MovePreviousColumn();
	}
}

bool MemoForm::IsFocused() {
	bool ret;
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(this->FindWindow("OtherNote", NULL));
	Note *note = (Note*)(otherNoteForm->GetContents());
	PageForm *pageForm = otherNoteForm->GetPageForm(note->GetCurrent());
	Page *page = note->GetPage(note->GetCurrent());
	Long index = page->GetCurrent();
	if (pageForm->GetMemoForm(index) == this) {
		ret = true;
	}
	else {
		ret = false;
	}

	return ret;
}

#include "MouseActionCreator.h"
#include "MouseAction.h"
#include "FindingForm.h"
void MemoForm::OnLButtonDown(UINT nFlags, CPoint point) {
	CWnd::OnLButtonDown(nFlags, point);
	this->SetFocusType(MEMOFORM_FOCUS_CLIENT);

	//OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	//FindingForm *findingForm = otherNoteForm->GetFindingForm();
	//if (findingForm != NULL) {
	//	//찾은단어의 글자들의 표시를 해제한다.
	//	findingForm->EraseFindIndexes();
	//	if (findingForm->GetLength() > 0) {
	//		//기존에 찾은 findIndex들을 삭제한다.
	//		Long i = 0;
	//		while (i <= findingForm->GetLength() - 1) {
	//			findingForm->RemoveFindIndex(i);
	//		}
	//		//기존tab에 색깔 원래 대로 칠하기
	//		findingForm->CancelFindingTabItem();
	//		//현제 페이지에 찾은 글자들을 해제한다
	//		otherNoteForm->GetPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent())->OnEraseFindIndexes();
	//	}
	//}

	MouseActionCreator mouseActionCreator;
	MouseAction *mouseAction = mouseActionCreator.Create(this, nFlags, point, WM_LBUTTONDOWN);
	if (mouseAction != 0) {
		mouseAction->OnMouseAction(nFlags, point);
		delete mouseAction;
		mouseAction = 0;
	}
}

void MemoForm::OnRButtonDown(UINT nFlags, CPoint point) {
	CWnd::OnRButtonDown(nFlags, point);
	this->SetFocusType(MEMOFORM_FOCUS_CLIENT);
	MouseActionCreator mouseActionCreator;
	MouseAction *mouseAction = mouseActionCreator.Create(this, nFlags, point, WM_RBUTTONDOWN);
	if (mouseAction != 0) {
		mouseAction->OnMouseAction(nFlags, point);
		delete mouseAction;
		mouseAction = 0;
	}
}

void MemoForm::OnMouseMove(UINT nFlags, CPoint point) {
	CWnd::OnMouseMove(nFlags, point);
	MouseActionCreator mouseActionCreator;
	if (nFlags == NULL) {
		MouseAction *mouseAction = mouseActionCreator.Create(this, point.x, point.y, WM_MOUSEMOVE);
		if (mouseAction != 0) {
			mouseAction->OnMouseAction(point.x, point.y);
			delete mouseAction;
			mouseAction = 0;
		}
	}
	else if (nFlags == MK_LBUTTON) {
		MouseAction *mouseAction = mouseActionCreator.Create(this, nFlags, point, WM_MOUSEMOVE);
		if (mouseAction != 0) {
			mouseAction->OnMouseAction(nFlags, point);
			delete mouseAction;
			mouseAction = 0;
		}
	}
}

void MemoForm::OnMove(int x, int y) {
	CWnd::OnMove(x, y);
	if (this->GetPositionX() != x) {
		this->SetPositionX(x);
	}

	if (this->GetPositionY() != y) {
		this->SetPositionY(y);
	}
}

void MemoForm::OnMoving(UINT nSide, LPRECT lpRect) {
	CWnd::OnMoving(nSide, lpRect);
	
	MouseActionCreator mouseActionCreator;
	MouseAction *mouseAction = mouseActionCreator.Create(this, nSide, lpRect, WM_MOVING);
	if (mouseAction != 0) {
		mouseAction->OnMouseAction(nSide, lpRect);
		delete mouseAction;
		mouseAction = 0;
	}
	this->RedrawWindow();
	//static_cast<PageForm*>(this->GetParent())->Redraw();
}

void MemoForm::RePosition() {
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CFrameWnd::FindWindow("OtherNote", NULL));
	CRect pageFormWndRect;
	static_cast<PageForm*>(this->GetParent())->GetWindowRect(&pageFormWndRect);
	CRect memoFormWndRect;
	this->GetWindowRect(&memoFormWndRect);
	
	CPoint cPoint;
	cPoint.x = memoFormWndRect.left;
	cPoint.y = memoFormWndRect.top;
	static_cast<PageForm*>(this->GetParent())->ScreenToClient(&cPoint);
	if (memoFormWndRect.right > pageFormWndRect.left + PAGEFORM_MAX_WIDTH) {
		this->SetWindowPos(0, PAGEFORM_MAX_WIDTH - memoFormWndRect.Width() - 10, cPoint.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		//this->RedrawWindow(NULL, NULL, RDW_NOERASE);
	}

	this->GetWindowRect(&memoFormWndRect);
	cPoint.x = memoFormWndRect.left;
	cPoint.y = memoFormWndRect.top;
	static_cast<PageForm*>(this->GetParent())->ScreenToClient(&cPoint);
	if (memoFormWndRect.bottom > pageFormWndRect.top + PAGEFORM_MAX_HEIGHT) {
		this->SetWindowPos(0, cPoint.x, PAGEFORM_MAX_HEIGHT - memoFormWndRect.Height() - 10, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		//this->RedrawWindow(NULL, NULL, RDW_NOERASE);
	}
}

#include "EraseFindIndexVisitor.h"
void MemoForm::OnEraseFindIndexes() {
	CDC *dc = this->GetDC();
	EraseFindIndexVisitor eraseFindIndexVisitor(dc);
	this->GetContents()->Accept(&eraseFindIndexVisitor);
	ReleaseDC(dc);
}

BOOL MemoForm::OnEraseBkgnd(CDC *pDC) {
	return TRUE;
}

BOOL MemoForm::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) {
	if (nHitTest == HTCLIENT) {
		CPoint point;
		GetCursorPos(&point);
		ScreenToClient(&point);
		CRect rect;
		this->GetClientRect(&rect);
		CRect memoClientRect(rect);
		memoClientRect.top = rect.top + MEMOFORM_CAPTION_HEIGHT;
		if (memoClientRect.PtInRect(point)) {
			SetCursor(LoadCursor(NULL, IDC_IBEAM));
		}
		else {
			SetCursor(LoadCursor(NULL, IDC_ARROW));
		}
		return TRUE;
	}
	else if (nHitTest == HTCAPTION) {
		SetCursor(LoadCursor(NULL, IDC_HAND));
		return TRUE;
	}
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void MemoForm::SetIsFocused(bool isFocused) {
	this->isFocused = isFocused;
}
void MemoForm::SetIsHovered(bool isHovered) {
	this->isHovered = isHovered;
}

void MemoForm::GetCaretPos(Long *xPosition, Long *yPosition) {
	*xPosition = this->GetMarginWidth();
	*yPosition = this->GetMarginHeight() + this->GetCaptionHeight();

	//2. Get infomation
	Memo *memo = static_cast<Memo*>(this->GetContents());
	Long row = memo->GetRow();
	Line *line = memo->GetLine(row);
	Long column = line->GetColumn();

	//3. Get yPosition
	Long i = 0;
	while (i < row) {
		*yPosition += this->GetCaret()->GetHeight();
		i++;
	}

	//4. Get xPosition
	i = 0;
	while (i < column) {
		*xPosition += line->GetCharacter(i)->GetWidth();
		i++;
	}
}

void MemoForm::ChangeColorToPurple() {
	this->colorType = MEMOFORM_COLOR_PURPLE;
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CWnd::FindWindow("OtherNote", NULL));
	otherNoteForm->SetDefaultMemoColor(this->colorType);
	this->RedrawWindow();
}

void MemoForm::ChangeColorToYellow() {
	this->colorType = MEMOFORM_COLOR_YELLOW;
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CWnd::FindWindow("OtherNote", NULL));
	otherNoteForm->SetDefaultMemoColor(this->colorType);
	this->RedrawWindow();
}

void MemoForm::ChangeColorToGreen() {
	this->colorType = MEMOFORM_COLOR_GREEN;
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CWnd::FindWindow("OtherNote", NULL));
	otherNoteForm->SetDefaultMemoColor(this->colorType);
	this->RedrawWindow();
}

void MemoForm::ChangeColorToBlue() {
	this->colorType = MEMOFORM_COLOR_BLUE;
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CWnd::FindWindow("OtherNote", NULL));
	otherNoteForm->SetDefaultMemoColor(this->colorType);
	this->RedrawWindow();
}

void MemoForm::ChangeColorToPink() {
	this->colorType = MEMOFORM_COLOR_PINK;
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CWnd::FindWindow("OtherNote", NULL));
	otherNoteForm->SetDefaultMemoColor(this->colorType);
	this->RedrawWindow();
}

void MemoForm::ChangeColorToGray() {
	this->colorType = MEMOFORM_COLOR_GRAY;
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CWnd::FindWindow("OtherNote", NULL));
	otherNoteForm->SetDefaultMemoColor(this->colorType);
	this->RedrawWindow();
}

void MemoForm::SetFocusType(Long type) {
	this->focusType = type;
}

void MemoForm::SetColorType(Long colorType) {
	this->colorType = colorType;
}