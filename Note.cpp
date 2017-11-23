//Note.cpp

#include "Note.h"
#include "Page.h"
#include "Memo.h"
#include "Line.h"
#include "Visitor.h"
#include "ArrayIterator.h"

Note::Note(Long capacity)
	:Composite(capacity) 
{
	this->current = 0;
	//this->current = Composite::Add(new Page);
}

Note::Note(const Note& source)
	: Composite(source)
{
	this->current = source.current;
}

Note::~Note() {

}

Note& Note::operator=(const Note& source) {
	Composite::operator=(source);
	this->current = source.current;

	return *this;
}

Long Note::AddPage() {
	this->current = Composite::Add(new Page);

	return this->current;
}

Long Note::AddPage(Page *page) {
	this->current = Composite::Add(page);

	return this->current;
}

Long Note::InsertPage() {
	this->current = Composite::Insert(this->current, new Page);
	
	return this->current;
}

Long Note::InsertPage(Page *page) {
	this->current = Composite::Insert(this->current, page);

	return this->current;
}

Long Note::RemovePage() {
	Long index = Composite::Remove(this->current);
	this->current--;
	//if (this->current <0) {
	//	current++;
	//}			//남은 페이지가 없을 수 있음

	return index;
}

Page* Note::GetPage(Long index) {
	return static_cast<Page*>(Composite::GetAt(index));
}

Page* Note::operator[](Long index) {
	return static_cast<Page*>(Composite::GetAt(index));
}

Contents* Note::Clone() const {
	return new Note(*this);
}

void Note::Accept(Visitor* visitor) {
	visitor->Visit(this);
}

ArrayIterator<Contents*>* Note::CreateIterator() const {
	//return Composite::CreateIterator();
	return const_cast<ArrayIterator<Contents*>*>(new ArrayIterator<Contents*>(&this->contents));
}