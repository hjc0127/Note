#pragma once
//FindingForm.h

#ifndef _FINDINGFORM_H
#define _FINDINGFORM_H
#include "Array.h"
#include "FindIndex.h"
#include<afxdlgs.h>
//#include <afxwin.h>
//#include<Commdlg.h>

class Contents;
class OtherNoteForm;
class FindingForm :public CFindReplaceDialog{
public:
	FindingForm(Contents *contents);
	virtual ~FindingForm();
	FindingForm(const FindingForm& source);
	FindingForm& operator=(const FindingForm& source);
	void Create(OtherNoteForm *otherNoteForm);
	//virtual BOOL FindNext() const;
	//virtual BOOL IsTerminating() const;
	//virtual void EndDialog(int nResult);
	void Find(CString key);
	void EraseFindIndexes();
	FindIndex& GetAt(Long index);
	Array<FindIndex>& GetIndexes() const;
	Long GetCapacity();
	Long GetLength();
	CString& GetKey();
	CString& SetKey(CString key);
	Long GetCurrent();
	Long SetCurrent(Long current);
	Contents* GetContents() const;
	void SortFindIndexes();
	void CheckFindingTabItem();
	//afx_msg void OnClose();
	//DECLARE_MESSAGE_MAP()
	Long GetKeyLength();
	Long RemoveFindIndex(Long index);//1104
	void CancelFindingTabItem();//1104
	void ClearFindIndexes();//1104
	bool GetIsEdited() const;
	void SetIsEdited(bool isEdited);
	Long GetNextIndex();
	Long GetPreviousIndex();
	void ResetIndexes();
	afx_msg void OnClose();
private:
	
	afx_msg void PostNcDestroy();
	//afx_msg void OnKillFocus(CWnd* pNewWnd);
	DECLARE_MESSAGE_MAP()

public:
	static UINT WM_FIND;
	CString key;
	Array<FindIndex> indexes;
	Long capacity;
	Long length;
	Long current;
	//OtherNoteForm *otherNoteForm;
	Contents *contents;
	bool isEdited;
	//bool tempFlag;
};

inline Array<FindIndex>& FindingForm::GetIndexes() const {
	return const_cast<Array<FindIndex>&>(this->indexes);
}

inline Long FindingForm::GetCapacity() {
	return this->capacity;
}

inline Long FindingForm::GetLength() {
	return this->length;
}

inline CString& FindingForm::GetKey() {
	return this->key;
}

inline Long FindingForm::GetCurrent() {
	return this->current;
}

inline Contents* FindingForm::GetContents() const {
	return const_cast<Contents*>(this->contents);
}

inline bool FindingForm::GetIsEdited() const {
	return this->isEdited;
}

#endif	//_FINDVISITOR_H