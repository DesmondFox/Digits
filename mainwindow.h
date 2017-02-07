#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QMessageBox>
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
    QLineEdit   *lineInput;
    int         countDig;
    bool        firstStartFlag;

signals:

public slots:

private slots:
    void slotStartGame(int count);
    void slotNewGame();     // Слот для кнопки "Новая игра" для запуска в дальнейшем slotStartGame
    void slotQuit();
};

#endif // MAINWINDOW_H
