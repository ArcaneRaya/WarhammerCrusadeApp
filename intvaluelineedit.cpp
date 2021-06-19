#include "intvaluelineedit.h"

IntValueLineEdit::IntValueLineEdit(QWidget *parent) : QLineEdit(parent)
{
    this->validator = new QIntValidator(-9999,9999, this);
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
    selectAll();
    this->insert(QString::number(currentValue));
}

void IntValueLineEdit::DecreaseValue()
{
    int currentValue = this->text().toInt();

    currentValue--;
    selectAll();
    this->insert(QString::number(currentValue));
}

void IntValueLineEdit::OnValueChanged(QString value)
{
    if (value.isEmpty()){
        insert("0");
        return;
    }

    if (value.startsWith("0") && value.toInt() > 0){
        selectAll();
        insert(QString::number(value.toInt()));
        return;
    }
    int newIntValue = value.toInt();
    if (newIntValue != this->intValue){
        this->intValue = newIntValue;
        this->IntValueChanged(this->intValue);
    }
}
