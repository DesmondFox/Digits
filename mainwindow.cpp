#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // Установка флага первой загрузки
    // Нужно, чтобы не настраивать виджеты дважды
    firstStartFlag      = true;

    // Стартовое окно для начала
    startDlg    = new StartDialog(this);
    connect(startDlg, SIGNAL(signalStart(int)), this, SLOT(slotStartGame(int)));
    startDlg->exec();

    QWidget     *wgt        = new QWidget(this);
    // Обьявление виджетов
    QLabel      *lblInput   = new QLabel(tr("Ввод:"), wgt);
    QPushButton *btnOK      = new QPushButton("&OK", wgt);
    QStatusBar  *sttBar     = new QStatusBar(this);
    QToolBar    *toolBar    = new QToolBar(this);

    lblStatus   = new QLabel(tr("Игра началась"), this);
    tree        = new QTreeWidget(wgt);
    lineInput   = new QLineEdit(wgt);

    // Компоновка виджетов
    QHBoxLayout *pHBox      = new QHBoxLayout();
    pHBox->addWidget(lblInput,  0, Qt::AlignRight   | Qt::AlignTop);
    pHBox->addWidget(lineInput, 0, Qt::AlignCenter  | Qt::AlignTop);
    pHBox->addWidget(btnOK,     0, Qt::AlignLeft    | Qt::AlignTop);

    QVBoxLayout *pVBox      = new QVBoxLayout();
    pVBox->addLayout(pHBox);
    pVBox->addWidget(tree);
    wgt->setLayout(pVBox);

    this->setCentralWidget(wgt);
    this->setStatusBar(sttBar);
    this->addToolBar(toolBar);

    // Настройка виджетов
    lineInput->setValidator(new QRegExpValidator(QRegExp(QString("[0-9]{1,"+QString::number(countDig)+"}"))));
    tree->setColumnCount(3);

    QStringList columnHeaders;
    columnHeaders << tr("Номер")
                  << tr("Запрос")
                  << tr("Ответ");
    tree->setHeaderLabels(columnHeaders);
    tree->setColumnWidth(0, 50);

    // Настройка туллбара
//    toolBar->setFloatable(false);
    toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolBar->setMovable(false);
    QAction *acNewGame  = new QAction(QIcon(":/icons/Icons/button_newGame.png"), tr("Новая игра"));
    QAction *acQuit     = new QAction(QIcon(":/icons/Icons/button_quit.png"), tr("Выйти"));
    toolBar->addAction(acNewGame);
    toolBar->addAction(acQuit);

    connect(acNewGame, SIGNAL(triggered(bool)), SLOT(slotNewGame()));
    connect(acQuit, SIGNAL(triggered(bool)), SLOT(slotQuit()));

    // Настройка кнопок и других элементов
    sttBar->addWidget(lblStatus);
    btnOK->setDefault(true);
    btnOK->setIcon(QIcon(":/icons/Icons/button_ok.png"));
    lineInput->setFocus();



}

void MainWindow::slotStartGame(int count)
{

    // Количество цифр
    countDig    = count;
    if (!firstStartFlag)
    {
        qDebug() << "Note:\tSetting the widgets...";
        // Очистка виджетов
        lineInput->clear();
        tree->clear();

        // Заполнение первоначальными данными
        lblStatus->setText(tr("Игра началась"));
        // Изменение валидатора на поле ввода
        lineInput->setValidator(new QRegExpValidator(QRegExp(QString("[0-9]{1,"+QString::number(countDig)+"}"))));
        // Указание фокуса при загрузке
        lineInput->setFocus();
    }

    // Установка того, что новая игра запускается уже не в первый раз,
    // чтобы потом перенастроить виджеты
    if (firstStartFlag)
        firstStartFlag = false;
}

void MainWindow::slotNewGame()
{
    int wnd = QMessageBox::question(this, tr("Новая игра"),
                                    tr("Вы действительно хотите начать игру заново?"),
                                    QMessageBox::Yes | QMessageBox::No);
    if (wnd == QMessageBox::Yes)
        startDlg->exec();
    qDebug() << "Note:\tNew game request";
}

void MainWindow::slotQuit()
{
    int wnd = QMessageBox::question(this, tr("Выход из игры"),
                                    tr("Вы действительно хотите завершить игру?"),
                                    QMessageBox::Yes | QMessageBox::No);
    if (wnd == QMessageBox::Yes)
        StartDialog::slotExit();
}
