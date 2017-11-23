//CtrlLeftArrowKey.cpp

#include "CtrlLeftArrowKey.h"

CtrlLeftArrowKey::CtrlLeftArrowKey(Form *form)
	:KeyAction(form) {

}

CtrlLeftArrowKey::CtrlLeftArrowKey(const CtrlLeftArrowKey& source)
	:KeyAction(source) {

}

CtrlLeftArrowKey::~CtrlLeftArrowKey() {

}

CtrlLeftArrowKey& CtrlLeftArrowKey::operator=(const CtrlLeftArrowKey& source) {
	KeyAction::operator=(source);

	return *this;
}

#include "MemoForm.h"
#include "Caret.h"
#include "Memo.h"
#include "Line.h"
#include "Character.h"
#include "SingleCharacter.h"
#include "DoubleCharacter.h"
#include "SelectedBuffer.h"
void CtrlLeftArrowKey::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (dynamic_cast<MemoForm*>(this->form)) {
		Memo *memo = static_cast<Memo*>(this->form->GetContents());
		Line *line = memo->GetLine(memo->GetRow());

		Caret *caret = dynamic_cast<MemoForm*>(this->form)->GetCaret();


		if (memo->GetRow() > 0 || line->GetColumn() > 0) {
			if (line->GetColumn() > 0) {
				char previousCharacter = '\0';
				//caret->MovePreviousCharacter();
				line->MovePreviousColumn();
				Character *character = line->GetCharacter(line->GetColumn());
				char currentCharacter = '\0';
				if (dynamic_cast<SingleCharacter*>(character)) {
					currentCharacter = dynamic_cast<SingleCharacter*>(character)->GetValue();
				}
				else if (dynamic_cast<DoubleCharacter*>(character)) {
					currentCharacter = 'a';
				}

				//			while ((previousCharacter < 97 || previousCharacter > 122) || currentCharacter != ' ') {
				while ((previousCharacter < 33 || previousCharacter > 126 || currentCharacter != ' ') && line->GetColumn() > 0) {
					//caret->MovePreviousCharacter();
					line->MovePreviousColumn();
					character = line->GetCharacter(line->GetColumn());
					previousCharacter = currentCharacter;
					if (dynamic_cast<SingleCharacter*>(character)) {
						currentCharacter = dynamic_cast<SingleCharacter*>(character)->GetValue();
					}
					else if (dynamic_cast<DoubleCharacter*>(character)) {
						currentCharacter = 'a';
					}
				}
				if (line->GetColumn() > 0) {
					line->MoveNextColumn();
					//caret->MoveNextCharacter();
				}
			}
			else if (line->GetColumn() == 0) {
				//caret->MovePreviousLine();

				memo->MovePreviousRow();
				line = memo->GetLine(memo->GetRow());

				line->MoveLastColumn();
				//caret->MoveLastCharacter();
			}
		}
		caret->UpdateCaret();
		dynamic_cast<MemoForm*>(this->form)->GetSelectedBuffer()->SetIsSelecting(false);
	}
}