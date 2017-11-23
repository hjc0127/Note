//SingleCharacter.cpp

#include "SingleCharacter.h"
#include "Visitor.h"


SingleCharacter::SingleCharacter() 
	:Character(){
	this->value = ' ';
}

SingleCharacter::SingleCharacter(char value, Long width, Long height) 
	:Character(width, height){
	this->value = value;
}

SingleCharacter::SingleCharacter(const SingleCharacter& source)
	: Character(source) {
	this->value = source.value;
}

SingleCharacter::~SingleCharacter() {

}

SingleCharacter& SingleCharacter::operator=(const SingleCharacter& source) {
	Character::operator=(source);
	this->value = source.value;
	return *this;
}

Contents* SingleCharacter::Clone() const {
	return new SingleCharacter(*this);
}

void SingleCharacter::Accept(Visitor *visitor) {
	visitor->Visit(this);
}