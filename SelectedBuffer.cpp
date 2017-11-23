//SelectedBuffer.cpp

#include "SelectedBuffer.h"
#include "MemoForm.h"
#include "Memo.h"
#include "Line.h"
#include "Character.h"

SelectedBuffer::SelectedBuffer(MemoForm *memoForm, Long currentRow, Long currentColumn) {
	this->memoForm = memoForm;
	this->buffer = 0;
	this->initialRow = currentRow;
	this->initialColumn = currentColumn;
	this->beginRow = currentRow;
	this->beginColumn = currentColumn;
	this->endRow = currentRow;
	this->endColumn = currentColumn;
	
	this->isSelecting = false;
//	this->isCopy = false;
}

SelectedBuffer::SelectedBuffer(const SelectedBuffer& source) {
	this->memoForm = source.memoForm;
	this->buffer = new Memo(*source.buffer);
	this->initialRow = source.initialRow;
	this->initialColumn = source.initialColumn;
	this->beginRow = source.beginRow;
	this->beginColumn = source.beginColumn;
	this->endRow = source.endRow;
	this->endColumn = source.endColumn;

	this->isSelecting = source.isSelecting;
//	this->isCopy = source.isCopy;
}

SelectedBuffer::~SelectedBuffer() {
	if (this->buffer != 0) {
		delete this->buffer;
	}
}

SelectedBuffer& SelectedBuffer::operator=(const SelectedBuffer& source) {
	this->memoForm = source.memoForm;
	if (this->buffer != 0) {
		delete this->buffer;
	}
	this->buffer = new Memo(*source.buffer);
	this->initialRow = source.initialRow;
	this->initialColumn = source.initialColumn;
	this->beginRow = source.beginRow;
	this->beginColumn = source.beginColumn;
	this->endRow = source.endRow;
	this->endColumn = source.endColumn;

	this->isSelecting = source.isSelecting;
//	this->isCopy = source.isCopy;

	return *this;
}

void SelectedBuffer::SetPosition(Long currentRow, Long currentColumn) {
	if (this->initialRow < currentRow) {
		this->beginRow = this->initialRow;
		this->endRow = currentRow;

		this->beginColumn = this->initialColumn;
		this->endColumn = currentColumn;
	}
	else if (this->initialRow == currentRow) {
		this->beginRow = this->initialRow;
		this->endRow = currentRow;
		if (this->initialColumn < currentColumn) {
			this->beginColumn = this->initialColumn;
			this->endColumn = currentColumn;
		}
		else {
			this->beginColumn = currentColumn;
			this->endColumn = this->initialColumn;
		}
	}
	else if (this->initialRow > currentRow) {
		this->beginRow = currentRow;
		this->endRow = this->initialRow;
		
		this->beginColumn = currentColumn;
		this->endColumn = this->initialColumn;
	}
}

#include "SingleCharacter.h"
#include "DoubleCharacter.h"

//void SelectedBuffer::Copy(Long currentRow, Long currentColumn) {
//	this->SetPosition(currentRow, currentColumn);
//	
//	if (this->buffer != 0) {
//		delete this->buffer;
//		this->buffer = 0;
//	}
//	this->buffer = new Memo;
//
//	Long i = this->beginRow;
//	Long j = this->beginColumn;
//		
//	Memo *memo = this->otherNoteForm->GetMemo();
//	Line *line = memo->GetLine(i);
//
//	Line *bufferLine = this->buffer->GetLine(this->buffer->GetRow());
//	if (i == this->endRow) {
//		while (j < this->endColumn) {
//			bufferLine->Add(line->GetCharacter(j)->Clone());
//			bufferLine->MoveNextColumn();
//			j++;
//		}
//	}
//	else {
//		while (j < line->GetLength()) {
//			bufferLine->Add(line->GetCharacter(j)->Clone());
//			bufferLine->MoveNextColumn();
//			j++;
//		}
//	}
///*
//	k++;
//	i++;
//	while (i < this->endRow) {
//		//bufferLine = this->buffer->GetLine(k);
//		this->buffer->Add(this->buffer->GetLine(k)->Clone());
//		k++;
//		i++;
//	}
//*/
//	//if (this->beginRow != this->endRow) {
//	//	j = 0;
//	//	//while(j<)
//	//}
//	
//
//	this->otherNoteForm->RedrawWindow();
//	//if (i == this->currentRow) {
//	//	while (j < this->currentColumn) {
//	//		Character *character = line->GetCharacter(j);
//	//		if (dynamic_cast<SingleCharacter*>(character)) {
//	//			buffer += dynamic_cast<SingleCharacter*>(character)->GetValue();
//	//		}
//	//		else if (dynamic_cast<DoubleCharacter*>(character)) {
//	//			buffer += dynamic_cast<DoubleCharacter*>(character)->GetValue()[0];
//	//			buffer += dynamic_cast<DoubleCharacter*>(character)->GetValue()[1];
//	//		}
//	//	}
//	//}
//	//else if (i < this->currentRow) {
//
//	//}
//
//}

