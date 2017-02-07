#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QApplication>
#include <QtWidgets>

class StartDialog : public QDialog
{
    Q_OBJECT
public:
    explicit StartDialog(QWidget *parent = 0);

private:
    QSpinBox *sbCountOfDigits;

public slots:
    static void slotExit();

private slots:
    void slotStart();

signals:
    void signalStart(int digits);
public slots:
};

#endif // STARTDIALOG_H
