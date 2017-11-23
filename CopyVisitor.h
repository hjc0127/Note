#pragma once
//CopyVisitor.h
#include "Visitor.h"
#ifndef _COPYVISITOR_H
#define _COPYVISITOR_H

class Note;
class Page;
class Memo;
class Line;
class Character;
class SingleCharacter;
class DoubleCharacter;
class OtherNoteForm;
class PageForm;
class MemoForm;
class Form;

class CopyVisitor : public Visitor{
public:
	CopyVisitor();
	virtual ~CopyVisitor();
	CopyVisitor(const CopyVisitor& source);
	CopyVisitor& operator=(const CopyVisitor& source);
	virtual void Visit(Note *note);
	virtual void Visit(Page *page);
	virtual void Visit(Memo *memo);
	virtual void Visit(Line *line);
	virtual void Visit(Character *character);
	virtual void Visit(SingleCharacter *singleCharacter);
	virtual void Visit(DoubleCharacter *doubleCharaceter);

	virtual void Visit(PageForm *pageForm);
	virtual void Visit(MemoForm *memoForm);
	Form* GetForm() const;
private:
	Form *form;
};

inline Form* CopyVisitor::GetForm() const {
	return const_cast<Form*>(this->form);
}

#endif	//_COPYVISITOR_H