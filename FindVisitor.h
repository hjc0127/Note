//FindVisitor.h

#ifndef _FINDVISITOR_H
#define _FINDVISITOR_H

#include "Visitor.h"
#include "FindIndex.h"
#include "Array.h"
#include <string>
using namespace std;

typedef signed long int Long;

class Note;
class Page;
class Memo;
class Line;
class Character;
class SingleCharacter;
class DoubleCharacter;
class FindVisitor :public Visitor {
public:
	FindVisitor();
	FindVisitor(const string& key);
	FindVisitor(const string& key, const Array<FindIndex>& indexes);
	FindVisitor(const FindVisitor& source);
	virtual ~FindVisitor();
	FindVisitor& operator=(const FindVisitor& source);
	virtual void Visit(Note *note);
	virtual void Visit(Page *page);
	virtual void Visit(Memo *memo);
	virtual void Visit(Line *line);
	virtual void Visit(Character *character);
	virtual void Visit(SingleCharacter *singleCharacter);
	virtual void Visit(DoubleCharacter *doubleCharacter);
	Array<FindIndex>& GetIndexes() const;
	string& GetKey() const;
	FindIndex& GetAt(Long index);
	Long GetCapacity();
	Long GetLength();

private:
	string key;
	Array<FindIndex> indexes;
	Long capacity;
	Long length;
};
	

inline Array<FindIndex>& FindVisitor::GetIndexes() const {
	return const_cast<Array<FindIndex>&>(this->indexes); 
}

inline string& FindVisitor::GetKey() const {
	return const_cast<string&>(this->key);
}

inline Long FindVisitor::GetCapacity() {
	return this->capacity;
}

inline Long FindVisitor::GetLength() {
	return this->length;
}
#endif	//_FINDVISITOR_H