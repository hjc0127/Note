// LoadVisitor.cpp

#include "LoadVisitor.h"
#include "CharacterFaces.h"
#include "Note.h"
#include "Page.h"
#include "Memo.h"
#include "Line.h"
#include "OtherNoteForm.h"
#include "PageForm.h"
#include "MemoForm.h"
#include <afxwin.h>
#include <string>
#include <stdlib.h>
//#define BUFFERSIZE 256
#define BUFFERSIZE 2048
using namespace std;

typedef signed long int Long;


LoadVisitor::LoadVisitor(LPTSTR lpstrFile)
	//:fs("OtherNote.txt", ios::in) {
	:fs(lpstrFile, ios::in) {
	//this->isEof = false;
	//this->isBad = false;
	//if(!(this->fs.bad())){
	//	this->isBad = true;
	//}
}

LoadVisitor::LoadVisitor(const LoadVisitor& source) {
	//:fs("OtherNote.txt", ios::in) {
	//:fs(source.fs, ios::in) {
	//재구현 필요
}

LoadVisitor::~LoadVisitor() {
	this->fs.close();
}

LoadVisitor& LoadVisitor::operator=(const LoadVisitor& source) {
	//재구현 필요
	return *this;
}

void LoadVisitor::Visit(Note *note) {
	/*char buffer[BUFFERSIZE];
	
	this->fs.getline(buffer, sizeof(buffer));
	Long count = stoi(buffer);

	Long i = 0;
	while (i < count) {
		Page *page = note->GetPage(i);
		page->Accept(this);
		note->AddPage();
		i++;
	}*/
}

void LoadVisitor::Visit(Page *page) {
	//char buffer[BUFFERSIZE];

	//if (!this->fs.fail()) {

	//	//1. Iterate line(s)
	//	this->fs.getline(buffer, sizeof(buffer));
	//	Long count = stoi(buffer);

	//	Long i = 0;
	//	while (i < count) {
	//		Memo *memo = page->GetMemo(i);
	//		memo->Accept(this);
	//		page->AddMemo();
	//		i++;
	//	}
	//	//memo->RemoveLine();
	//}
}

void LoadVisitor::Visit(Memo *memo) {
	char buffer[BUFFERSIZE];

	if (!this->fs.fail()) {
		//1. get number of line(s)
		this->fs.getline(buffer, sizeof(buffer));
		Long count = stoi(buffer);

		//2. Iterate line(s)
		Long i = 0;
		while (i < count) {
			Long index = memo->AddLine();
			memo->GetLine(index)->Accept(this);
			i++;
		}
	}
}

#include "SingleCharacter.h"
#include "DoubleCharacter.h"
void LoadVisitor::Visit(Line *line) {
	char buffer[BUFFERSIZE];

	//1. get number of character(s)
	this->fs.getline(buffer, sizeof(buffer));
	Long count = stoi(buffer);

	//2. Write character(s)
	Long j = 0;
	while (j < count) {
		//1. get character information
		this->fs.getline(buffer, sizeof(buffer));
		Long length = CString(buffer).GetLength();
		char doubleCharacter[2];
		Long index;
		Long i = 0;
		while (i < 1) {
			if (buffer[i] >= 0 && buffer[i] < 130) {
				index = line->Write(buffer[i]);
			}
			else {
				doubleCharacter[0] = buffer[i];
				doubleCharacter[1] = buffer[i + 1];
				i++;
				index = line->Write(doubleCharacter);
			}
			i++;
		}
		//2. set highLight flag
		char highLight = buffer[i + 1];
		Long highLightBool = stoi(&highLight);
		Character *character = line->GetCharacter(j);
		character->SetHighLight(highLightBool);

		j++;
	}
	//3. 라인 마지막 \n문자 읽어와서 무시하기
	this->fs.getline(buffer, sizeof(buffer));
}

void LoadVisitor::Visit(Character *character) {

}

void LoadVisitor::Visit(SingleCharacter *singleCharacter) {

}

void LoadVisitor::Visit(DoubleCharacter *doubleCharacter) {

}

