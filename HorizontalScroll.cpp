// HorizontalScroll.cpp

#include "HorizontalScroll.h"
#include "Caret.h"
#include "CharacterFaces.h"
#include "PageForm.h"
#include "Note.h"

HorizontalScroll::HorizontalScroll(OtherNoteForm *otherNoteForm)
	:Scroll(otherNoteForm) {
	CRect rect;
	this->otherNoteForm->GetClientRect(&rect);
	this->scrollBar->Create(SBS_HORZ, CRect(rect.left, rect.bottom-20, rect.right-20, rect.bottom), this->otherNoteForm, 1);
	/*Caret *caret = Caret::Instance(0);
	CharacterFaces *characterFaces = CharacterFaces::Instance(0);*/
	//Long tabWidth = characterFaces->GetCharacterSize(97).GetWidth();
	SCROLLINFO scrinfo;
	scrinfo.cbSize = sizeof(scrinfo); 
	scrinfo.fMask = SIF_ALL; 
	scrinfo.nMin = 0;
	scrinfo.nMax = rect.right - 20;//this->maxLineSize;//(rect.right / (characterFaces->GetCharacterSize(97).GetWidth())) - 1;	
	scrinfo.nPage = 150;//this ->maxLineSize / rect.right; //5;
	scrinfo.nPos = 0;
	this->scrollBar->SetScrollInfo(&scrinfo); 
	this->scrollBar->ShowScrollBar(SB_BOTH);
	//this->scrollBar->EnableScrollBar(ESB_DISABLE_BOTH);
}

HorizontalScroll::HorizontalScroll(const HorizontalScroll& source)
	:Scroll(source) {
}

HorizontalScroll::~HorizontalScroll() {
}

HorizontalScroll& HorizontalScroll::operator=(const HorizontalScroll& source) {
	return *this;
}

