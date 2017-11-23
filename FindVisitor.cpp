//FindVisitor.cpp

#include "FindVisitor.h"
#include "Note.h"
#include "Page.h"
#include "Memo.h"
#include "Line.h"
#include "SingleCharacter.h"
#include "DoubleCharacter.h"
#include "ArrayIterator.h"
#include <afxWin.h>


FindVisitor::FindVisitor() 
	:Visitor(), key("") {
	this->length = 0;
	this->capacity = 100000;
}

FindVisitor::FindVisitor(const string& key) 
	:Visitor(), key(key){
	this->length = 0;
	this->capacity = 100000;
}

FindVisitor::FindVisitor(const string& key, const Array<FindIndex>& indexes)
	:Visitor(), key(key), indexes(indexes) {
	this->length = indexes.GetLength();
	this->capacity = indexes.GetCapacity();
}

FindVisitor::FindVisitor(const FindVisitor& source)
	: Visitor(source) {
	this->key = source.key;
	this->indexes = source.indexes;
	this->length = const_cast<FindVisitor&>(source).GetLength();
	this->capacity = const_cast<FindVisitor&>(source).GetCapacity();
}

FindVisitor::~FindVisitor() {

}

FindVisitor& FindVisitor::operator=(const FindVisitor& source) {
	Visitor::operator=(source);
	this->key = key;
	this->indexes = source.indexes;
	this->length = const_cast<FindVisitor&>(source).GetLength();
	this->capacity = const_cast<FindVisitor&>(source).GetCapacity();
	return *this;
}

void FindVisitor::Visit(Note *note) {
	ArrayIterator<Contents*> *pageIterator = note->CreateIterator();
	pageIterator->First();
	while (!pageIterator->IsDone()) {
		Page *page = static_cast<Page*>(pageIterator->CurrentItem());
		FindVisitor findVisitor(this->key);
		page->Accept(&findVisitor);
		Long i = 0;
		while (i < findVisitor.GetIndexes().GetLength()) {
			if (this->length < this->capacity) {
				this->indexes.Store(this->length, FindIndex(pageIterator->GetCurrent(), findVisitor.GetIndexes().GetAt(i).GetMemoIndex(), findVisitor.GetIndexes().GetAt(i).GetRow(), findVisitor.GetIndexes().GetAt(i).GetColumn()));
			}
			else {
				this->indexes.AppendFromRear(FindIndex(pageIterator->GetCurrent(), findVisitor.GetIndexes().GetAt(i).GetMemoIndex(), findVisitor.GetIndexes().GetAt(i).GetRow(), findVisitor.GetIndexes().GetAt(i).GetColumn()));
				this->capacity++;
			}
			this->length++;
			i++;
		}
		pageIterator->Next();
	}
	if (pageIterator != 0) {
		delete pageIterator;
	}
}

#include "OtherNoteForm.h"
#include "Note.h"
#include "PageForm.h"
#include "Page.h"
#include "MemoForm.h"
#include "Memo.h"
void FindVisitor::Visit(Page *page) {
	//1027
	OtherNoteForm *otherNoteForm = (OtherNoteForm*)(CWnd::FindWindow("OtherNote", NULL));
	Note *note = static_cast<Note*>(otherNoteForm->GetContents());
	Long pageIndex = 0;
	while (pageIndex < note->GetLength()
		&& note->GetPage(pageIndex) != page) {
		pageIndex++;
	} 
	PageForm *pageForm = otherNoteForm->GetPageForm(pageIndex);
	//

	ArrayIterator<Contents*> *memoIterator = page->CreateIterator();
	memoIterator->First();
	while (!memoIterator->IsDone()) {
		Memo *memo = static_cast<Memo*>(memoIterator->CurrentItem());

		//
		Long memoIndex = 0;
		while (memoIndex < page->GetLength() 
			&& memo != static_cast<Memo*>(pageForm->GetMemoForm(memoIndex)->GetContents())) {
			memoIndex++;
		}
		//
		FindVisitor findVisitor(this->key);
		memo->Accept(&findVisitor);
		Long i = 0;
		while (i < findVisitor.GetIndexes().GetLength()) {
			if (this->length < this->capacity) {
				//this->indexes.Store(this->length, FindIndex(-1, memoIterator->GetCurrent(), findVisitor.GetIndexes().GetAt(i).GetRow(), findVisitor.GetIndexes().GetAt(i).GetColumn()));
				//this->indexes.Store(this->length, FindIndex(-1, pageForm->GetMemoForm(memoIndex), findVisitor.GetIndexes().GetAt(i).GetRow(), findVisitor.GetIndexes().GetAt(i).GetColumn()));
				//this->indexes.Store(this->length, FindIndex(0, pageForm->GetMemoForm(memoIndex), findVisitor.GetIndexes().GetAt(i).GetRow(), findVisitor.GetIndexes().GetAt(i).GetColumn()));
				this->indexes.Store(this->length, FindIndex(pageIndex, pageForm->GetMemoForm(memoIndex), findVisitor.GetIndexes().GetAt(i).GetRow(), findVisitor.GetIndexes().GetAt(i).GetColumn()));
			}
			else {
				//this->indexes.AppendFromRear(FindIndex(-1, memoIterator->GetCurrent(), findVisitor.GetIndexes().GetAt(i).GetRow(), findVisitor.GetIndexes().GetAt(i).GetColumn()));
				//this->indexes.AppendFromRear(FindIndex(-1, pageForm->GetMemoForm(memoIndex), findVisitor.GetIndexes().GetAt(i).GetRow(), findVisitor.GetIndexes().GetAt(i).GetColumn()));
				//this->indexes.AppendFromRear(FindIndex(0, pageForm->GetMemoForm(memoIndex), findVisitor.GetIndexes().GetAt(i).GetRow(), findVisitor.GetIndexes().GetAt(i).GetColumn()));
				this->indexes.AppendFromRear(FindIndex(pageIndex, pageForm->GetMemoForm(memoIndex), findVisitor.GetIndexes().GetAt(i).GetRow(), findVisitor.GetIndexes().GetAt(i).GetColumn()));
				this->capacity++;
			}
			this->length++;
			i++;
		}
		memoIterator->Next();
	}
	if (memoIterator != 0) {
		delete memoIterator;
	}
}