void SelectedBuffer::CopyToBuffer(Long currentRow, Long currentColumn) {
	this->SetPosition(currentRow, currentColumn);

	if (this->buffer != 0) {
		delete this->buffer;
		this->buffer = 0;
	}

	this->buffer = new Memo;
	this->buffer->AddLine();
	Line *bufferLine = this->buffer->GetLine(this->buffer->GetRow());
	
	Memo *memo = static_cast<Memo*>(this->memoForm->GetContents());
	Long i = this->beginRow;
	Line *line = memo->GetLine(i);
	Long j = this->beginColumn;

	if (this->beginRow == this->endRow) {
		while (j < this->endColumn) {
			bufferLine->Add(line->GetCharacter(j)->Clone());
			j++;
		}
	}
	else {
		while (j < line->GetLength()) {
			bufferLine->Add(line->GetCharacter(j)->Clone());
			j++;
		}
	}

	i++;
	while (i < this->endRow) {
		line = memo->GetLine(i);
		this->buffer->Add(line->Clone());
		i++;
	}

	if (this->beginRow != this->endRow && i == this->endRow) {
		line = memo->GetLine(i);
		this->buffer->AddLine();
		bufferLine = this->buffer->GetLine(this->buffer->GetRow());
		j = 0;
		while (j < this->endColumn) {
			bufferLine->Add(line->GetCharacter(j)->Clone());
			j++;
		}
	}
	//this->memoForm->RedrawWindow();
}
/*
void SelectedBuffer::Paste() {
	if (this->isCopy) {
		Memo *memo = this->otherNoteForm->GetMemo();
		
		Memo *bufferMemo = this->buffer;
		bufferMemo->MoveFirstRow();
		while (bufferMemo->GetRow() < bufferMemo->GetLength()) {
			Line *line = memo->GetLine(memo->GetRow());

			Line *bufferLine = bufferMemo->GetLine(bufferMemo->GetRow());
			bufferLine->MoveFirstColumn();
			while (bufferLine->GetColumn() < bufferLine->GetLength()) {
				line->Insert(line->GetColumn(), bufferLine->GetCharacter(bufferLine->GetColumn())->Clone());

				line->MoveNextColumn();
				bufferLine->MoveNextColumn();
			}
			memo->MoveNextRow();
			bufferMemo->MoveNextRow();
		}
	}
}
*/
//
//bool SelectedBuffer::SetIsCopy(bool isCopy) {
//	this->isCopy = isCopy;
//	return this->isCopy;
//}

bool SelectedBuffer::SetIsSelecting(bool isSelecting) {
	this->isSelecting = isSelecting;
	return this->isSelecting;
}

#include "MakeStringVisitor.h"
void SelectedBuffer::CopyToClipboard() {
	MakeStringVisitor makeStringVisitor;
	this->buffer->Accept(&makeStringVisitor);

	CString clipboardStr(makeStringVisitor.GetCompleteString().c_str());

	if (!this->memoForm->OpenClipboard()) {
		AfxMessageBox(_T("Cannot open the Clipboard"));
		return;
	}
	if (!EmptyClipboard())
	{
		AfxMessageBox(_T("Cannot empty the Clipboard"));
		return;
	}

	size_t cbStr = (clipboardStr.GetLength() + 1) * sizeof(TCHAR);
	HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, cbStr);
	memcpy_s(GlobalLock(hData), cbStr, clipboardStr.LockBuffer(), cbStr);
	GlobalUnlock(hData);
	clipboardStr.UnlockBuffer();
	// For the appropriate data formats...
	UINT uiFormat = (sizeof(TCHAR) == sizeof(WCHAR)) ? CF_UNICODETEXT : CF_TEXT;
	if (::SetClipboardData(uiFormat, hData) == NULL)
	{
		AfxMessageBox(_T("Unable to set Clipboard data"));
		CloseClipboard();
		return;
	}

	CloseClipboard();
}

