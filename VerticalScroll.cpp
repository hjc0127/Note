//VerticalScroll.cpp

#include "VerticalScroll.h"
#include "CharacterFaces.h"
#include "Caret.h"
#include "PageForm.h"

VerticalScroll::VerticalScroll(OtherNoteForm *otherNoteForm) 
	:Scroll(otherNoteForm){
	//1. scroll 생성
	CRect rect;
	this->otherNoteForm->GetClientRect(&rect);
	//this->scrollBar->Create(SBS_VERT, CRect(rect.right - 20, rect.top+30, rect.right, rect.bottom - 20), this->otherNoteForm, 1);
	this->scrollBar->Create(SBS_VERT, CRect(rect.right - 20, rect.top + 30 + 4, rect.right, rect.bottom - 20 - 4), this->otherNoteForm, 1);

	//2.캐럿 준비
	//Caret *caret = Caret::Instance(0);
	
	//3. 캐릭터페이스 준비
	//CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	//Long tabWidth = characterFaces->GetCharacterSize(97).GetWidth();
	
	//4. scroll 준비
	SCROLLINFO scrinfo;
	scrinfo.cbSize = sizeof(scrinfo);
	scrinfo.fMask = SIF_ALL;
	scrinfo.nMin = 0;
	scrinfo.nMax = rect.bottom - 20;//this->maxLineSize;//(rect.right / (characterFaces->GetCharacterSize(97).GetWidth())) - 1;	
	scrinfo.nPage = 150;//this ->maxLineSize / rect.right; //5;
	scrinfo.nPos = 0;
	this->scrollBar->SetScrollInfo(&scrinfo);
	this->scrollBar->ShowScrollBar(SB_BOTH);
	//this->scrollBar->EnableScrollBar(ESB_DISABLE_BOTH);
}

VerticalScroll::VerticalScroll(const VerticalScroll& source)
	:Scroll(source) {
}

VerticalScroll::~VerticalScroll() {

}

VerticalScroll& VerticalScroll::operator=(const VerticalScroll& source) {
	//
	Scroll::operator=(source);
	return *this;
}

#include "OtherNoteForm.h"
#include "Line.h"
#include "Memo.h"
#include "Character.h"
//void VerticalScroll::UpdateLine() {
//	Memo *memo = this->otherNoteForm->GetMemo();
//	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
//	Long height = characterFaces->GetCharacterSize(97).GetHeight();
//	this->maxLineSize = memo->GetLength() * height;
//
//	CRect rect;
//	this->otherNoteForm->GetClientRect(&rect);
//	if (this->maxLineSize > rect.bottom - 20) {
//		SCROLLINFO scrinfo;
//		this->scrollBar->GetScrollInfo(&scrinfo);
//		scrinfo.nMax = this->maxLineSize;//scrinfo.nPos + scrinfo.nPage + height;//this->maxLineSize;
//		scrinfo.nPage = rect.bottom - 20;
//		this->scrollBar->SetScrollInfo(&scrinfo);
//	}
//	else {
//		this->SetScrollUnVisible();
//	}
//}

