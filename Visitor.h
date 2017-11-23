#pragma once
//Visitor.h

#ifndef _VISITOR_H
#define _VISITOR_H

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

class Visitor {
public:
	Visitor();
	virtual ~Visitor() = 0;
	Visitor(const Visitor& source);
	Visitor& operator=(const Visitor& source);
	virtual void Visit(Note *note) = 0;
	virtual void Visit(Page *page) = 0;
	virtual void Visit(Memo *memo) = 0;
	virtual void Visit(Line *line) = 0;
	virtual void Visit(Character *character) = 0;
	virtual void Visit(SingleCharacter *singleCharacter) = 0;
	virtual void Visit(DoubleCharacter *doubleCharaceter) = 0;

	virtual void Visit(OtherNoteForm *otherNoteForm) { };// = 0;
	virtual void Visit(PageForm *pageForm) {};// = 0;
	virtual void Visit(MemoForm *memoForm) {};// = 0;
};

#endif	//_VISITOR_H