#include "intvaluelineedit.h"

IntValueLineEdit::IntValueLineEdit(QWidget *parent) : QLineEdit(parent)
{
    this->validator = new QIntValidator(0,9999, this);
    this->setValidator(this->validator);
    connect(this, &QLineEdit::textChanged, this, &IntValueLineEdit::OnValueChanged);
}

int IntValueLineEdit::GetIntValue()
{
    return this->intValue;
}

void IntValueLineEdit::IncreaseValue()
{
    int currentValue = this->text().toInt();
    currentValue++;
    this->setText(QString::number(currentValue));
}

void IntValueLineEdit::DecreaseValue()
{
    int currentValue = this->text().toInt();
    currentValue--;
    this->setText(QString::number(currentValue));
}

void IntValueLineEdit::OnValueChanged(QString value)
{
    int newIntValue = value.toInt();
    if (newIntValue != this->intValue){
        this->intValue = newIntValue;
        this->IntValueChanged(this->intValue);
    }
}
