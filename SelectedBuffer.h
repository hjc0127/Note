#pragma once
//SelectedBuffer.h

#ifndef _SELECTEDBUFFER_H
#define _SELECTEDBUFFER_H

#include <afxwin.h>

typedef signed long int Long;

//class OtherNoteForm;
class MemoForm;
class Memo;
class SelectedBuffer {
public:
	~SelectedBuffer();
	void SetPosition(Long currentRow, Long currentColumn);
//	void Move(Long currentRow, Long currentColumn);
	//void Copy(Long currentRow, Long currentColumn);
	void CopyToBuffer(Long currentRow, Long currentColumn);
	void CopyToClipboard();
//	void PasteToBuffer();
	CString GetClipboardString();
	void PasteToBuffer();
	void PasteToMemoForm();

	void SetInitialPosition(Long currentRow, Long currentColumn);
	
	Memo* GetBuffer() const;
	Long GetInitialRow() const;
	Long GetInitialColumn() const;
	Long GetBeginRow() const;
	Long GetBeginColumn() const;
	Long GetEndRow() const;
	Long GetEndColumn() const;

	bool GetIsSelecting() const;
	bool SetIsSelecting(bool isSelecting);
//	bool GetIsCopied() const;
//	bool SetIsCopied(bool isCopied);
	
	SelectedBuffer(MemoForm *memoForm, Long currentRow, Long currentColumn);
	SelectedBuffer(const SelectedBuffer& source);
	SelectedBuffer& operator=(const SelectedBuffer& source);
	BOOL CanPaste();
private:
	MemoForm *memoForm;
	Memo *buffer;
	Long initialRow;
	Long initialColumn;
	
	Long beginRow;
	Long beginColumn;
	Long endRow;
	Long endColumn;
	
	bool isSelecting;
//	bool isCopied;
};

inline Memo* SelectedBuffer::GetBuffer() const {
	return const_cast<Memo*>(this->buffer);
}

inline Long SelectedBuffer::GetInitialRow() const {
	return this->initialRow;
}

inline Long SelectedBuffer::GetInitialColumn() const {
	return this->initialColumn;
}

inline bool SelectedBuffer::GetIsSelecting() const {
	return this->isSelecting;
}

//inline bool SelectedBuffer::GetIsCopy() const {
//	return this->isCopy;
//}

//inline Long SelectedBuffer::GetCurrentRow() const {
//	return this->currentRow;
//}
//
//inline Long SelectedBuffer::GetCurrentColumn() const {
//	return this->currentColumn;
//}

inline Long SelectedBuffer::GetBeginRow() const {
	return this->beginRow;
}

inline Long SelectedBuffer::GetBeginColumn() const {
	return this->beginColumn;
}

inline Long SelectedBuffer::GetEndRow() const {
	return this->endRow;
}

inline Long SelectedBuffer::GetEndColumn() const {
	return this->endColumn;
}

//inline bool SelectedBuffer::GetEndSelection() const {
//	return this->endSelection;
//}

#endif	//_SELECTEDBUFFER_H