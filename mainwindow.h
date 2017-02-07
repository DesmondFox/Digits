#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "gameclass.h"
#include "startdialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

private:
    StartDialog *startDlg;
    QLabel      *lblStatus;
    QTreeWidget *tree;
    int         countDig;

signals:

public slots:

private slots:
    void slotStartGame(int count);
    void slotNewGame();     // Слот для кнопки "Новая игра" для запуска в дальнейшем slotStartGame
};

#endif // MAINWINDOW_H
