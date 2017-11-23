//CopyVisitor.cpp

#include "CopyVisitor.h"

CopyVisitor::CopyVisitor() {

}

CopyVisitor::~CopyVisitor() {

}

CopyVisitor::CopyVisitor(const CopyVisitor& source) {

}

CopyVisitor& CopyVisitor::operator=(const CopyVisitor& source) {
	return *this;
}

void CopyVisitor::Visit(Note *note) {

}

void CopyVisitor::Visit(Page *page) {

}

void CopyVisitor::Visit(Memo *memo) {

}

void CopyVisitor::Visit(Line *line) {

}

void CopyVisitor::Visit(Character *character) {

}

void CopyVisitor::Visit(SingleCharacter *singleCharacter) {

}

void CopyVisitor::Visit(DoubleCharacter *doubleCharacter) {

}

#include "PageForm.h"
#include "Page.h"
#include "MemoForm.h"
void CopyVisitor::Visit(PageForm *pageForm) {
	//1. 페이지를 복사한다.
	Page *page = new Page(*static_cast<Page*>(pageForm->GetContents()));
	
	//2. 페이지폼 복사
	this->form = new PageForm;
	*static_cast<PageForm*>(this->form) = *pageForm;
	//this->form = new PageForm(*pageForm);
	//2. 페이지폼내에 메모폼들 모두삭제
	Long i = 0;
	while (i < static_cast<PageForm*>(this->form)->GetLength()) {
		static_cast<PageForm*>(this->form)->RemoveMemoForm(0);
		i++;
	}
	//3.
	i = 0;
	while (i < pageForm->GetLength()) {
		CopyVisitor copyVisitor;
		MemoForm *memoForm = pageForm->GetMemoForm(i);
		memoForm->Accept(&copyVisitor);
		CRect rect;
		static_cast<PageForm*>(this->form)->AddMemoForm(static_cast<MemoForm*>(copyVisitor.GetForm()));
		i++;
	}
	
	//4.. 페이폼에 껴준다.
	this->form->SetContents(page);
}

#include "MemoForm.h"
#include "Memo.h"
void CopyVisitor::Visit(MemoForm *memoForm) {
	//1.메모복사해준다.
	Memo *memo = new Memo(*static_cast<Memo*>(memoForm->GetContents()));
	//2. 메모폼 복사
	this->form = new MemoForm;
	*static_cast<MemoForm*>(this->form) = *memoForm;
	//3. 메모폼에 껴준다.
	this->form->SetContents(memo);
}