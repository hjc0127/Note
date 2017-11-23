#pragma once
//MemoForm.h

#ifndef _MEMOFORM_H
#define _MEMOFROM_H

#include "Form.h"
#include "HighLight.h"
#include "Array.h"
//#include "ArrayIterator.h"
#include "resource1.h"
#include <afxwin.h>
#include <afxcmn.h>

#define MEMOFORM_WIDTH 300
#define MEMOFORM_HEIGH 200
#define MEMOFORM_MARGIN_LEFT 15
#define MEMOFORM_MARGIN_RIGHT 50
#define MEMOFORM_MARGIN_TOP 7
#define MEMOFORM_MARGIN_BOTTOM 10
#define MEMOFORM_CAPTION_HEIGHT 20
#define MEMOFORM_COLOR_PURPLE 1
#define MEMOFORM_COLOR_YELLOW 2
#define MEMOFORM_COLOR_GREEN 3
#define MEMOFORM_COLOR_BLUE 4
#define MEMOFORM_COLOR_PINK 5
#define MEMOFORM_COLOR_GRAY 6
#define MEMOFORM_FOCUS_CAPTION 1
#define MEMOFORM_FOCUS_CLIENT 2

class Contents;
class Visitor;
class Caret;
class SelectedBuffer;
class MemoForm : public CWnd, public Form {
public :
	MemoForm(Contents *contents = 0, Long positionX = 0, Long positionY = 0, Long width = MEMOFORM_WIDTH, Long height = MEMOFORM_HEIGH, Long color = -1, Long highLightCapacity = 100, Long marginWidth = MEMOFORM_MARGIN_LEFT, Long marginHeight = MEMOFORM_MARGIN_TOP, Long captionHeight = MEMOFORM_CAPTION_HEIGHT);
	~MemoForm();
	MemoForm(const MemoForm& source);
	MemoForm& operator = (const MemoForm& source);
	
	virtual Form* Clone() const;
	virtual void Accept(Visitor* visitor);

	bool GetEndComposition() const;
	Long GetPositionX() const;
	Long GetPositionY() const;
	void SetPositionX(Long positionX);
	void SetPositionY(Long positionY);
	Caret* GetCaret() const;
	void SetIsCaption(bool isCaption);
	bool GetIsCaption() const;
	void SetSelectedBuffer(SelectedBuffer* selectedBuffer);
	SelectedBuffer* GetSelectedBuffer() const;
	void CalculatePosition(Long *xPos, Long *yPos);
	void ReSizeWindow();
	Long GetMaxWidth() const;
	Long GetMaxHeight() const;
	void SetMaxWidth(Long width);
	void SetMaxHeight(Long height);
	Long UpdateMaxWidth();
	Long UpdateMaxHeight();
	Long GetMarginWidth() const;
	Long GetMarginHeight() const;
	Long GetCaptionHeight() const;
	void UpdateIndex(CPoint point);
	bool IsFocused();
	void RePosition();
	void OnEraseFindIndexes();
	bool GetIsFocused() const;
	bool GetIsHovered() const;
	void SetIsFocused(bool isFocused);
	void SetIsHovered(bool isHovered);
	void AutoReturn();
	void AutoReturnIme();
	void GetCaretPos(Long *xPosition, Long *yPosition);
	afx_msg void OnClose();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	void ChangeColorToPurple();
	void ChangeColorToYellow();
	void ChangeColorToGreen();
	void ChangeColorToBlue();
	void ChangeColorToPink();
	void ChangeColorToGray();
	Long GetColorType() const;
	Long GetFocusType() const;
	void SetFocusType(Long type);
	void SetColorType(Long colorType);

protected :
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnImeComposition(WPARAM wParam, LPARAM lParam);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg int OnMouseActivate(CWnd *pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg LRESULT OnNcHitTest(CPoint point);	
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnNcRButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnSetHighLight();
	afx_msg void OnHighLight();
	afx_msg void OnUnHighLight();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	
	afx_msg void OnMove(int x, int y);
	afx_msg void OnMoving(UINT nSide, LPRECT lpRect);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	DECLARE_MESSAGE_MAP()
private :
	Caret *caret;
	bool endComposition;
	Long positionX;
	Long positionY;
	bool isCaption;
	Long maxWidth;
	Long maxHeight;
	SelectedBuffer *selectedBuffer;
	Long highLightCapacity;
	Long highLightLength;
	Array<HighLight*> highLights;
	Long marginWidth;
	Long marginHeight;
	Long captionHeight;
	bool isFocused;
	bool isHovered;
	Long colorType;
	Long focusType;
};

inline Long MemoForm::GetColorType() const {
	return this->colorType;
}

inline bool MemoForm::GetEndComposition() const {
	return this->endComposition;
}

inline Long MemoForm::GetPositionX() const {
	return this->positionX;
}

inline Long MemoForm::GetPositionY() const {
	return this->positionY;
}

inline Caret* MemoForm::GetCaret() const {
	return const_cast<Caret*>(this->caret);
}

inline bool MemoForm::GetIsCaption() const {
	return this->isCaption;
}

inline SelectedBuffer* MemoForm::GetSelectedBuffer() const {
	return const_cast<SelectedBuffer*>(this->selectedBuffer);
}

inline Long MemoForm::GetMaxWidth() const {
	return this->maxWidth;
}
inline Long MemoForm::GetMaxHeight() const {
	return this->maxHeight;
}

inline Long MemoForm::GetMarginWidth() const {
	return this->marginWidth;
}

inline Long MemoForm::GetMarginHeight() const {
	return this->marginHeight;
}

inline Long MemoForm::GetCaptionHeight() const {
	return this->captionHeight;
}

inline bool MemoForm::GetIsFocused() const {
	return this->isFocused;
}

inline bool MemoForm::GetIsHovered() const {
	return this->isHovered;
}

inline Long MemoForm::GetFocusType() const {
	return this->focusType;
}

#endif	//_MEMOFORM_H