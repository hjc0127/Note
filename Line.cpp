//Line.cpp

#include "Line.h"
#include "SingleCharacter.h"
#include "DoubleCharacter.h"
#include "Visitor.h"
#include "ArrayIterator.h"
#include "CharacterFaces.h"
#include "CharacterSize.h"

#define HANGUL 127

Line::Line(Long capacity)
	:Composite(capacity) {
	this->column = 0;
}

Line::Line(Long capacity, string str)
	:Composite(capacity) {
	this->column = 0;
	CharacterFaces *characterFaces = CharacterFaces::Instance(0);

	Long i = 0;
	while (i < str.length()) {
		if (str[i] >= 32 && str[i] < 128) {
			CharacterSize characterSize(characterFaces->GetCharacterSize(static_cast<Long>(str[i])));
			Composite::Add(new SingleCharacter(str[i], characterSize.GetWidth(), characterSize.GetHeight()));
		}
		else if (str[i] < 0) {
			CharacterSize characterSize(characterFaces->GetCharacterSize(HANGUL));
			char character[2];
			character[0] = str[i];
			i++;
			character[1] = str[i];
			Composite::Add(new DoubleCharacter(character, characterSize.GetWidth(), characterSize.GetHeight()));
		}
		this->column++;
		i++;
	}
}

Line::Line(const Line& source)
	:Composite(source) {
	this->column = source.column;
}

Line::~Line() {

}

Line& Line::operator=(const Line& source) 
{	
	Composite::operator=(source);
	this->column = source.column;

	return *this;
}

Long Line::Write(char value) {
	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	CharacterSize characterSize = characterFaces->GetCharacterSize(static_cast<Long>(value));

	Long index;
	if (this->column == this->length) {
		index = Composite::Add(new SingleCharacter(value, characterSize.GetWidth(), characterSize.GetHeight()));
	}
	else {
		index = Composite::Insert(this->column, new SingleCharacter(value, characterSize.GetWidth(), characterSize.GetHeight()));
	}
	this->column++;

	return index;
}

Long Line::Write(char value, Long width, Long height) {
	Long index;
	if (this->column == this->length) {
		index = Composite::Add(new SingleCharacter(value, width, height));
	}
	else {
		index = Composite::Insert(this->column, new SingleCharacter(value, width, height));
	}
	this->column++;

	return index;
}

Long Line::Write(char* value) {
	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	CharacterSize characterSize = characterFaces->GetCharacterSize(HANGUL);

	Long index;
	if (this->column == this->length) {
		index = Composite::Add(new DoubleCharacter(value, characterSize.GetWidth(), characterSize.GetHeight()));
	}
	else {
		index = Composite::Insert(this->column, new DoubleCharacter(value, characterSize.GetWidth(), characterSize.GetHeight()));
	}
	this->column++;

	return index;
}

Long Line::Erase() {
	Long index = Composite::Remove(--this->column);

	return index;
}

Long Line::Erase(Long column) {
	Long index = Composite::Remove(column);
	return index;
}

Character* Line::GetCharacter(Long index) {
	return static_cast<Character*>(Composite::GetAt(index));

}

Character* Line::operator[](Long index) {
	return static_cast<Character*>(Composite::GetAt(index));
}

Contents* Line::Clone() const {
	return new Line(*this);
}

void Line::Accept(Visitor* visitor) {
	visitor->Visit(this);
}

ArrayIterator<Contents*>* Line::CreateIterator() const {
	//return Composite::CreateIterator();
	return const_cast<ArrayIterator<Contents*>*>(new ArrayIterator<Contents*>(&this->contents));
}

Long Line::MoveFirstColumn() {
	this->column = 0;
	return this->column;
}

Long Line::MovePreviousColumn() {
	return --this->column;
}

Long Line::MoveNextColumn() {
	return ++this->column;
}

Long Line::MoveLastColumn() {
	this->column = this->length;
	return this->column;
}

void Line::SetColumn(Long index) {
	this->column = index;
}

Long Line::GetWdith() {
	Long i = 0;
	Long width = 0;
	while (i < this->GetLength()) {
		width += this->GetCharacter(i)->GetWidth();
		i++;
	}
	return width;
}