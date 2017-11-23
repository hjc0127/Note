// CharacterSize.cpp

#include "CharacterSize.h"

CharacterSize::CharacterSize(Long width, Long height) {
	this->width = width;
	this->height = height;
}

CharacterSize::CharacterSize(const CharacterSize& source) {
	this->width = source.width;
	this->height = source.height;
}

CharacterSize::~CharacterSize() {

}

CharacterSize& CharacterSize::operator=(const CharacterSize& source) {
	this->width = source.width;
	this->height = source.height;

	return *this;
}

//bool CharacterSize::IsEqual(const CharacterSize& other) { return false; }
//bool CharacterSize::IsNotEqual(const CharacterSize& other) { return false; }
//bool CharacterSize::operator==(const CharacterSize& other) { return false; }
//bool CharacterSize::operator!=(const CharacterSize& other) { return false; }
//bool CharacterSize::IsGreaterThan(const CharacterSize& other) { return false; }
//bool CharacterSize::IsLesserThan(const CharacterSize& other) { return false; }
//bool CharacterSize::operator<(const CharacterSize& other) { return false; }
//bool CharacterSize::operator<=(const CharacterSize& other) { return false; }
//bool CharacterSize::operator>(const CharacterSize& other) { return false; }
//bool CharacterSize::operator>=(const CharacterSize& other) { return false; }
