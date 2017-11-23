//DoubleCharacter.cpp

#include "DoubleCharacter.h"
#include "Visitor.h"

DoubleCharacter::DoubleCharacter()
	:Character() {
	this->value[0] = ' ';
	this->value[1] = ' ';
}

DoubleCharacter::DoubleCharacter(char* value, Long width, Long height)
	: Character(width, height) {
	this->value[0] = value[0];
	this->value[1] = value[1];
}

DoubleCharacter::DoubleCharacter(const DoubleCharacter& source)
	: Character(source)
{
	this->value[0] = source.value[0];
	this->value[1] = source.value[1];
}

DoubleCharacter::~DoubleCharacter() {

}

DoubleCharacter& DoubleCharacter::operator=(const DoubleCharacter& source)
{
	Character::operator=(source);
	this->value[0] = source.value[0];
	this->value[1] = source.value[1];

	return *this;
}

Contents* DoubleCharacter::Clone() const {
	return new DoubleCharacter(*this);
}

void DoubleCharacter::Accept(Visitor *visitor) {
	visitor->Visit(this);
}