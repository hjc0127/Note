// SingleCharacter.h

#ifndef _SINGLECHARACTER_H
#define _SINGLECHARACTER_H

#include "Character.h"

typedef signed long int Long;

class SingleCharacter :public Character {
public:
	SingleCharacter();
	SingleCharacter(char value, Long width, Long height);
	SingleCharacter(const SingleCharacter& source);
	virtual ~SingleCharacter();
	SingleCharacter& operator=(const SingleCharacter& source);
	char GetValue() const;
	virtual Contents* Clone() const;
	virtual void Accept(Visitor *visitor);
private:
	char value;
};

inline char SingleCharacter::GetValue() const {
	return this->value;
}

#endif	//_SINGLECHARACTER_H