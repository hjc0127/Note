// SaveVisitor.cpp
#include "SaveVisitor.h"
#include "MakeStringVisitor.h"
#include "CharacterFaces.h"
#include "Note.h"
#include "Page.h"
#include "Memo.h"
#include "Line.h"
#include "OtherNoteForm.h"
#include "PageForm.h"
#include "MemoForm.h"
#include "SingleCharacter.h"
#include "DoubleCharacter.h"

SaveVisitor::SaveVisitor(LPTSTR lpstrFile)
	//:fs("OtherNote.txt", ios::out | ios::trunc) {
	:fs(lpstrFile, ios::out | ios::trunc) {
	this->saveFileName = CString(lpstrFile);
}

SaveVisitor::SaveVisitor(const SaveVisitor& source)
	//:fs("OtherNote.txt", ios::out | ios::trunc) {
	//: fs(source.lptstrFile, ios::out | ios::trunc) {
	: fs(source.saveFileName, ios::out | ios::trunc) {
	this->saveFileName = source.saveFileName;
}

SaveVisitor::~SaveVisitor(){
	this->fs.close();
}

SaveVisitor& SaveVisitor::operator=(const SaveVisitor& source) {
	this->fs = fstream(source.saveFileName, ios::out | ios::trunc);
	this->saveFileName = source.saveFileName;
	return *this;
}

void SaveVisitor::Visit(Note *note) {
	//1. Iterate page(s)
	ArrayIterator<Contents*> *noteIterator = note->CreateIterator();
	noteIterator->First();
	while (!noteIterator->IsDone()) {
		noteIterator->CurrentItem()->Accept(this);
		this->fs << endl;
		noteIterator->Next();
	}

	if (noteIterator != 0) {
		delete noteIterator;
		noteIterator = 0;
	}
}

void SaveVisitor::Visit(Page *page) {
	//1. Iterate memo(s)
	ArrayIterator<Contents*> *pageIterator = page->CreateIterator();
	pageIterator->First();
	while (!pageIterator->IsDone()) {
		pageIterator->CurrentItem()->Accept(this);
		this->fs << endl;
		pageIterator->Next();
	}

	if (pageIterator != 0) {
		delete pageIterator;
		pageIterator = 0;
	}
}

void SaveVisitor::Visit(Memo *memo) {
	//1. Iterate line(s)
	ArrayIterator<Contents*> *memoIterator = memo->CreateIterator();
	memoIterator->First();
	while (!memoIterator->IsDone()) {
		memoIterator->CurrentItem()->Accept(this);
		memoIterator->Next();
	}

	if (memoIterator != 0) {
		delete memoIterator;
		memoIterator = 0;
	}
}

void SaveVisitor::Visit(Line *line) {
	//1. Write lines
	this->fs << line->GetLength() << endl;

	//2. Iterate character(s)
	ArrayIterator<Contents*> *lineIterator = line->CreateIterator();
	lineIterator->First();
	while (!lineIterator->IsDone()) {
		lineIterator->CurrentItem()->Accept(this);
		lineIterator->Next();
	}

	if (lineIterator != 0) {
		delete lineIterator;
		lineIterator = 0;
	}
}

void SaveVisitor::Visit(Character *character) {

}

void SaveVisitor::Visit(SingleCharacter *singleCharacter) {
	//1. Write singleCharacter
	MakeStringVisitor makeStringVisitor;
	singleCharacter->Accept(&makeStringVisitor);
	this->fs << makeStringVisitor.GetCompleteString().c_str() << " " << singleCharacter->GetHighLight() << endl;
}

void SaveVisitor::Visit(DoubleCharacter *doubleCharacter) {
	//1. Write doubleCharacter
	MakeStringVisitor makeStringVisitor;
	doubleCharacter->Accept(&makeStringVisitor);
	this->fs << makeStringVisitor.GetCompleteString().c_str() << " " << doubleCharacter->GetHighLight() << endl;
}

void SaveVisitor::Visit(OtherNoteForm *otherNoteForm) {
	//1. Write File name
	//To do 

	//2. Write font family
	CharacterFaces *characterFaces = CharacterFaces::Instance(0);
	this->fs << characterFaces->GetFontFamily().c_str() << endl;
	
	//3. Write font size
	this->fs << characterFaces->GetFontSize() << endl;

	//4. Write Memo color 11/12
	this->fs << otherNoteForm->GetDefaultMemoColor() << endl;

	/////////////////////////////////////////////////////////
	//3. Wirte current Page index(11/11)
	this->fs << static_cast<Note*>(otherNoteForm->GetContents())->GetCurrent() << endl;
	/////////////////////////////////////////////////////////

	//4. Write count of page(s)
	this->fs << static_cast<Note*>(otherNoteForm->GetContents())->GetLength() << endl;
	
	//5. Iterate pageForm(s)
	ArrayIterator<Form*> *noteFormIterator = otherNoteForm->CreateIterator();
	noteFormIterator->First();
	while (!noteFormIterator->IsDone()) {
		noteFormIterator->CurrentItem()->Accept(this);
		noteFormIterator->Next();
	}

	if (noteFormIterator != 0) {
		delete noteFormIterator;
		noteFormIterator = 0;
	}
}

void SaveVisitor::Visit(PageForm *pageForm) {
	//1. Write Page name
	this->fs << pageForm->GetPageFormName() << endl;

	//2. Wriet page width, height
	CRect pageWndRect;
	pageForm->GetWindowRect(&pageWndRect);
	this->fs << pageWndRect.Width() << endl;
	this->fs << pageWndRect.Height() << endl;

	//2. Write nPos of scroll
	this->fs << pageForm->GetHScrinfo().nPos << endl;
	this->fs << pageForm->GetVScrinfo().nPos << endl;

	//2. Write count of Memo(s)
	this->fs << static_cast<Page*>(pageForm->GetContents())->GetLength() << endl;

	//3. Iterate memoForm(s)
	ArrayIterator<Form*> *pageFormIterator = pageForm->CreateIterator();
	pageFormIterator->First();
	while (!pageFormIterator->IsDone()) {
		pageFormIterator->CurrentItem()->Accept(this);
		pageFormIterator->Next();
	}

	if (pageFormIterator != 0) {
		delete pageFormIterator;
		pageFormIterator = 0;
	}
}

void SaveVisitor::Visit(MemoForm *memoForm) {
	//1. Write Position of MemoForm
	this->fs << memoForm->GetPositionX() << endl;
	this->fs << memoForm->GetPositionY() << endl;

	//2. Write width, height of MemoForm
	this->fs << memoForm->GetMaxWidth() << endl;
	this->fs << memoForm->GetMaxHeight() << endl;

	//1109 Write color of MemoForm
	this->fs << memoForm->GetColorType() << endl;

	//2. Write count of Line(s)
	this->fs << static_cast<Memo*>(memoForm->GetContents())->GetLength() << endl;

	//3. Iterate line(s)
	ArrayIterator<Contents*> *memoIterator = static_cast<Memo*>(memoForm->GetContents())->CreateIterator();
	memoIterator->First();
	while (!memoIterator->IsDone()) {
		memoIterator->CurrentItem()->Accept(this);
		this->fs << endl;
		memoIterator->Next();
	}

	if (memoIterator != 0) {
		delete memoIterator;
		memoIterator = 0;
	}
}