CString SelectedBuffer::GetClipboardString() {
	if (!::IsClipboardFormatAvailable(CF_TEXT))	return CString("");
	if (!this->memoForm->OpenClipboard())	return CString("");

	CString clipboardStr;
	HGLOBAL hData = GetClipboardData(CF_TEXT);
	if (hData != NULL) {
		TCHAR* pszBuffer = (TCHAR*)::GlobalLock(hData);
		if (pszBuffer != NULL) {
			clipboardStr.Format(_T("%s"), pszBuffer);
			::GlobalUnlock(hData);
		}
	}

	CloseClipboard();

	return clipboardStr;
}

#include "SingleCharacter.h"
#include "DoubleCharacter.h"
#include <string>
using namespace std;
void SelectedBuffer::PasteToBuffer() {
	CString clipboardStr(this->GetClipboardString());
	//string clipboardString(clipboardStr);
	//string clipboardStr(this->GetClipboardString());
	
	if (this->buffer != 0) {
		delete this->buffer;
		this->buffer = 0;
	}
	this->buffer = new Memo;
	//this->buffer->RemoveLine();

	string lineStr;
	Long i = 0;
	while (i<clipboardStr.GetLength()) {
		lineStr = "";
		while (i<clipboardStr.GetLength() && clipboardStr.GetAt(i) != '\r') {
			lineStr += clipboardStr.GetAt(i);
			i++;
		}
		this->buffer->Add(new Line(256, lineStr));
		this->buffer->MoveNextRow();
		i += 2;
	}
}

