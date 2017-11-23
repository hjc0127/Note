#pragma once
//Line.h

#ifndef _LINE_H
#define _LINE_H

#include "Composite.h"
#include <string>
using namespace std;

class Character;
class Line : public Composite {
public:
	Line(Long capacity = 256);
	Line(Long capacity, string str);
	Line(const Line& source);
	virtual ~Line();
	Line& operator=(const Line& source);
	Long Write(char value);
	Long Write(char value, Long width, Long height);
	Long Write(char *value);
	Long Erase();
	Long Erase(Long column);
	Character* GetCharacter(Long index);
	Character* operator[](Long index);
	Long GetColumn() const;
	virtual Contents* Clone() const;
	void Accept(Visitor* visitor);
	virtual ArrayIterator<Contents*>* CreateIterator() const;
	Long MoveFirstColumn();
	Long MovePreviousColumn();
	Long MoveNextColumn();
	Long MoveLastColumn();
	void SetColumn(Long index);
	Long GetWdith();
private:
	Long column;
};

inline Long Line::GetColumn() const {
	return this->column;
}

#endif	//_LINE_H