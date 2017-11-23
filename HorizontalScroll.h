// HorizontalScroll.h

#ifndef _HORIZONTALSCROLL_H
#define _HORIZONTALSCROLL_H

#include "Scroll.h"
#include "OtherNoteForm.h"
#include "Line.h"

class HorizontalScroll : public Scroll {
public:
	HorizontalScroll(OtherNoteForm *otherNoteForm);
	HorizontalScroll(const HorizontalScroll& source);
	virtual ~HorizontalScroll();
	HorizontalScroll& operator=(const HorizontalScroll& source);
	//virtual void UpdateLine();
	virtual void ScrollNextLine();
	virtual void ScrollPreviousLine();
	virtual void ScrollNextPage();
	virtual void ScrollPreviousPage();
	virtual void MoveThumb();
	virtual void ScrollNext(Long size);
	virtual void ScrollPrevious(Long size);
	/*virtual void ScrollNextCharacter();
	virtual void ScrollPreviousCharacter();*/
	virtual void ScrollFirst();
	virtual void ScrollLast();
	virtual void SetCurrent(Long index);
	virtual void UpdateScrinfo(SCROLLINFO scrinfo);
	void ScrollToPosition(Long position);
};

#endif //_HORIZONTALSCROLL_H