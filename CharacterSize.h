// CharacterSize.h

#ifndef _CHARACTERSIZE_H
#define _CHARACTERSIZE_H

typedef signed long int Long;

class CharacterSize {
public:
	CharacterSize(Long width = 0, Long height = 0);
	CharacterSize(const CharacterSize& source);
	~CharacterSize();
	CharacterSize& operator=(const CharacterSize& source);
	//bool IsEqual(const CharacterSize& other);
	//bool IsNotEqual(const CharacterSize& other);
	//bool operator==(const CharacterSize& other);
	//bool operator!=(const CharacterSize& other);
	//bool IsGreaterThan(const CharacterSize& other);
	//bool IsLesserThan(const CharacterSize& other);
	//bool operator<(const CharacterSize& other);
	//bool operator<=(const CharacterSize& other);
	//bool operator>(const CharacterSize& other);
	//bool operator>=(const CharacterSize& other);
	Long GetWidth() const;
	Long GetHeight() const;
private:
	Long width;
	Long height;
};

inline Long CharacterSize::GetWidth() const{
	return this->width;
}

inline Long CharacterSize::GetHeight() const {
	return this->height;
}

#endif // CHARACTERSIZE_H