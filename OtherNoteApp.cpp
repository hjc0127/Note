//OtherNoteApp.cpp

#include "OtherNoteApp.h"
#include "OtherNoteForm.h"
#include "Note.h"
#include "PageForm.h"
#include "resource1.h"
//#include <crtdbg.h>//메모리 릭 체크
BOOL OtherNoteApp::InitInstance() {

	OtherNoteForm *otherNoteForm = new OtherNoteForm(new Note);
	
	//CString otherNote = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW, NULL, (HBRUSH)GetStockObject(WHITE_BRUSH), NULL);
	otherNoteForm->Create("otherNote", "제목없음", WS_OVERLAPPEDWINDOW | WS_MAXIMIZE, CFrameWnd::rectDefault, NULL, (LPCTSTR)IDR_MENU_MAIN, 0, NULL);

	//otherNoteForm->Create(NULL, "OtherNote", WS_OVERLAPPEDWINDOW, CFrameWnd::rectDefault, NULL, (LPCTSTR)IDR_MENU_MAIN, 0, NULL);
	//otherNoteForm->Create(NULL, "OtherNote", WS_OVERLAPPEDWINDOW | WS_MAXIMIZE, CFrameWnd::rectDefault, NULL, (LPCTSTR)IDR_MENU_MAIN, 0, NULL);
	//otherNoteForm->Create(NULL, "제목없음", WS_OVERLAPPEDWINDOW | WS_MAXIMIZE, CFrameWnd::rectDefault, NULL, (LPCTSTR)IDR_MENU_MAIN, 0, NULL);
	//otherNoteForm->Create(NULL, "OtherNote", WS_CAPTION | WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX, CFrameWnd::rectDefault, NULL, (LPCTSTR)IDR_MENU1, 0, NULL);
	//otherNoteForm->ShowWindow(SW_SHOWMAXIMIZED);

	otherNoteForm->ShowWindow(SW_SHOW);
	
	otherNoteForm->UpdateWindow();
	otherNoteForm->GetTabCtrl()->DrawTabItem();
	this->m_pMainWnd = otherNoteForm;
	//_CrtDumpMemoryLeaks(); 메모리 릭 체크
	return TRUE;
}

OtherNoteApp otherNoteApp;
