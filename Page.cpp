//Page.cpp

#include "Page.h"
#include "Memo.h"
#include "Line.h"
#include "Visitor.h"

Page::Page(Long capacity) 
	:Composite(capacity){
	this->current = -1;

	//this->currentMemo = Composite::Add(new Memo);
	//Memo *memo = this->GetMemo(this->currentMemo);
	//Line *line = memo->GetLine(memo->GetRow());

}

Page::Page(const Page& source)
	:Composite(source){
	this->current = source.current;
}

Page::~Page() {

}

Page& Page::operator=(const Page& source) {
	Composite::operator=(source);
	this->current = source.current;
	return *this;
}

Long Page::AddMemo() {
	this->current = Composite::Add(new Memo);
	return this->current;
}

Long Page::RemoveMemo() {
	Long index = Composite::Remove(this->current--);
	return index;
}

Memo* Page::GetMemo(Long index) {
	return static_cast<Memo*>(Composite::GetAt(index));
}

Memo* Page::operator[](Long index) {
	return static_cast<Memo*>(Composite::GetAt(index));
}

Contents* Page::Clone() const {
	return new Page(*this);
}

void Page::Accept(Visitor* visitor) {
	visitor->Visit(this);
}

ArrayIterator<Contents*>* Page::CreateIterator() const {
	return const_cast<ArrayIterator<Contents*>*>(new ArrayIterator<Contents*>(&this->contents));
}
void Page::SetCurrent(Long current) {
	this->current = current;
}