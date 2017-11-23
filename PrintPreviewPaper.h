#pragma once
#ifndef _PRINTPREVIEWPAPER_H
#define _PRINTPREVIEWPAPER_H
typedef signed long int Long;
#define A4WIDTH 1190
#define A4HEIGHT 1683
#define PREVIEWWIDTH 833
#define PREVIEWHEIGHT 1178
#include <afxwin.h>

class PrintPreviewPaper : public CFrameWnd {
public:
	PrintPreviewPaper(Long paperWidth = A4WIDTH, Long paperHeight = A4HEIGHT, Long previewWidth = PREVIEWWIDTH, Long previewHeight = PREVIEWHEIGHT);
	~PrintPreviewPaper();
	PrintPreviewPaper(const PrintPreviewPaper& source);
	PrintPreviewPaper& operator=(const PrintPreviewPaper& source);
	Long GetPositionX() const;
	Long GetPositionY() const;
	Long GetPreviewWidth() const;
	Long GetPreviewHeight() const;
	void moveNextPaper();
	void movePreviousPaper();
	afx_msg void OnClose();
private:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	
	DECLARE_MESSAGE_MAP()
private:
	Long paperWidth;
	Long paperHeight;
	Long positionX;
	Long positionY;
	Long previewWidth;
	Long previewHeight;

};

inline Long PrintPreviewPaper::GetPositionX() const {
	return this->positionX;
}

inline Long PrintPreviewPaper::GetPositionY() const {
	return this->positionY;
}

inline Long PrintPreviewPaper::GetPreviewWidth() const {
	return this->previewWidth;
}

inline Long PrintPreviewPaper::GetPreviewHeight() const {
	return this->previewHeight;
}

#endif //_PRINTPREVIEWPAPER_H
