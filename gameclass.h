#ifndef GAMECLASS_H
#define GAMECLASS_H

#include <QObject>
#include <ctime>
#include <QDebug>

struct BullsAndCows
{
    int bulls;  // Количество быков (прямых попаданий)
    int cows;   // Количество коров (угаданных цифр)
};

class GameClass : public QObject
{
    Q_OBJECT
public:
    explicit GameClass(int count = 4, QObject *parent = 0);
    BullsAndCows    checkDigits(const QVector<int> &attempt);

private:
    QVector<int>    digits;
    int     countDigits;
    void    setDigits(int count = 4);

signals:
    void win();

public slots:
};

#endif // GAMECLASS_H
