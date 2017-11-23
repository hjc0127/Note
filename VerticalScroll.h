#pragma once
//VerticalScroll.h
#ifndef _VERTICALSCROLL_H
#define _VERTICALSCROLL_H

#include "Scroll.h"
#include "OtherNoteForm.h"

class VerticalScroll : public Scroll {
public:
	VerticalScroll(OtherNoteForm *otherNoteForm);
	VerticalScroll(const VerticalScroll& source);
	virtual ~VerticalScroll();
	VerticalScroll& operator=(const VerticalScroll& source);
	//virtual void UpdateLine();
	virtual void ScrollNextLine();
	virtual void ScrollPreviousLine();
	virtual void ScrollNextPage();
	virtual void ScrollPreviousPage();
	virtual void MoveThumb();
	virtual void ScrollPrevious(Long size);
	virtual void ScrollNext(Long size);
	//virtual void ScrollNextCharacter();
	//virtual void ScrollPreviousCharacter();
	virtual void ScrollFirst();
	virtual void ScrollLast();
	virtual void SetCurrent(Long index);
	void UpdateScrinfo(SCROLLINFO scrinfo);
	void ScrollToPosition(Long position);
};

#endif //_VERTICALSCROLL_H