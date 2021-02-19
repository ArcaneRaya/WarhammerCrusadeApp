#ifndef INTVALUELINEEDIT_H
#define INTVALUELINEEDIT_H

#include <QLineEdit>
#include <QObject>
#include <QIntValidator>


class IntValueLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    IntValueLineEdit(QWidget *parent = nullptr);

public slots:
    void IncreaseValue();
    void DecreaseValue();

private:
    const QIntValidator * validator;
};

#endif // INTVALUELINEEDIT_H
