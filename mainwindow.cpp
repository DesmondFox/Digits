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
    btnOK->setAutoDefault(true);
    btnOK->setDefault(true);
    btnOK->setIcon(QIcon(":/icons/Icons/button_ok.png"));
    lineInput->setFocus();

    connect(btnOK, SIGNAL(clicked(bool)), SLOT(slotOkPress()));

    tryNumber = 1;

    connect(&game, SIGNAL(win()), SLOT(slotWin()));

    winFlag = false;
}

void MainWindow::slotStartGame(int count)
{

    // Количество цифр
    countDig    = count;

    // Генерация числа
    game.setDigits(count);

    if (!firstStartFlag)
    {
        qDebug() << "Note:\tSetting the widgets...";
        // Очистка виджетов и вектора избежания совпадений
        lineInput->clear();
        tree->clear();
        withoutMatches.clear();

        // Заполнение первоначальными данными
        lblStatus->setText(tr("Игра началась"));
        // Изменение валидатора на поле ввода
        lineInput->setValidator(new QRegExpValidator(QRegExp(QString("[0-9]{1,"+QString::number(countDig)+"}"))));
        // Указание фокуса при загрузке
        lineInput->setFocus();

        tryNumber = 1;
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

void MainWindow::slotOkPress()
{
    // Если количество цифр не подходит - игнорируем
    if (lineInput->text().length() < countDig)
        return;

    // Проверка на совпадения с прошлыми попытками
    bool matchFlag = false;
    for (int i = 0; i < withoutMatches.length(); i++)
    {
        if (withoutMatches.at(i) == lineInput->text())
        {
            matchFlag = true;
            break;
        }
    }
    if (matchFlag)
    {
        qDebug() << "Note:\tMatching!";
        lblStatus->setText(tr("<font color=red>Было уже</font>"));
    }
    else
    {
            // Переганяем в вектор строку
            QVector<int> tmpVector;
            for (int i = 0; i < countDig; i++)
                tmpVector << lineInput->text().at(i).digitValue();

            qDebug() << "Note:\tAdding:" << tmpVector;

            // Получаем данные и записываем в таблицу
            BullsAndCows tmp = game.checkDigits(tmpVector);
            // Если стоит флаг победы, то мы не будем заново добавлять это же число еще раз в таблицу
            if (!winFlag)
            {
                QTreeWidgetItem *item = new QTreeWidgetItem(tree);
                item->setText(0, QString::number(tryNumber));
                item->setText(1, lineInput->text());
                item->setText(2, QString(QString::number(tmp.bulls)+tr("Б, ")+QString::number(tmp.cows)+tr("К")));
                tree->addTopLevelItem(item);
                tryNumber++;
                withoutMatches << lineInput->text();
            }
            else
                winFlag = false;

    }
    lineInput->setText("");
    lineInput->setFocus();

}

void MainWindow::slotWin()
{
    // Поставим флаг победы для избежания добавления элемента прошлой игры в таблицу
    // Да, костыль
    winFlag = true;

    int wnd = QMessageBox::information(this, tr("Победа"),
                                       QString(tr("Вы угадали число <font color=green><b>")+
                                               game.getDigits()+tr("</b></font> с ")+
                                          QString::number(tryNumber)+tr(" попытки. <br>Хотите начать заново?")),
                                          QMessageBox::Yes | QMessageBox::Abort);
    if (wnd == QMessageBox::Yes)
        slotStartGame(countDig);
    if (wnd == QMessageBox::Abort)
        StartDialog::slotExit();
}

