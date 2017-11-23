// FindIndex.h

#ifndef _FINDINDEX_H
#define _FINDINDEX_H

typedef signed long int Long;

class MemoForm;
class FindIndex {
public:
	//FindIndex(Long pageIndex=0, Long memoIndex=0, Long row = 0, Long column = 0);
	FindIndex(Long pageIndex = 0, MemoForm *memoIndex = 0, Long row = 0, Long column = 0);
	FindIndex(const FindIndex& source);
	~FindIndex();
	FindIndex& operator=(const FindIndex& source);
	//bool IsEqual(const RowColumn& other);
	//bool IsNotEqual(const RowColumn& other);
	//bool operator==(const RowColumn& other);
	//bool operator!=(const RowColumn& other);
	//bool IsGreaterThan(const RowColumn& other);
	//bool IsLesserThan(const RowColumn& other);
	//bool operator<(const RowColumn& other);
	//bool operator<=(const RowColumn& other);
	//bool operator>(const RowColumn& other);
	//bool operator>=(const RowColumn& other);
	Long GetPageIndex() const;
	//Long GetMemoIndex();
	MemoForm* GetMemoIndex() const;
	Long GetRow() const;
	Long GetColumn() const;
private:
	Long pageIndex;
	//Long memoIndex;
	MemoForm *memoIndex;
	Long row;
	Long column;
};

inline Long FindIndex::GetPageIndex() const {
	return this->pageIndex;
}

//inline Long FindIndex::GetMemoIndex() {
//	return this->memoIndex;
//}

inline MemoForm* FindIndex::GetMemoIndex() const {
	return const_cast<MemoForm*>(this->memoIndex);
}

inline Long FindIndex::GetRow() const {
	return this->row;
}

inline Long FindIndex::GetColumn() const {
	return this->column;
}

#endif // FINDINDEX_H