void VerticalScroll::ScrollNextLine() {
	SCROLLINFO  scrinfo;
	this->scrollBar->GetScrollInfo(&scrinfo);

	if ((scrinfo.nPos + scrinfo.nPage) < scrinfo.nMax) {
		//CharacterFaces *characterFaces = CharacterFaces::Instance(0);
		Long height = 150;
		scrinfo.nPos += height;
		if (scrinfo.nPos + scrinfo.nPage > scrinfo.nMax) {
			scrinfo.nPos -= height;
			height -= scrinfo.nPos + scrinfo.nPage - scrinfo.nMax + height;
			scrinfo.nPos += height;
		}
		//자료구조에 저장
		this->otherNoteForm->GetPageForm(this->current)->SetVScrinfo(scrinfo);
		//윈도우 이동
		SCROLLINFO hScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
		SCROLLINFO vScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetVScrinfo();
		this->scrollBar->SetScrollInfo(&vScrinfo);
		this->otherNoteForm->GetPageForm(this->current)->SetWindowPos(0, -hScrinfo.nPos, -vScrinfo.nPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		/*this->scrollBar->SetScrollInfo(&scrinfo);
		CRect rect;
		this->otherNoteForm->GetClientRect(&rect);
		this->otherNoteForm->ScrollWindow(0, -height, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
		this->otherNoteForm->UpdateWindow();*/
	}
}

void VerticalScroll::ScrollPreviousLine() {
	SCROLLINFO  scrinfo;
	this->scrollBar->GetScrollInfo(&scrinfo);

	if (scrinfo.nPos > 0) {
		//CharacterFaces *characterFaces = CharacterFaces::Instance(0);
		Long height = 150;
		scrinfo.nPos -= height;
		if (scrinfo.nPos < 0) {
			scrinfo.nPos += height;
			height = scrinfo.nPos;
			scrinfo.nPos -= height;//=0
		}
		//자료구조에 저장
		this->otherNoteForm->GetPageForm(this->current)->SetVScrinfo(scrinfo);
		//윈도우 이동
		SCROLLINFO hScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
		SCROLLINFO vScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetVScrinfo();
		this->scrollBar->SetScrollInfo(&vScrinfo);
		this->otherNoteForm->GetPageForm(this->current)->SetWindowPos(0, -hScrinfo.nPos, -vScrinfo.nPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		/*this->scrollBar->SetScrollInfo(&scrinfo);
		CRect rect;
		this->otherNoteForm->GetClientRect(&rect);
		this->otherNoteForm->ScrollWindow(0, height, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
		this->otherNoteForm->UpdateWindow();*/
	}
}

void VerticalScroll::ScrollNextPage() {
	SCROLLINFO  scrinfo;
	this->scrollBar->GetScrollInfo(&scrinfo);
	Long height = scrinfo.nPage;
	if ((scrinfo.nPos + scrinfo.nPage) < scrinfo.nMax) {
		//CharacterFaces *characterFaces = CharacterFaces::Instance(0);
		scrinfo.nPos += scrinfo.nPage;
		if (scrinfo.nPos + scrinfo.nPage > scrinfo.nMax) {
			scrinfo.nPos -= scrinfo.nPage;
			height = scrinfo.nPage;
			height -= scrinfo.nPos + scrinfo.nPage - scrinfo.nMax + height;
			scrinfo.nPos += height;
		}
		//자료구조에 저장
		this->otherNoteForm->GetPageForm(this->current)->SetVScrinfo(scrinfo);
		//윈도우 이동
		SCROLLINFO hScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
		SCROLLINFO vScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetVScrinfo();
		this->scrollBar->SetScrollInfo(&vScrinfo);
		this->otherNoteForm->GetPageForm(this->current)->SetWindowPos(0, -hScrinfo.nPos, -vScrinfo.nPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		/*this->scrollBar->SetScrollInfo(&scrinfo);
		CRect rect;
		this->otherNoteForm->GetClientRect(&rect);
		this->otherNoteForm->ScrollWindow(0, -height, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
		this->otherNoteForm->UpdateWindow();*/
	}
}

void VerticalScroll::ScrollPreviousPage() {
	SCROLLINFO  scrinfo;
	this->scrollBar->GetScrollInfo(&scrinfo);
	Long height = scrinfo.nPage;
	if (scrinfo.nPos > 0) {
		//CharacterFaces *characterFaces = CharacterFaces::Instance(0);
		scrinfo.nPos -= height;
		if (scrinfo.nPos < 0) {
			scrinfo.nPos += height;
			height = scrinfo.nPos;
			scrinfo.nPos = 0;
		}
		//자료구조에 저장
		this->otherNoteForm->GetPageForm(this->current)->SetVScrinfo(scrinfo);
		//윈도우 이동
		SCROLLINFO hScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
		SCROLLINFO vScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetVScrinfo();
		this->scrollBar->SetScrollInfo(&vScrinfo);
		this->otherNoteForm->GetPageForm(this->current)->SetWindowPos(0, -hScrinfo.nPos, -vScrinfo.nPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	/*	this->scrollBar->SetScrollInfo(&scrinfo);
		CRect rect;
		this->otherNoteForm->GetClientRect(&rect);
		this->otherNoteForm->ScrollWindow(0, height, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
		this->otherNoteForm->UpdateWindow();*/
	}
}

void VerticalScroll::MoveThumb() {
	SCROLLINFO  scrinfo;
	this->scrollBar->GetScrollInfo(&scrinfo);
	Long height = scrinfo.nTrackPos - scrinfo.nPos;
	scrinfo.nPos = scrinfo.nTrackPos;
	//자료구조에 저장
	this->otherNoteForm->GetPageForm(this->current)->SetVScrinfo(scrinfo);
	//윈도우 이동
	SCROLLINFO hScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
	SCROLLINFO vScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetVScrinfo();
	this->scrollBar->SetScrollInfo(&vScrinfo);
	this->otherNoteForm->GetPageForm(this->current)->SetWindowPos(0, -hScrinfo.nPos, -vScrinfo.nPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	//this->scrollBar->SetScrollInfo(&scrinfo);

	/*CRect rect;
	this->otherNoteForm->GetClientRect(&rect);
	this->otherNoteForm->ScrollWindow(0, -height, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
	this->otherNoteForm->UpdateWindow();*/
}

void VerticalScroll::ScrollNext(Long size) {
	SCROLLINFO  scrinfo;
	this->scrollBar->GetScrollInfo(&scrinfo);

	if ((scrinfo.nPos + scrinfo.nPage) < scrinfo.nMax) {
		/*CharacterFaces *characterFaces = CharacterFaces::Instance(0);
		size = characterFaces->GetCharacterSize(97).GetHeight();*/
		scrinfo.nPos += size;
		if (scrinfo.nPos + scrinfo.nPage > scrinfo.nMax) {
			scrinfo.nPos -= size;
			size -= scrinfo.nPos + scrinfo.nPage - scrinfo.nMax + size;
			scrinfo.nPos += size;
		}
		//자료구조에 저장
		this->otherNoteForm->GetPageForm(this->current)->SetVScrinfo(scrinfo);
		//윈도우 이동
		SCROLLINFO hScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
		SCROLLINFO vScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetVScrinfo();
		this->scrollBar->SetScrollInfo(&vScrinfo);
		this->otherNoteForm->GetPageForm(this->current)->SetWindowPos(0, -hScrinfo.nPos, -vScrinfo.nPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		//scrinfo.nPos += size;
		//this->scrollBar->SetScrollInfo(&scrinfo);
		/*CRect rect;
		this->otherNoteForm->GetClientRect(&rect);
		this->otherNoteForm->ScrollWindow(0, -size, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
		this->otherNoteForm->UpdateWindow();*/
	}
}

void VerticalScroll::ScrollPrevious(Long size) {
	SCROLLINFO  scrinfo;
	this->scrollBar->GetScrollInfo(&scrinfo);

	if (scrinfo.nPos > 0) {
		/*CharacterFaces *characterFaces = CharacterFaces::Instance(0);
		Long height = characterFaces->GetCharacterSize(97).GetHeight();*/
		scrinfo.nPos -= size;
		if (scrinfo.nPos < 0) {
			scrinfo.nPos += size;
			size = scrinfo.nPos;
			scrinfo.nPos -= size;//=0
		}
		//자료구조에 저장
		this->otherNoteForm->GetPageForm(this->current)->SetVScrinfo(scrinfo);
		//윈도우 이동
		SCROLLINFO hScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
		SCROLLINFO vScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetVScrinfo();
		this->scrollBar->SetScrollInfo(&vScrinfo);
		this->otherNoteForm->GetPageForm(this->current)->SetWindowPos(0, -hScrinfo.nPos, -vScrinfo.nPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		/*scrinfo.nPos -= size;
		this->scrollBar->SetScrollInfo(&scrinfo);*/
		/*CRect rect;
		this->otherNoteForm->GetClientRect(&rect);
		this->otherNoteForm->ScrollWindow(0, size, CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20), CRect(rect.left, rect.top, rect.right - 20, rect.bottom - 20));
		this->otherNoteForm->UpdateWindow();*/
	}
}

//void VerticalScroll::ScrollNextCharacter() {
//}
//
//void VerticalScroll::ScrollPreviousCharacter() {
//}

void VerticalScroll::ScrollFirst() {
}

void VerticalScroll::ScrollLast() {
}

void VerticalScroll::SetCurrent(Long index) {
	this->current = index;
	SCROLLINFO hScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
	SCROLLINFO vScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetVScrinfo();
	this->scrollBar->SetScrollInfo(&vScrinfo);
	this->otherNoteForm->GetPageForm(index)->SetWindowPos(0, -hScrinfo.nPos, -vScrinfo.nPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void VerticalScroll::UpdateScrinfo(SCROLLINFO scrinfo) {
	this->scrollBar->SetScrollInfo(&scrinfo);
}

void VerticalScroll::ScrollToPosition(Long position) {
	SCROLLINFO  scrinfo;
	this->scrollBar->GetScrollInfo(&scrinfo);
	scrinfo.nPos = position;

	if (scrinfo.nPos < 0) {
		scrinfo.nPos = 0;
	}
	if (scrinfo.nPos + scrinfo.nPage > scrinfo.nMax) {
		scrinfo.nPos = scrinfo.nMax - scrinfo.nPage;
	}

	this->otherNoteForm->GetPageForm(this->current)->SetVScrinfo(scrinfo);

	SCROLLINFO hScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetHScrinfo();
	SCROLLINFO vScrinfo = this->otherNoteForm->GetPageForm(this->current)->GetVScrinfo();
	this->scrollBar->SetScrollInfo(&vScrinfo);
	this->otherNoteForm->GetPageForm(this->current)->SetWindowPos(0, -hScrinfo.nPos, -vScrinfo.nPos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}
