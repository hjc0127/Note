#pragma once
//DoubleCharacter.h

#ifndef _DOUBLECHARACTER_H
#define _DOUBLECHARACTER_H

#include "Character.h"

class DoubleCharacter :public Character {
public:
	DoubleCharacter();
	DoubleCharacter(char* value, Long width, Long height);
	DoubleCharacter(const DoubleCharacter& source);
	virtual ~DoubleCharacter();
	DoubleCharacter& operator=(const DoubleCharacter& source);
	char* GetValue() const;
	virtual Contents* Clone() const;
	virtual void Accept(Visitor *visitor);
private:
	char value[2];
};

inline char* DoubleCharacter::GetValue() const {
	return const_cast<char*>(this->value);
}

#endif	//_DOUBLECHARACTER_H