//TabCtrlMouseLButtonDoubleClicked.cpp

#include "TabCtrlMouseLButtonDoubleClicked.h"
#include "TabCtrl.h"
#include "EditControl.h"

TabCtrlMouseLButtonDoubleClicked::TabCtrlMouseLButtonDoubleClicked(TabCtrl *form)
	:MouseAction(form) {
	//this->form = form;
}

TabCtrlMouseLButtonDoubleClicked::TabCtrlMouseLButtonDoubleClicked(const TabCtrlMouseLButtonDoubleClicked& source)
	: MouseAction(source) {
	//this->form = source.form;
}

TabCtrlMouseLButtonDoubleClicked::~TabCtrlMouseLButtonDoubleClicked() {

}

TabCtrlMouseLButtonDoubleClicked& TabCtrlMouseLButtonDoubleClicked::operator=(const TabCtrlMouseLButtonDoubleClicked& source) {
	//this->form = source.form;
	MouseAction::operator=(source);

	return *this;
}

void TabCtrlMouseLButtonDoubleClicked::OnMouseAction(UINT nFlags, CPoint point) {
	static_cast<TabCtrl*>(this->form)->OnChangeName();
}

void TabCtrlMouseLButtonDoubleClicked::OnMouseAction(int x, int y) {

}

void TabCtrlMouseLButtonDoubleClicked::OnMouseAction(UINT nSide, LPRECT lpRect) {

}