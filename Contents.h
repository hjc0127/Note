#pragma once
//Contents.h

#ifndef _CONTENTS_H
#define _CONTENTS_H

typedef signed long int Long;

class Visitor;
class Contents {
public:
	Contents();
	Contents(const Contents& source);
	virtual ~Contents() = 0;
	Contents& operator=(const Contents& source);
	virtual Long Add(Contents *contents) { return -1; }
	virtual Long Insert(Long index, Contents *contents) { return -1; };
	virtual Long Remove(Long index) { return -1; }
	virtual Contents* GetAt(Long index) { return 0; }
	virtual Contents* Clone() const = 0;
	virtual void Accept(Visitor *visitor) = 0;
};

#endif	//_CONTENTS_H