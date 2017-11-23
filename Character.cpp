//Character.cpp

#include "Character.h"
#include "Visitor.h"

Character::Character(Long width, Long height, bool highLight) {
	this->width = width;
	this->height = height;
	this->highLight = highLight;

	//this->isFindIndexPainted = isFindIndexPainted;
	this->isFindIndexPainted = false;
}

Character::Character(const Character& source) {
	this->width = source.width;
	this->height = source.height;
	this->highLight = source.highLight;

	this->isFindIndexPainted = source.isFindIndexPainted;

}

Character::~Character() {

}

Character& Character::operator=(const Character& source) {
	this->width = source.width;
	this->height = source.height;
	this->highLight = source.highLight;

	this->isFindIndexPainted = source.isFindIndexPainted;
	return *this;
}

void Character::SetHighLight(bool highLight) {
	this->highLight = highLight;
}

void Character::Accept(Visitor *visitor) {
	visitor->Visit(this);
}

void Character::SetIsFindIndexPainted(bool isFindIndexPainted) {
	this->isFindIndexPainted = isFindIndexPainted;
}