#include "Caret.h"
#include "PageForm.h"
#include "CharacterFaces.h"
#include "HorizontalScroll.h"
#include "VerticalScroll.h"
void SelectedBuffer::PasteToMemoForm() {
	this->PasteToBuffer();
	
	if (this->CanPaste() == TRUE) {
		//Caret *caret = Caret::Instance(this->otherNoteForm);
		Caret *caret = this->memoForm->GetCaret();

		//1. 현재 메모와 라인을 구한다.
		Memo *memo = static_cast<Memo*>(this->memoForm->GetContents());
		Line *line = memo->GetLine(memo->GetRow());

		//2. 현재 라인의 캐럿 이후의 문자들을 복사한다.
		Line *remainLine = new Line;
		Long i = line->GetColumn();
		while (i < line->GetLength()) {
			remainLine->Add(line->GetCharacter(i)->Clone());
			line->MoveNextColumn();
			line->Erase();
			//i++;
		}

		//3. 현재 라인의 캐럿까지의 문자들의 width를 구한다.
		Long currentWidth = 0;
		Long z = 0;
		while (z < line->GetColumn()) {
			currentWidth += line->GetCharacter(z)->GetWidth();
			z++;
		}

		//4. 현재 라인까지의 height를 구한다.
		CharacterFaces *characterFaces = CharacterFaces::Instance(0);
		Long currentHeight = characterFaces->GetCharacterSize(97).GetHeight();
		z = 0;
		while (z < memo->GetRow()) {
			currentHeight += characterFaces->GetCharacterSize(97).GetHeight();
			z++;
		}

		//5. 페이지와 메모 윈도우 영역을 구한다.
		OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CWnd::FindWindow("OtherNote", NULL));
		CRect memoFormWndRect;
		this->memoForm->GetWindowRect(&memoFormWndRect);
		CRect pageFormWndRect;
		static_cast<PageForm*>(this->memoForm->GetParent())->GetWindowRect(&pageFormWndRect);

		//5.1.
		Long defaultHeight = characterFaces->GetCharacterSize(97).GetHeight();

		//6. 복사한 영역 한글자씩 붙여넣기
		Memo *bufferMemo = this->buffer;
		bufferMemo->MoveFirstRow();
		Line *bufferLine;
		while (bufferMemo->GetRow() < bufferMemo->GetLength()) {
			line = memo->GetLine(memo->GetRow());
			bufferLine = bufferMemo->GetLine(bufferMemo->GetRow());
			bufferLine->MoveFirstColumn();
			while (bufferLine->GetColumn() < bufferLine->GetLength()) {
				line->Add(bufferLine->GetCharacter(bufferLine->GetColumn())->Clone());
				if (memoFormWndRect.left + MEMOFORM_MARGIN_LEFT + currentWidth + bufferLine->GetCharacter(bufferLine->GetColumn())->GetWidth() + MEMOFORM_MARGIN_RIGHT > pageFormWndRect.left + PAGEFORM_MAX_WIDTH) {
					line->Remove(line->GetLength() - 1);

					CharacterFaces *characterFaces = CharacterFaces::Instance(0);
					Long characterHeight = characterFaces->GetCharacterSize(97).GetHeight();
					if (memoFormWndRect.top + MEMOFORM_CAPTION_HEIGHT + MEMOFORM_MARGIN_TOP + currentHeight + characterHeight + MEMOFORM_MARGIN_BOTTOM <= pageFormWndRect.top + PAGEFORM_MAX_HEIGHT) {
						Long index = memo->InsertLine();
						line = memo->GetLine(index);
						line->Add(bufferLine->GetCharacter(bufferLine->GetColumn())->Clone());
						currentWidth = bufferLine->GetCharacter(bufferLine->GetColumn())->GetWidth();
						//currentHeight += bufferLine->GetCharacter(bufferLine->GetColumn())->GetHeight();
						currentHeight += defaultHeight;
					}
				}
				currentWidth += bufferLine->GetCharacter(bufferLine->GetColumn())->GetWidth();
				line->MoveNextColumn();
				bufferLine->MoveNextColumn();
			}
			if (bufferMemo->GetRow() < bufferMemo->GetLength() - 1) {	//개행조건 추가
				Long index = memo->InsertLine();
				line = memo->GetLine(index);
				//currentHeight += bufferMemo->GetLine(bufferMemo->GetRow())->GetCharacter(0)->GetHeight();
				currentWidth = 0;
				currentHeight += defaultHeight;
			}
			bufferMemo->MoveNextRow();
		}

		//7. 남은 글자들 붙여넣기
		remainLine->MoveFirstColumn();
		i = remainLine->GetColumn();
		while (i < remainLine->GetLength()) {
			line->Add(remainLine->GetCharacter(i)->Clone());
			if (memoFormWndRect.left + MEMOFORM_MARGIN_LEFT + currentWidth + remainLine->GetCharacter(i)->GetWidth() + MEMOFORM_MARGIN_RIGHT > pageFormWndRect.left + PAGEFORM_MAX_WIDTH) {
				line->Remove(line->GetLength() - 1);

				CharacterFaces *characterFaces = CharacterFaces::Instance(0);
				Long characterHeight = characterFaces->GetCharacterSize(97).GetHeight();
				if (memoFormWndRect.top + MEMOFORM_CAPTION_HEIGHT + MEMOFORM_MARGIN_TOP + currentHeight + characterHeight + MEMOFORM_MARGIN_BOTTOM <= pageFormWndRect.top + PAGEFORM_MAX_HEIGHT) {
					Long index = memo->InsertLine();
					line = memo->GetLine(index);
					line->Add(remainLine->GetCharacter(i)->Clone());

					currentWidth = remainLine->GetCharacter(i)->GetWidth();
					//currentHeight += remainLine->GetCharacter(i)->GetHeight();
					currentHeight += defaultHeight;
				}
			}
			i++;
		}
		//8. 메모폼 캐럿 업데이트
		this->memoForm->GetCaret()->UpdateCaret();
	}
}

