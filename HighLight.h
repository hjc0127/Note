#pragma once

#ifndef _HIGHLIGHT_H
#define _HIGHLIGHT_H

#include <afxwin.h>
typedef signed long int Long;
class Memo;
class MemoForm;
class HighLight {
public:
	HighLight(MemoForm *memoForm, Long beginRow = 0, Long beginColumn = 0, Long endRow = 0, Long endColumn = 0, COLORREF crColor = RGB(255, 255, 102));
	~HighLight();
	HighLight(const HighLight& source);
	HighLight& operator = (const HighLight& source);
	Long GetBeginRow() const;
	Long GetBeginColumn() const;
	Long GetEndRow() const;
	Long GetEndColumn() const;
	void SetBegintRow(Long beginRow);
	void SetBeginColumn(Long beginColumn);
	void SetEndRow(Long endRow);
	void SetEndColumn(Long endColumn);
	void CopyToHighLightBuffer();
	Memo* GetHighLightBuffer() const;
	//MemoForm* GetMemoForm() const;

private:
	Long beginRow;
	Long beginColumn;
	Long endRow;
	Long endColumn;
	COLORREF crColor;
	Memo *highLightBuffer;
	MemoForm *memoForm;
};

inline Long HighLight::GetBeginRow() const {
	return this->beginRow;
}

inline Long HighLight::GetBeginColumn() const {
	return this->beginColumn;
}

inline Long HighLight::GetEndRow() const {
	return this->endRow;
}

inline Long HighLight::GetEndColumn() const {
	return this->endColumn;
}

inline Memo* HighLight::GetHighLightBuffer() const {
	return const_cast<Memo*>(this->highLightBuffer);
}

#endif //_HIGHLIGHT_H