//#include "OtherNoteForm.h"
//#include "Line.h"
//#include "Memo.h"
//#include "Character.h"
//void HorizontalScroll::UpdateLine() {
//	//Memo *memo = this->otherNoteForm->GetMemo();
//	Line *line;// = memo->GetLine(memo->GetRow());
//	Long lineWidth;// = 0;
//	Long i = 0;
//	Long j;
//	Long newMaxLineSize = 0;
//	while (i < memo->GetLength()) {
//		line = memo->GetLine(i);
//		j = 0;
//		lineWidth = 0;
//		while (j < line->GetLength()) {
//			lineWidth += line->GetCharacter(j)->GetWidth();
//			j++;
//		}
//		if (newMaxLineSize < lineWidth) {
//			newMaxLineSize = lineWidth;
//		}
//		i++;
//	}
//	if(newMaxLineSize > this->maxLineSize) {
//		this->maxLineSize = newMaxLineSize;
//	}
//	CRect rect;
//	this->otherNoteForm->GetClientRect(&rect);
//	if (this->GetMaxLineSize() > rect.right - 20) {
//		SCROLLINFO scrinfo;
//		this->scrollBar->GetScrollInfo(&scrinfo);
//		Long temp = scrinfo.nPos;
//		scrinfo.nMax = this->maxLineSize;
//		//scrinfo.nPos = temp;
//		//scrinfo.nPage = 0;//rect.right - 20;
//		//scrinfo.nPos = scrinfo.nMax - scrinfo.nPage;
//		this->scrollBar->SetScrollInfo(&scrinfo);
//	}
//	if (this->otherNoteForm->GetMemo()->GetLength() == 1 &&
//		this->otherNoteForm->GetMemo()->GetLine(0)->GetLength() == 0){
//		this->SetScrollUnVisible();
//	}
//}
//
void HorizontalScroll::ScrollNextLine() {
	SCROLLINFO  scrinfo;
	//scrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
	this->scrollBar->GetScrollInfo(&scrinfo);

	if((scrinfo.nPos + scrinfo.nPage) < scrinfo.nMax) {
		//CharacterFaces *characterFaces = CharacterFaces::Instance(0);
		Long width = 150;
		scrinfo.nPos += width;
		if (scrinfo.nPos + scrinfo.nPage > scrinfo.nMax) {
			scrinfo.nPos -= width;
			width -= scrinfo.nPos + scrinfo.nPage - scrinfo.nMax + width;
			scrinfo.nPos += width;
		}
		//자료구조에 저장
		this->otherNoteForm->GetPageForm(this->current)->SetHScrinfo(scrinfo);
		//윈도우 이동
		SCROLLINFO hScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
		SCROLLINFO vScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetVScrinfo();
		this->scrollBar->SetScrollInfo(&hScrinfo);
		this->otherNoteForm->GetPageForm(this->current)->SetWindowPos(0, -hScrinfo.nPos, -vScrinfo.nPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		//this->scrollBar->SetScrollInfo(&scrinfo);
		/*CRect rect;
		this->otherNoteForm->GetClientRect(&rect);
		this->otherNoteForm->ScrollWindow(-width, 0, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
		this->otherNoteForm->UpdateWindow();*/
	}
}

void HorizontalScroll::ScrollPreviousLine() {
	SCROLLINFO  scrinfo;
	//scrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
	this->scrollBar->GetScrollInfo(&scrinfo);

	if (scrinfo.nPos > 0) {
		//CharacterFaces *characterFaces = CharacterFaces::Instance(0);
		Long width = 150;
		scrinfo.nPos -= width;
		if (scrinfo.nPos < 0) {
			scrinfo.nPos += width;
			width = scrinfo.nPos;
			scrinfo.nPos = 0;
		}
		//자료구조에 저장
		this->otherNoteForm->GetPageForm(this->current)->SetHScrinfo(scrinfo);
		//윈도우 이동
		SCROLLINFO hScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
		SCROLLINFO vScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetVScrinfo();
		this->scrollBar->SetScrollInfo(&hScrinfo);
		this->otherNoteForm->GetPageForm(this->current)->SetWindowPos(0, -hScrinfo.nPos, -vScrinfo.nPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		//this->scrollBar->SetScrollInfo(&scrinfo);
		/*CRect rect;
		this->otherNoteForm->GetClientRect(&rect);
		this->otherNoteForm->ScrollWindow(+width, 0, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
		this->otherNoteForm->UpdateWindow();*/
	}
}

void HorizontalScroll::ScrollNextPage() {
	SCROLLINFO  scrinfo;
	//scrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
	this->scrollBar->GetScrollInfo(&scrinfo);
	Long width = scrinfo.nPage;
	if ((scrinfo.nPos + scrinfo.nPage) < scrinfo.nMax) {
		//CharacterFaces *characterFaces = CharacterFaces::Instance(0);
		scrinfo.nPos += scrinfo.nPage;
		if (scrinfo.nPos + scrinfo.nPage > scrinfo.nMax) {
			scrinfo.nPos -= scrinfo.nPage;
			width = scrinfo.nPage;
			width -= scrinfo.nPos + scrinfo.nPage - scrinfo.nMax + width;
			scrinfo.nPos += width;
		}
		//자료구조에 저장
		this->otherNoteForm->GetPageForm(this->current)->SetHScrinfo(scrinfo);
		//윈도우 이동
		SCROLLINFO hScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
		SCROLLINFO vScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetVScrinfo();
		this->scrollBar->SetScrollInfo(&hScrinfo);
		this->otherNoteForm->GetPageForm(this->current)->SetWindowPos(0, -hScrinfo.nPos, -vScrinfo.nPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		//this->scrollBar->SetScrollInfo(&scrinfo);
	/*	CRect rect;
		this->otherNoteForm->GetClientRect(&rect);
		this->otherNoteForm->ScrollWindow(-width, 0, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
		this->otherNoteForm->UpdateWindow();*/
	}
}

void HorizontalScroll::ScrollPreviousPage() {
	SCROLLINFO  scrinfo;
	//scrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
	this->scrollBar->GetScrollInfo(&scrinfo);
	Long width = scrinfo.nPage;
	if (scrinfo.nPos > 0) {
		//CharacterFaces *characterFaces = CharacterFaces::Instance(0);
		scrinfo.nPos -= width;
		if (scrinfo.nPos < 0) {
			scrinfo.nPos += width;
			width = scrinfo.nPos;
			scrinfo.nPos = 0;
		}
		//자료구조에 저장
		this->otherNoteForm->GetPageForm(this->current)->SetHScrinfo(scrinfo);
		//윈도우 이동
		SCROLLINFO hScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
		SCROLLINFO vScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetVScrinfo();
		this->scrollBar->SetScrollInfo(&hScrinfo);
		this->otherNoteForm->GetPageForm(this->current)->SetWindowPos(0, -hScrinfo.nPos, -vScrinfo.nPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		//this->scrollBar->SetScrollInfo(&scrinfo);
	/*	CRect rect;
		this->otherNoteForm->GetClientRect(&rect);
		this->otherNoteForm->ScrollWindow(+width, 0, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
		this->otherNoteForm->UpdateWindow();*/
	}
}

void HorizontalScroll::MoveThumb() {
	//스크롤 로직
	SCROLLINFO  scrinfo;
	//scrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
	this->scrollBar->GetScrollInfo(&scrinfo);
	Long width = scrinfo.nTrackPos - scrinfo.nPos;
	scrinfo.nPos = scrinfo.nTrackPos;
	//this->scrollBar->SetScrollInfo(&scrinfo);
	//자료구조에 저장
	this->otherNoteForm->GetPageForm(this->current)->SetHScrinfo(scrinfo);
	//윈도우 이동
	SCROLLINFO hScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
	SCROLLINFO vScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetVScrinfo();
	this->scrollBar->SetScrollInfo(&hScrinfo);
	this->otherNoteForm->GetPageForm(this->current)->SetWindowPos(0, -hScrinfo.nPos, -vScrinfo.nPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	//this->otherNoteForm->GetPageForm(this->current)->SetWindowPos(0, -scrinfo.nPos, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	/*CRect rect;
	this->otherNoteForm->GetClientRect(&rect);
	this->otherNoteForm->ScrollWindow(-width, 0, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
	this->otherNoteForm->UpdateWindow();*/
}

void HorizontalScroll::ScrollNext(Long size) {
	SCROLLINFO  scrinfo;
	//scrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
	this->scrollBar->GetScrollInfo(&scrinfo);

	if ((scrinfo.nPos + scrinfo.nPage) < scrinfo.nMax) {
		scrinfo.nPos += size;
		if (scrinfo.nPos + scrinfo.nPage > scrinfo.nMax) {
			scrinfo.nPos -= size;
			size -= scrinfo.nPos + scrinfo.nPage - scrinfo.nMax + size;
			scrinfo.nPos += size;
		}
		//this->scrollBar->SetScrollInfo(&scrinfo);
		//자료구조에 저장
		this->otherNoteForm->GetPageForm(this->current)->SetHScrinfo(scrinfo);
		//윈도우 이동
		SCROLLINFO hScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
		SCROLLINFO vScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetVScrinfo();
		this->scrollBar->SetScrollInfo(&hScrinfo);
		this->otherNoteForm->GetPageForm(this->current)->SetWindowPos(0, -hScrinfo.nPos, -vScrinfo.nPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	/*	CRect rect;
		this->otherNoteForm->GetClientRect(&rect);
		this->otherNoteForm->ScrollWindow(-size, 0, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
		this->otherNoteForm->UpdateWindow();*/
	}
}

void HorizontalScroll::ScrollPrevious(Long size) {
	SCROLLINFO  scrinfo;
	//scrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
	this->scrollBar->GetScrollInfo(&scrinfo);

	if (scrinfo.nPos > 0) {
		scrinfo.nPos -= size;
		if (scrinfo.nPos < 0) {
			scrinfo.nPos += size;
			size = scrinfo.nPos;
			scrinfo.nPos = 0;
		}
		//자료구조에 저장
		this->otherNoteForm->GetPageForm(this->current)->SetHScrinfo(scrinfo);
		//윈도우 이동
		SCROLLINFO hScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
		SCROLLINFO vScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetVScrinfo();
		this->scrollBar->SetScrollInfo(&hScrinfo);
		this->otherNoteForm->GetPageForm(this->current)->SetWindowPos(0, -hScrinfo.nPos, -vScrinfo.nPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		//this->scrollBar->SetScrollInfo(&scrinfo);
		/*CRect rect;
		this->otherNoteForm->GetClientRect(&rect);
		this->otherNoteForm->ScrollWindow(size, 0, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
		this->otherNoteForm->UpdateWindow();*/
	}
}

//void HorizontalScroll::ScrollNextCharacter() {
//	Line *line = this->otherNoteForm->GetMemo()->GetLine(this->otherNoteForm->GetMemo()->GetRow());
//	
//	Long currentLineWidth = 0;
//	Long i = 0;
//	while (i < line->GetColumn()) {
//		currentLineWidth += line->GetCharacter(i)->GetWidth();
//		i++;
//	}
//	SCROLLINFO scrinfo;
//	this->GetScrollBar()->GetScrollInfo(&scrinfo);
//		
//	//현재까지의 글자들의넓이들과 라인 최대 글자들의 넓이와 같은 경우
//	Long width = 0;
//	if (currentLineWidth >= this->GetMaxLineSize()) {
//		width = line->GetCharacter(line->GetColumn() - 1)->GetWidth();
//		//this->ScrollNext(width);
//
//	}
//	else if (currentLineWidth > scrinfo.nPos + scrinfo.nPage) {//현재까지ㅡ이 글자들의 넓이들이 큰 경우
//		CRect rect;
//		this->otherNoteForm->GetClientRect(&rect);
//		width = rect.right / 3.0;
//		if ((this->GetMaxLineSize() - currentLineWidth) < width) {
//			width = this->GetMaxLineSize() - currentLineWidth;
//		}
//		//this->ScrollNext(width);			
//	}
//	
//	if ((scrinfo.nPos + scrinfo.nPage) < scrinfo.nMax) {
//		scrinfo.nPos += width;
//		if (scrinfo.nPos + scrinfo.nPage > scrinfo.nMax) {
//			scrinfo.nPos -= width;
//			width -= scrinfo.nPos + scrinfo.nPage - scrinfo.nMax + width;
//			scrinfo.nPos += width;
//		}
//		this->scrollBar->SetScrollInfo(&scrinfo);
//		CRect rect;
//		this->otherNoteForm->GetClientRect(&rect);
//		this->otherNoteForm->ScrollWindow(-width, 0, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
//		this->otherNoteForm->UpdateWindow();
//	}
//}
//
//void HorizontalScroll::ScrollPreviousCharacter() {
//	Line *line = this->otherNoteForm->GetMemo()->GetLine(this->otherNoteForm->GetMemo()->GetRow());
//	
//	SCROLLINFO  scrinfo;
//	this->scrollBar->GetScrollInfo(&scrinfo);
//	
//	Long currentLineWidth = 0;
//	Long width = 0;
//	Long i = 0;
//	while (i < line->GetColumn()) {
//		currentLineWidth += line->GetCharacter(i)->GetWidth();
//		i++;
//	}
//	if (currentLineWidth < scrinfo.nPos) {
//		CRect rect;
//		this->otherNoteForm->GetClientRect(&rect);
//		width = (rect.right-20) / 3.0;
//		if (scrinfo.nPos < width) {
//			width = scrinfo.nPos;
//			//scrinfo.nPos = 0;
//		}
//		scrinfo.nPos -= width;
//		this->scrollBar->SetScrollInfo(&scrinfo);
//		/*CRect rect;
//		this->otherNoteForm->GetClientRect(&rect);*/
//		this->otherNoteForm->ScrollWindow(width, 0, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
//		this->otherNoteForm->UpdateWindow();
//	}
//	
//	/*if (scrinfo.nPos > 0) {
//		scrinfo.nPos -= width;
//		if (scrinfo.nPos < 0) {
//			scrinfo.nPos += width;
//			width = scrinfo.nPos;
//			scrinfo.nPos = 0;
//		}*/
//	/*this->scrollBar->SetScrollInfo(&scrinfo);
//	CRect rect;
//	this->otherNoteForm->GetClientRect(&rect);
//	this->otherNoteForm->ScrollWindow(width, 0, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
//	this->otherNoteForm->UpdateWindow();*/
////}
//}

void HorizontalScroll::ScrollFirst() {
	/*SCROLLINFO  scrinfo;
	this->scrollBar->GetScrollInfo(&scrinfo);
	Long width = scrinfo.nPos;
	scrinfo.nPos = 0;
	this->scrollBar->SetScrollInfo(&scrinfo);
	CRect rect;
	this->otherNoteForm->GetClientRect(&rect);
	this->otherNoteForm->ScrollWindow(width, 0, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
	this->otherNoteForm->UpdateWindow();*/
}

void HorizontalScroll::ScrollLast() {
	/*Line *line = this->otherNoteForm->GetMemo()->GetLine(this->otherNoteForm->GetMemo()->GetRow());

	SCROLLINFO  scrinfo;
	this->scrollBar->GetScrollInfo(&scrinfo);
	
	Long lineWidth = 0;
	Long width = 0;
	Long i = 0;
	while (i < line->GetLength()) {
		lineWidth += line->GetCharacter(i)->GetWidth();
		i++;
	}
	CRect rect;
	this->otherNoteForm->GetClientRect(&rect);
	if((this->maxLineSize - lineWidth) < (rect.right-20)*(1/3.0)) {
		Long nPos = scrinfo.nMax - scrinfo.nPage;
		width = nPos - scrinfo.nPos;
		scrinfo.nPos = nPos;
		this->scrollBar->SetScrollInfo(&scrinfo);
		this->otherNoteForm->ScrollWindow(-width, 0, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
		this->otherNoteForm->UpdateWindow();
	}
	else {
		Long nPos = lineWidth - ((rect.right-20)*(2/3.0));
		width = nPos - scrinfo.nPos;
		scrinfo.nPos = nPos;
		this->scrollBar->SetScrollInfo(&scrinfo);
		this->otherNoteForm->ScrollWindow(-width, 0, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
		this->otherNoteForm->UpdateWindow();
	}*/
}

void HorizontalScroll::SetCurrent(Long index) {
	this->current = index;
	SCROLLINFO hScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
	SCROLLINFO vScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetVScrinfo();
	this->scrollBar->SetScrollInfo(&hScrinfo);
	this->otherNoteForm->GetPageForm(index)->SetWindowPos(0, -hScrinfo.nPos, -vScrinfo.nPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void HorizontalScroll::UpdateScrinfo(SCROLLINFO scrinfo) {
	this->scrollBar->SetScrollInfo(&scrinfo);
}

void HorizontalScroll::ScrollToPosition(Long position) {
	SCROLLINFO  scrinfo;
	this->scrollBar->GetScrollInfo(&scrinfo);
	scrinfo.nPos = position;
	
	if (scrinfo.nPos < 0) {
		scrinfo.nPos = 0;
	}
	if (scrinfo.nPos + scrinfo.nPage > scrinfo.nMax) {
		scrinfo.nPos = scrinfo.nMax - scrinfo.nPage;
	}

	this->otherNoteForm->GetPageForm(this->current)->SetHScrinfo(scrinfo);

	SCROLLINFO hScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
	SCROLLINFO vScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetVScrinfo();
	this->scrollBar->SetScrollInfo(&hScrinfo);
	this->otherNoteForm->GetPageForm(this->current)->SetWindowPos(0, -hScrinfo.nPos, -vScrinfo.nPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}