BOOL SelectedBuffer::CanPaste() {
	//Caret *caret = Caret::Instance(this->otherNoteForm);
	Caret *caret = this->memoForm->GetCaret();

	//0.현재 메모의 row, column -나중에 복원용
	Long originRow = static_cast<Memo*>(this->memoForm->GetContents())->GetRow();
	Line *tempLine = static_cast<Memo*>(this->memoForm->GetContents())->GetLine(originRow);
	Long originColumn = tempLine->GetColumn();

	//1. 현재 메모와 라인을 구한다.
	Memo *origin = static_cast<Memo*>(this->memoForm->GetContents());
	//Memo *memo = static_cast<Memo*>(this->memoForm->GetContents());
	Memo *memo = static_cast<Memo*>(origin->Clone());
	Line *line = memo->GetLine(memo->GetRow());

	//2. 현재 라인의 캐럿 이후의 문자들을 복사한다.
	Line *remainLine = new Line;
	Long i = line->GetColumn();
	while (i < line->GetLength()) {
		remainLine->Add(line->GetCharacter(i)->Clone());
		line->MoveNextColumn();
		line->Erase();
		//i++;
	}

	//3. 현재 라인의 캐럿까지의 문자들의 width를 구한다.
	Long currentWidth = 0;
	Long z = 0;
	while (z < line->GetColumn()) {
		currentWidth += line->GetCharacter(z)->GetWidth();
		z++;
	}
	//4. 현재 라인까지의 height를 구한다.
	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	Long currentHeight = characterFaces->GetCharacterSize(97).GetHeight();
	z = 0;
	while (z < memo->GetRow()) {
		currentHeight += characterFaces->GetCharacterSize(97).GetHeight();
		z++;
	}

	//5. 페이지와 메모 윈도우 영역을 구한다.
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CWnd::FindWindow("OtherNote", NULL));
	CRect memoFormWndRect;
	this->memoForm->GetWindowRect(&memoFormWndRect);
	CRect pageFormWndRect;
	static_cast<PageForm*>(this->memoForm->GetParent())->GetWindowRect(&pageFormWndRect);

	//5.1. 기본 높이 구하기
	Long defaultHeight = characterFaces->GetCharacterSize(97).GetHeight();
	
	//6. 복사한 영역 한글자씩 붙여넣기
	Memo *bufferMemo = this->buffer;
	bufferMemo->MoveFirstRow();
	Line *bufferLine;
	while (bufferMemo->GetRow() < bufferMemo->GetLength()) {
		line = memo->GetLine(memo->GetRow());
		bufferLine = bufferMemo->GetLine(bufferMemo->GetRow());
		bufferLine->MoveFirstColumn();
		while (bufferLine->GetColumn() < bufferLine->GetLength()) {
			line->Add(bufferLine->GetCharacter(bufferLine->GetColumn())->Clone());
			if (memoFormWndRect.left + MEMOFORM_MARGIN_LEFT + currentWidth + bufferLine->GetCharacter(bufferLine->GetColumn())->GetWidth() + MEMOFORM_MARGIN_RIGHT > pageFormWndRect.left + PAGEFORM_MAX_WIDTH) {
				line->Remove(line->GetLength() - 1);

				CharacterFaces *characterFaces = CharacterFaces::Instance(0);
				Long characterHeight = characterFaces->GetCharacterSize(97).GetHeight();
				//if (memoFormWndRect.top + MEMOFORM_CAPTION_HEIGHT + MEMOFORM_MARGIN_TOP + currentHeight + characterHeight + MEMOFORM_MARGIN_BOTTOM <= pageFormWndRect.top + PAGEFORM_MAX_HEIGHT) {
					Long index = memo->InsertLine();
					line = memo->GetLine(index);
					line->Add(bufferLine->GetCharacter(bufferLine->GetColumn())->Clone());
					currentWidth = bufferLine->GetCharacter(bufferLine->GetColumn())->GetWidth();
					//currentHeight += bufferLine->GetCharacter(bufferLine->GetColumn())->GetHeight();
					currentHeight += defaultHeight;
				//}
			}
			currentWidth += bufferLine->GetCharacter(bufferLine->GetColumn())->GetWidth();
			line->MoveNextColumn();
			bufferLine->MoveNextColumn();
		}
		if (bufferMemo->GetRow() < bufferMemo->GetLength() - 1) {	//개행조건 추가
			Long index = memo->InsertLine();
			line = memo->GetLine(index);

			//currentHeight += bufferMemo->GetLine(bufferMemo->GetRow())->GetCharacter(0)->GetHeight();//11/12버그 코드
			//Long defaultHeight = characterFaces->GetCharacterSize(97).GetHeight();
			currentWidth = 0;
			currentHeight += defaultHeight;
		}
		bufferMemo->MoveNextRow();
	}

	//7. 남은 글자들 붙여넣기
	remainLine->MoveFirstColumn();
	i = remainLine->GetColumn();
	while (i < remainLine->GetLength()) {
		line->Add(remainLine->GetCharacter(i)->Clone());
		if (memoFormWndRect.left + MEMOFORM_MARGIN_LEFT + currentWidth + remainLine->GetCharacter(i)->GetWidth() + MEMOFORM_MARGIN_RIGHT > pageFormWndRect.left + PAGEFORM_MAX_WIDTH) {
			line->Remove(line->GetLength() - 1);

			CharacterFaces *characterFaces = CharacterFaces::Instance(0);
			Long characterHeight = characterFaces->GetCharacterSize(97).GetHeight();
			//if (memoFormWndRect.top + MEMOFORM_CAPTION_HEIGHT + MEMOFORM_MARGIN_TOP + currentHeight + characterHeight + MEMOFORM_MARGIN_BOTTOM <= pageFormWndRect.top + PAGEFORM_MAX_HEIGHT) {
				Long index = memo->InsertLine();
				line = memo->GetLine(index);
				line->Add(remainLine->GetCharacter(i)->Clone());

				currentWidth = remainLine->GetCharacter(i)->GetWidth();
				//currentHeight += remainLine->GetCharacter(i)->GetHeight();
				currentHeight += defaultHeight;
			//}
		}
		i++;
	}

	//원상복구
	if (memo != 0) {
		delete memo;
	}
	static_cast<Memo*>(this->memoForm->GetContents())->SetRow(originRow);
	static_cast<Memo*>(this->memoForm->GetContents())->GetLine(originRow)->SetColumn(originColumn);

	//8. 메모폼 캐럿 업데이트
	//this->memoForm->GetCaret()->UpdateCaret();
	BOOL ret = TRUE;
	Long memoWidth = memoFormWndRect.top + MEMOFORM_CAPTION_HEIGHT + MEMOFORM_MARGIN_TOP + currentHeight + MEMOFORM_MARGIN_BOTTOM;
	Long pageWidth = pageFormWndRect.top + PAGEFORM_MAX_HEIGHT;
	if (memoFormWndRect.top + MEMOFORM_CAPTION_HEIGHT + MEMOFORM_MARGIN_TOP + currentHeight + MEMOFORM_MARGIN_BOTTOM > pageFormWndRect.top + PAGEFORM_MAX_HEIGHT) {
		ret = FALSE;
	}

	return ret;
}


