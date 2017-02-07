#include "startdialog.h"

StartDialog::StartDialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle(QApplication::applicationName()+ " " +
                         QApplication::applicationVersion());

    QLabel      *lblWelcome         = new QLabel(tr("<h2><b><center>Добро пожаловать<center></b></h2>"), this);
    QLabel      *lblEnterCount      = new QLabel(tr("Количество цифр"), this);
    QLabel      *lblClassic         = new QLabel(tr("(4 - классика)"), this);
    QPushButton *btnStart           = new QPushButton(tr("&Старт"), this);
    QPushButton *btnExit            = new QPushButton(tr("&Выход"), this);
    sbCountOfDigits    = new QSpinBox(this);

    sbCountOfDigits->setRange(2, 9);
    sbCountOfDigits->setValue(4);
    sbCountOfDigits->setMinimumWidth(70);
//    sbCountOfDigits->setFont(QFont("DeJaVu Sans", 12));
    btnStart->setDefault(true);

    QHBoxLayout *pHlay1 = new QHBoxLayout();
    pHlay1->addWidget(lblEnterCount);
    pHlay1->addWidget(sbCountOfDigits);
    pHlay1->addWidget(lblClassic);

    QHBoxLayout *pHlay2 = new QHBoxLayout();
    pHlay2->addWidget(btnStart);
    pHlay2->addWidget(btnExit);

    QVBoxLayout *pVlay  = new QVBoxLayout(this);
    pVlay->addWidget(lblWelcome);
    pVlay->addLayout(pHlay1);
    pVlay->addLayout(pHlay2);


    this->setLayout(pVlay);

//    connect(this,       SIGNAL(finished(int)),     SLOT(slotExit()));
    connect(btnExit,    SIGNAL(clicked(bool)),  SLOT(slotExit()));
    connect(btnStart,   SIGNAL(clicked(bool)),  SLOT(slotStart()));
}

void StartDialog::slotExit()
{
    std::exit(0);
}

void StartDialog::slotStart()
{
    emit signalStart(sbCountOfDigits->value());
    qDebug() << "Note:\tGame started with" << sbCountOfDigits->value() << "digits";
    this->close();
}
