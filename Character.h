#pragma once
//Character.h

#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "Contents.h"

typedef signed long int Long;

class Character :public Contents {
public:
	Character(Long width = 0, Long height = 0, bool highLight = false);
	Character(const Character& source);
	virtual ~Character() = 0;
	Character& operator=(const Character& source);
	Long GetWidth() const;
	Long GetHeight() const;
	bool GetHighLight() const;
	void SetHighLight(bool highLight);
	bool GetIsFindIndexPainted() const;
	void SetIsFindIndexPainted(bool isFindIndexPainted);
	void Accept(Visitor *visitor);
protected:
	Long width;
	Long height;
	bool highLight;
	bool isFindIndexPainted;
};

inline Long Character::GetWidth() const {
	return this->width;
}

inline Long Character::GetHeight() const {
	return this->height;
}

inline bool Character::GetHighLight() const {
	return this->highLight;
}

inline bool Character::GetIsFindIndexPainted() const {
	return this->isFindIndexPainted;
}

#endif	//_CHARACTER_H