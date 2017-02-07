#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Digits");
    a.setApplicationVersion("0.1");

    MainWindow wnd;
    wnd.show();

    return a.exec();
}
