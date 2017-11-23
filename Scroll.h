// Scroll.h
#ifndef _SCROLL_H
#define _SCROLL_H

#include "OtherNoteForm.h"
typedef signed long int Long;

class Scroll {
public:
	Scroll(OtherNoteForm *otherNoteForm);
	Scroll(const Scroll& source);
	virtual ~Scroll() = 0;
	Scroll& operator=(const Scroll& source);
	virtual void ScrollNextLine() {};
	virtual void ScrollPreviousLine() {};
	virtual void ScrollNextPage() = 0;
	virtual void ScrollPreviousPage() = 0;
	virtual void MoveThumb() = 0;
	virtual void SetScrollVisible();
	virtual void SetScrollUnVisible();
	virtual void UpdateLine() {};
	virtual void ScrollPrevious(Long size) = 0;
	virtual void ScrollNext(Long size) = 0;
	virtual void ScrollNextCharacter() {};
	virtual void ScrollPreviousCharacter() {};
	virtual void ScrollFirst() = 0;
	virtual void ScrollLast() = 0;
	virtual void SetCurrent(Long index) = 0;
	Long GetCurrent() const;
	OtherNoteForm* GetOtherNoteForm() const;
	CScrollBar* GetScrollBar() const;
	Long GetMaxLineSize() const;

protected:
	OtherNoteForm *otherNoteForm;
	CScrollBar *scrollBar;
	Long maxLineSize;
	Long current;
};

inline OtherNoteForm* Scroll::GetOtherNoteForm() const {
	return const_cast<OtherNoteForm*>(this->otherNoteForm);
}

inline CScrollBar* Scroll::GetScrollBar() const {
	return const_cast<CScrollBar*>(this->scrollBar);
}

inline Long Scroll::GetMaxLineSize() const {
	return this->maxLineSize;
}

inline Long Scroll::GetCurrent() const {
	return this->current;
}

#endif //_SCROLL_H