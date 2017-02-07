#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // Стартовое окно для начала
    startDlg    = new StartDialog(this);
    connect(startDlg, SIGNAL(signalStart(int)), this, SLOT(slotStartGame(int)));
    startDlg->exec();

    QWidget     *wgt        = new QWidget(this);

    // Обьявление виджетов
    QLabel      *lblInput   = new QLabel(tr("Ввод:"), wgt);
    QLineEdit   *lineInput  = new QLineEdit(wgt);
    QPushButton *btnOK      = new QPushButton("&OK", wgt);
    QStatusBar  *sttBar     = new QStatusBar(this);
    QToolBar    *toolBar    = new QToolBar(this);

    lblStatus   = new QLabel(tr("Игра началась"), this);
    tree        = new QTreeWidget(wgt);

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
    toolBar->setMovable(false);
    QAction *acNewGame  = new QAction(QIcon(":/icons/Icons/button_newGame.png"), tr("Новая игра"), toolBar);

    sttBar->addWidget(lblStatus);
    btnOK->setDefault(true);
    btnOK->setIcon(QIcon(":/icons/Icons/button_ok.png"));




}

void MainWindow::slotStartGame(int count)
{
    countDig    = count;

    qDebug() << "Note:\tSlot is working [" << count << "]";
}

void MainWindow::slotNewGame()
{

}
