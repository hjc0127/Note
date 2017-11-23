//HighLight.cpp

#include "HighLight.h"
#include "MemoForm.h"
#include "Memo.h"
#include "Line.h"
#include "Character.h"

HighLight::HighLight(MemoForm *memoForm, Long beginRow, Long beginColumn, Long endRow, Long endColumn, COLORREF crColor) {
	this->memoForm = memoForm;
	this->beginRow = beginRow;
	this->beginColumn = beginColumn;
	this->endRow = endRow;
	this->endColumn = endColumn;
	this->crColor = crColor;
	this->highLightBuffer = 0;
}

HighLight::~HighLight() {
	if (this->highLightBuffer != 0) {
		delete this->highLightBuffer;
	}
}

HighLight::HighLight(const HighLight& source) {
	this->memoForm = source.memoForm;
	this->beginRow = source.beginRow;
	this->beginColumn = source.beginColumn;
	this->endRow = source.endRow;
	this->endColumn = source.endColumn;
	this->crColor = source.crColor;
	this->highLightBuffer = new Memo(*source.highLightBuffer);
}

HighLight& HighLight::operator = (const HighLight& source) {
	this->memoForm = source.memoForm;
	this->beginRow = source.beginRow;
	this->beginColumn = source.beginColumn;
	this->endRow = source.endRow;
	this->endColumn = source.endColumn;
	this->crColor = source.crColor;
	if (this->highLightBuffer != 0) {
		delete this->highLightBuffer;
	}
	this->highLightBuffer = new Memo(*source.highLightBuffer);
	return *this;
}

void HighLight::SetBegintRow(Long beginRow) {
	this->beginRow = beginRow;
}

void HighLight::SetBeginColumn(Long beginColumn) {
	this->beginColumn = beginColumn;
}

void HighLight::SetEndRow(Long endRow) {
	this->endRow = endRow;
}

void HighLight::SetEndColumn(Long endColumn) {
	this->endColumn = endColumn;
}


void HighLight::CopyToHighLightBuffer() {
	//this->SetPosition(currentRow, currentColumn);

	if (this->highLightBuffer != 0) {
		delete this->highLightBuffer;
		this->highLightBuffer = 0;
	}

	this->highLightBuffer = new Memo;
	this->highLightBuffer->AddLine();
	Line *highLightBufferLine = this->highLightBuffer->GetLine(this->highLightBuffer->GetRow());

	Memo *memo = static_cast<Memo*>(this->memoForm->GetContents());
	Long i = this->beginRow;
	Line *line = memo->GetLine(i);
	Long j = this->beginColumn;

	if (this->beginRow == this->endRow) {
		while (j < this->endColumn) {
			highLightBufferLine->Add(line->GetCharacter(j)->Clone());
			j++;
		}
	}
	else {
		while (j < line->GetLength()) {
			highLightBufferLine->Add(line->GetCharacter(j)->Clone());
			j++;
		}
	}

	i++;
	while (i < this->endRow) {
		line = memo->GetLine(i);
		this->highLightBuffer->Add(line->Clone());
		i++;
	}

	if (this->beginRow != this->endRow && i == this->endRow) {
		line = memo->GetLine(i);
		this->highLightBuffer->AddLine();
		highLightBufferLine = this->highLightBuffer->GetLine(this->highLightBuffer->GetRow());
		j = 0;
		while (j < this->endColumn) {
			highLightBufferLine->Add(line->GetCharacter(j)->Clone());
			j++;
		}
	}
}