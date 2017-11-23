#pragma once

#ifndef __PAGE_H
#define __PAGE_H

#include "Composite.h"
#include "Memo.h"
typedef signed long int Long;

class Page : public Composite {
public :
	Page(Long capacity = 256);
	Page(const Page& source);
	virtual ~Page();
	Page& operator=(const Page& source);
	Long AddMemo();
	Long RemoveMemo();
	Memo* GetMemo(Long index);
	Memo* operator[](Long index);
	virtual Contents* Clone() const;
	void Accept(Visitor* visitor);
	virtual ArrayIterator<Contents*>* CreateIterator() const;
	Long GetCurrent() const;
	void SetCurrent(Long current);
private :
	Long current;
};

inline Long Page::GetCurrent() const {
	return this->current;
}

#endif //__PAGE_H

