#pragma once
//Note.h

#ifndef _NOTE_H
#define _NOTE_H

#include "Composite.h"

class Line;
class Page;
class Note :public Composite {
public:
	Note(Long capacity = 64);
	Note(const Note& source);
	virtual ~Note();
	Note& operator=(const Note& source);
	Long AddPage();
	Long AddPage(Page *page);
	Long InsertPage();
	Long InsertPage(Page *page);
	Long RemovePage();
	Page* GetPage(Long index);
	Page* operator[](Long index);
	Long GetCurrent() const;
	void SetCurrent(Long current) const;
	virtual Contents* Clone() const;
	void Accept(Visitor* visitor);
	virtual ArrayIterator<Contents*>* CreateIterator() const;

private:
	Long current;
};

inline Long Note::GetCurrent() const {
	return this->current;
}

inline void Note::SetCurrent(Long current) const {
	const_cast<Note*>(this)->current = current;
	//static_cast<Long>(this->current) = current;
}

#endif	//_NOTE_H