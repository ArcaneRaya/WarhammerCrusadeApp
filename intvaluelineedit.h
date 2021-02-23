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
    int GetIntValue();

signals:
    void IntValueChanged(int value);

public slots:
    void IncreaseValue();
    void DecreaseValue();

private slots:
    void OnValueChanged(QString value);

private:
    const QIntValidator * validator;
    int intValue;
};

#endif // INTVALUELINEEDIT_H
