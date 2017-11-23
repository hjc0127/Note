//CharacterFaces.cpp

#include "CharacterFaces.h"
#include <afxWin.h>
using namespace std;

CharacterFaces* CharacterFaces::instance = 0;

CharacterFaces::CharacterFaces(CDC *dc)
	:characterSizes(96) {
	this->capacity = 96;
	this->length = 0;

	this->fontFamily = "Tahoma";
	//this->fontFamily = "Consolas";
	this->fontStyle = "Normal";
	this->fontSize = 100;
	
	CFont font;
	font.CreatePointFont(this->fontSize, this->fontFamily.c_str(), dc);
	dc->SelectObject(&font);
	
	Long i = 0;
	while (i <= 94) {
		CSize csize = dc->GetTextExtent(CString(static_cast<char>(i + 32)));
		this->characterSizes.Store(this->length, CharacterSize(csize.cx, csize.cy));
		this->length++;
		i++;
	}
	CSize csize = dc->GetTextExtent(CString("°ª"));
	this->characterSizes.Store(this->length, CharacterSize(csize.cx, csize.cy));
	this->length++;
}

CharacterFaces::CharacterFaces(const CharacterFaces& source)
	:characterSizes(source.characterSizes){
	this->instance = source.instance;
	this->fontFamily = source.fontFamily;
	this->fontStyle = source.fontStyle;
	this->fontSize = source.fontSize;
	this->capacity = source.capacity;
	this->length = source.length;
}

CharacterFaces::~CharacterFaces() {
	
}

CharacterFaces& CharacterFaces::operator=(const CharacterFaces& source) {
	this->instance = source.instance;
	this->fontSize = source.fontSize;
	this->characterSizes = source.characterSizes;
	this->capacity = source.capacity;
	this->length = source.length;
	return *this;
}

CharacterFaces* CharacterFaces::Instance(CDC *dc) {
	if (instance == 0) {
		instance = new CharacterFaces(dc);
	}
	return instance;
}

CharacterSize& CharacterFaces::GetCharacterSize(Long nChar) {
	return this->characterSizes.GetAt(nChar-32);
}

CharacterSize& CharacterFaces::operator[](Long nChar) {
	return this->characterSizes[nChar - 32];
}

void CharacterFaces::SetFontFamily(string fontFamily) {
	this->fontFamily = fontFamily;
}

void CharacterFaces::SetFontStyle(string fontStyle) {
	this->fontStyle = fontStyle;
}

void CharacterFaces::SetFontSize(Long fontSize) {
	this->fontSize = fontSize;
}