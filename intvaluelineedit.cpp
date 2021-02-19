#include "intvaluelineedit.h"

IntValueLineEdit::IntValueLineEdit(QWidget *parent) : QLineEdit(parent)
{
    this->validator = new QIntValidator(0,9999, this);
    this->setValidator(this->validator);
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
