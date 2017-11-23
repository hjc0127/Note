//Caret.h

#ifndef _CARET_H
#define _CARET_H

//#include <afxwin.h>
//using namespace std;

typedef signed long int Long;

class MemoForm;
class Caret {
public:
	Caret(MemoForm *memoForm);
	~Caret();
	Caret(const Caret& source);
	Caret& operator=(const Caret& source);
	void UpdateCaret();
	bool ChangeCaret();
	bool ChangeImeCaret();
	Long GetWidth() const;
	Long GetHeight() const;
	MemoForm* GetMemoForm() const;
	void ShowCaret();
	void HideCaret();
	Long GetXPosition();
	Long GetYPosition();
	
	//temp
	void Move(Long xPos, Long yPos);
private:
	Long width;
	Long height;
	MemoForm *memoForm;
};

inline Long Caret::GetWidth() const {
	return this->width;
}

inline Long Caret::GetHeight() const {
	return this->height;
}

inline MemoForm* Caret::GetMemoForm() const {
	return const_cast<MemoForm*>(this->memoForm);
}

#endif	//_CARET_H