////handler for Edit | Copy menu
//void OtherNoteForm::OnCopy()
//{
//	if (!this->OpenClipboard())
//	{
//		AfxMessageBox(_T("Cannot open the Clipboard"));
//		return;
//	}
//	// Remove the current Clipboard contents  
//	if (!EmptyClipboard())
//	{
//		AfxMessageBox(_T("Cannot empty the Clipboard"));
//		return;
//	}
//
//	// Get the currently selected data, hData handle to 
//	// global memory of data
//	CString str;
//	m_Edit.GetWindowText(str);
//	size_t cbStr = (str.GetLength() + 1) * sizeof(TCHAR);
//	HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, cbStr);
//	memcpy_s(GlobalLock(hData), cbStr, str.LockBuffer(), cbStr);
//	GlobalUnlock(hData);
//	str.UnlockBuffer();
//
//	// For the appropriate data formats...
//	UINT uiFormat = (sizeof(TCHAR) == sizeof(WCHAR)) ? CF_UNICODETEXT : CF_TEXT;
//	if (::SetClipboardData(uiFormat, hData) == NULL)
//	{
//		AfxMessageBox(_T("Unable to set Clipboard data"));
//		CloseClipboard();
//		return;
//	}
//
//	CloseClipboard();
//}

void SelectedBuffer::SetInitialPosition(Long currentRow, Long currentColumn) {
	this->initialRow = currentRow;
	this->initialColumn = currentColumn;
}