#include <afxwin.h>
void LoadVisitor::Visit(OtherNoteForm *otherNoteForm) {
	char buffer[BUFFERSIZE];

	if (!this->fs.fail()) {
		//1. Set fontFamily
		CPaintDC dc(otherNoteForm);
		CharacterFaces *characterFaces = CharacterFaces::Instance(&dc);
		this->fs.getline(buffer, sizeof(buffer));
		characterFaces->SetFontFamily(static_cast<string>(buffer));

		//2. Set fontSize
		this->fs.getline(buffer, sizeof(buffer));
		Long fontSize = stoi(buffer);
		characterFaces->SetFontSize(fontSize);

		//4. Write Memo color 11/12
		this->fs.getline(buffer, sizeof(buffer));
		Long defaultMemoColor = stoi(buffer);
		otherNoteForm->SetDefaultMemoColor(defaultMemoColor);

		/////////////////////////////////////////////////////////
		//3. Set Current Page(11/11)
		this->fs.getline(buffer, sizeof(buffer));
		Long currentIndexOfPage = stoi(buffer);
		/////////////////////////////////////////////////////////

		//3. iterate  
		this->fs.getline(buffer, sizeof(buffer));
		Long pageCount = stoi(buffer);
		Long i = 0;
		while (i < pageCount) {
			//3.1. get pageFormName
			this->fs.getline(buffer, sizeof(buffer));
			
			//3.2 add Page & add PageForm
			Long index = static_cast<Note*>(otherNoteForm->GetContents())->AddPage();
			Long pageIndex = otherNoteForm->AddPageForm(static_cast<Note*>(otherNoteForm->GetContents())->GetPage(index), buffer);

			//3.3. set PageFormName
			//otherNoteForm->GetPageForm(index)->SetPageFormName(buffer);

			//3.3. set width, height of page
			this->fs.getline(buffer, sizeof(buffer));
			Long width = stoi(buffer);
			this->fs.getline(buffer, sizeof(buffer));
			Long height = stoi(buffer);
			otherNoteForm->GetPageForm(pageIndex)->SetWindowPos(NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW);
			otherNoteForm->GetPageForm(pageIndex)->UpdateScrinfo();

			//3.3. set nPos scroll
			SCROLLINFO hScrinfo;
			this->fs.getline(buffer, sizeof(buffer));
			hScrinfo = otherNoteForm->GetPageForm(pageIndex)->GetHScrinfo();
			hScrinfo.nPos = stoi(buffer);
			otherNoteForm->GetPageForm(pageIndex)->SetHScrinfo(hScrinfo);

			SCROLLINFO vScrinfo;
			this->fs.getline(buffer, sizeof(buffer));
			vScrinfo = otherNoteForm->GetPageForm(pageIndex)->GetVScrinfo();
			vScrinfo.nPos = stoi(buffer);
			otherNoteForm->GetPageForm(pageIndex)->SetVScrinfo(vScrinfo);
			//

			//3.4. load pageForm
			otherNoteForm->GetPageForm(pageIndex)->Accept(this);

			i++;
		}

		/////////////////////////////////////////////////////////
		//5. Set current page index in note 11/11
		static_cast<Note*>(otherNoteForm->GetContents())->SetCurrent(currentIndexOfPage);
		/////////////////////////////////////////////////////////
	}
}

#include "OtherNoteForm.h"
#include "HorizontalScroll.h"
#include "VerticalScroll.h"
void LoadVisitor::Visit(PageForm *pageForm) {
	char buffer[BUFFERSIZE];

	if (!this->fs.fail()) {
		//1. set pageFormName
		/*this->fs.getline(buffer, sizeof(buffer));
		pageForm->SetPageFormName(buffer);*/

		//2. get number of memo(s)
		this->fs.getline(buffer, sizeof(buffer));
		Long memoCount = stoi(buffer);

		//3. Add memoForm(s)
		Long i = 0;
		while (i < memoCount) {
			CPoint point;
			//1. Get positionX
			this->fs.getline(buffer, sizeof(buffer));
			point.x = stoi(buffer);
			
			//2. Get positionY
			this->fs.getline(buffer, sizeof(buffer));
			point.y = stoi(buffer);

			//3. Get width
			this->fs.getline(buffer, sizeof(buffer));
			Long width = stoi(buffer);

			//4. Get height
			this->fs.getline(buffer, sizeof(buffer));
			Long height = stoi(buffer);

			//1109 Get color
			this->fs.getline(buffer, sizeof(buffer));
			Long colorType = stoi(buffer);

			//5. add memo
			Long index = static_cast<Page*>(pageForm->GetContents())->AddMemo();

			//6. add memoForm
			CRect rect;
			rect.left = point.x;
			rect.top = point.y;
			rect.right = rect.left + width;
			rect.bottom = rect.top + height;
			//Long memoIndex = pageForm->AddMemoForm(static_cast<Page*>(pageForm->GetContents())->GetMemo(index), rect);
			Long memoIndex = pageForm->AddMemoForm(static_cast<Page*>(pageForm->GetContents())->GetMemo(index), rect, colorType);

			pageForm->GetMemoForm(memoIndex)->Accept(this);
			pageForm->GetMemoForm(memoIndex)->SetFocus(); //11/12

			i++;
		}
	}
}

void LoadVisitor::Visit(MemoForm *memoForm) {
	if (!this->fs.fail()) {
		//1. load memo
		memoForm->GetContents()->Accept(this);
	}
}