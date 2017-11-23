#pragma once
//CharacterFaces.h

#ifndef _CHARACTERFACES_H
#define _CHARACTERFACES_H

#include "Array.h"
#include "CharacterSize.h"
#include <string>
using namespace std;

typedef signed long int Long;

class CDC;
class CharacterFaces {
public:
	~CharacterFaces();
	static CharacterFaces* Instance(CDC *dc);
	CharacterSize& GetCharacterSize(Long nChar);
	CharacterSize& operator[](Long nChar);
	string& GetFontFamily() const;
	string& GetFontStyle() const;
	Long GetFontSize() const;
	Long GetCapacity() const;
	Long GetLength() const;
	void SetFontFamily(string fontFamily);
	void SetFontStyle(string fontStyle);
	void SetFontSize(Long FontSize);
protected:
	CharacterFaces(CDC *dc);
	CharacterFaces(const CharacterFaces& source);
	CharacterFaces& operator=(const CharacterFaces& source);
private:
	static CharacterFaces* instance;
	string fontFamily;
	string fontStyle;
	Long fontSize;
	Array<CharacterSize> characterSizes;
	Long capacity;
	Long length;
};

inline string& CharacterFaces::GetFontFamily() const {
	return const_cast<string&>(this->fontFamily);
}

inline string& CharacterFaces::GetFontStyle() const {
	return const_cast<string&>(this->fontStyle);
}

inline Long CharacterFaces::GetFontSize() const {
	return this->fontSize;
}
inline Long CharacterFaces::GetCapacity() const {
	return this->capacity;
}

inline Long CharacterFaces::GetLength() const {
	return this->length;
}

#endif	//_CHARACTERFACES_H