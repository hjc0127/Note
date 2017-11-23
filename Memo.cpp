//Memo.cpp

#include "Memo.h"
#include "Line.h"
#include "Visitor.h"
#include "ArrayIterator.h"

Memo::Memo(Long capacity)
	:Composite(capacity)
{
	//this->row = Composite::Add(new Line);
	this->row = 0;
}

Memo::Memo(const Memo& source)
	: Composite(source)
{
	this->row = source.row;
}

Memo::~Memo() {

}

Memo& Memo::operator=(const Memo& source) {
	Composite::operator=(source);
	this->row = source.row;

	return *this;
}

Long Memo::AddLine() {
	this->row = Composite::Add(new Line);

	return this->row;
}

Long Memo::InsertLine() {
	this->row = Composite::Insert(++this->row, new Line);
	
	return this->row;
}

Long Memo::RemoveLine() {
	Long index = Composite::Remove(this->row--);

	return index;
}

Line* Memo::GetLine(Long index) {
	return static_cast<Line*>(Composite::GetAt(index));
}

Line* Memo::operator[](Long index) {
	return static_cast<Line*>(Composite::GetAt(index));
}

Contents* Memo::Clone() const {
	return new Memo(*this);
}

void Memo::Accept(Visitor* visitor) {
	visitor->Visit(this);
}

ArrayIterator<Contents*>* Memo::CreateIterator() const {
	//return Composite::CreateIterator();
	return const_cast<ArrayIterator<Contents*>*>(new ArrayIterator<Contents*>(&this->contents));
}

Long Memo::MoveFirstRow() {
	this->row = 0;
	return this->row;
}

Long Memo::MovePreviousRow() {
	return --this->row;
}

Long Memo::MoveNextRow() {
	return ++this->row;
}

Long Memo::MoveLastRow() {
	this->row = this->length - 1;
	return this->row;
}

void Memo::SetRow(Long index) {
	this->row = index;
}

#include "Character.h"
void Memo::SetHighLightMode(Long startRow, Long startColumn, Long endRow, Long endColumn, bool mode) {
	Long i = startRow;
	Long j = startColumn;
	while (i <= endRow) {
		if (i > startRow) {
			j = 0;
		}
		Long length = this->GetLine(i)->GetLength();
		if (i == endRow) {
			length = endColumn;
		}
		while (j < length) {
			this->GetLine(i)->GetCharacter(j)->SetHighLight(mode);
			j++;
		}
		i++;
	}
}
//
//void Memo::UnHighLightMemo(Long startRow, Long startColumn, Long endRow, Long endColumn) {
//	Long i = startRow;
//	Long j = startColumn;
//	while (i <= endRow) {
//		if (i > startRow) {
//			j = 0;
//		}
//		Long length = this->GetLine(i)->GetLength();
//		if (i == endRow) {
//			length = endColumn;
//		}
//		while (j < length) {
//			this->GetLine(i)->GetCharacter(j)->SetHighLight(false);
//			j++;
//		}
//		i++;
//	}
//}