void FindVisitor::Visit(Memo *memo) {
	ArrayIterator<Contents*> *lineIterator = memo->CreateIterator();
	lineIterator->First();
	while (!lineIterator->IsDone()) {
		Line *line = static_cast<Line*>(lineIterator->CurrentItem());
		FindVisitor findVisitor(this->key);
		line->Accept(&findVisitor);
		Long i = 0;
		while (i < findVisitor.GetIndexes().GetLength()) {
			if (this->length < this->capacity) {
				//this->indexes.Store(this->length, FindIndex(-1, -1, lineIterator->GetCurrent(), findVisitor.GetIndexes().GetAt(i).GetColumn()));
				this->indexes.Store(this->length, FindIndex(-1, 0, lineIterator->GetCurrent(), findVisitor.GetIndexes().GetAt(i).GetColumn()));
			}
			else {
				//this->indexes.AppendFromRear(FindIndex(-1, -1, lineIterator->GetCurrent(), findVisitor.GetIndexes().GetAt(i).GetColumn()));
				this->indexes.AppendFromRear(FindIndex(-1, 0, lineIterator->GetCurrent(), findVisitor.GetIndexes().GetAt(i).GetColumn()));
				this->capacity++;
			}
			this->length++;
			i++;
		}
		lineIterator->Next();
	}
	if (lineIterator != 0) {
		delete lineIterator;
	}
}

void FindVisitor::Visit(Line *line) {
	ArrayIterator<Contents*> *characterIterator = line->CreateIterator();
	ArrayIterator<Contents*> *checkingIterator = line->CreateIterator();
	Long keyLength = static_cast<Long>(this->key.length());
	Long i;
	Character *character;
	characterIterator->First();
	while (!characterIterator->IsDone()) {
		checkingIterator->operator=(*characterIterator); ///////////////////////(?)
		//checkingIterator = characterIterator;
		//bool isCorrect = true;
		bool isCorrect = false;
		i = 0;
		character = static_cast<Character*>(checkingIterator->CurrentItem());
		
		///////////1115
		Character *beforeCharacter;
		if (checkingIterator->GetCurrent() == 0) {
			isCorrect = true;
		}
		else {
			beforeCharacter = static_cast<Character*>(checkingIterator->GetItem(checkingIterator->GetCurrent() - 1));
			if (dynamic_cast<SingleCharacter*>(beforeCharacter)) {
				if (dynamic_cast<SingleCharacter*>(beforeCharacter)->GetValue() == ' ') {
					isCorrect = true;
				}
			}
		}
		//////////1115
		while (isCorrect == true && i < keyLength && !checkingIterator->IsDone()) {
			isCorrect = false;
 			if (dynamic_cast<SingleCharacter*>(character) 
				&& dynamic_cast<SingleCharacter*>(character)->GetValue() == key.at(i)){
				isCorrect = true;
			}
			else if (dynamic_cast<DoubleCharacter*>(character) 
				&& dynamic_cast<DoubleCharacter*>(character)->GetValue()[0] == key.at(i) 
				&& dynamic_cast<DoubleCharacter*>(character)->GetValue()[1] == key.at(i + 1)) {
				isCorrect = true;
			}
			if (key.at(i) >= 0 && key.at(i) <= 127) {//영문
 				i++;
			}
			else {
				i = i + 2;//한글
			}
			checkingIterator->Next();
			character = static_cast<Character*>(checkingIterator->CurrentItem());
		}

		if (isCorrect==true && i>=keyLength /*&& !checkingIterator->IsDone()*/) {
			//FindIndex columnIndex(-1, -1, -1, characterIterator->GetCurrent());
			FindIndex columnIndex(-1, 0, -1, characterIterator->GetCurrent());
			if (this->length < this->capacity) {
				this->indexes.Store(this->length, columnIndex);
			} 
			else {
				this->indexes.AppendFromRear(columnIndex);
				this->capacity++;
			}
			this->length++;
			while (characterIterator->GetCurrent() != checkingIterator->GetCurrent()) {
				//찾은거 색칠해 주는거 들어와야 한다 0919
				static_cast<Character*>(characterIterator->CurrentItem())->SetIsFindIndexPainted(true);
				characterIterator->Next();
			}
		}
		else {
			characterIterator->Next();
		}
	}
	if (characterIterator != 0) {
		delete characterIterator;
	}if (checkingIterator != 0) {
		delete checkingIterator;
	}
}

void FindVisitor::Visit(Character *character) {

}

void FindVisitor::Visit(SingleCharacter *singleCharacter) {

}

void FindVisitor::Visit(DoubleCharacter *doubleCharacter) {

}

FindIndex& FindVisitor::GetAt(Long index) {
	return this->indexes.GetAt(index);
}