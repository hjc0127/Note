// FindIndex.cpp

#include "FindIndex.h"
#include "MemoForm.h"
//FindIndex::FindIndex(Long pageIndex, Long memoIndex, Long row, Long column) {
FindIndex::FindIndex(Long pageIndex, MemoForm *memoIndex, Long row, Long column) {
	this->pageIndex = pageIndex;
	this->memoIndex = memoIndex;
	this->row = row;
	this->column = column;
}

FindIndex::FindIndex(const FindIndex& source) {
	this->pageIndex = source.pageIndex;
	this->memoIndex = source.memoIndex;
	this->row = source.row;
	this->column = source.column;
}

FindIndex::~FindIndex() {

}

FindIndex& FindIndex::operator=(const FindIndex& source) {
	this->pageIndex = source.pageIndex;
	this->memoIndex = source.memoIndex;
	this->row = source.row;
	this->column = source.column;

	return *this;
}

//bool RowColumn::IsEqual(const RowColumn& other) { return false; }
//bool RowColumn::IsNotEqual(const RowColumn& other) { return false; }
//bool RowColumn::operator==(const RowColumn& other) { return false; }
//bool RowColumn::operator!=(const RowColumn& other) { return false; }
//bool RowColumn::IsGreaterThan(const RowColumn& other) { return false; }
//bool RowColumn::IsLesserThan(const RowColumn& other) { return false; }
//bool RowColumn::operator<(const RowColumn& other) { return false; }
//bool RowColumn::operator<=(const RowColumn& other) { return false; }
//bool RowColumn::operator>(const RowColumn& other) { return false; }
//bool RowColumn::operator>=(const RowColumn& other) { return false; }
