#include "gameclass.h"

GameClass::GameClass(int count, QObject *parent) : QObject(parent)
{

}

BullsAndCows GameClass::checkDigits(const QVector<int> &attempt)
{
    BullsAndCows toResult;

    // Вычисляем быков, т.е. прямые попадания
    int bulls = 0;
    for (int i = 0; i < countDigits; i++)
        if (digits.at(i) == attempt.at(i))
            bulls++;

    // Если прямых попаданий равно количеству цифр, то победа
    if (bulls == countDigits)
        emit win();

    // Вычисляем коров, т.е. просто отгаданные числа
    int cows = 0;
    for (int i = 0; i < countDigits; i++)
    {
        for (int j = 0; j < countDigits; j++)
        {
            if ((i != j) && (digits.at(i) == attempt.at(j)))
            {
                cows++;
            }
        }
    }
    toResult.bulls  = bulls;
    toResult.cows   = cows;

#ifdef _DEBUG
    qDebug() << "Bulls: " << toResult.bulls << " Cows: " << toResult.cows;
#endif

    return toResult;
}

void GameClass::setDigits(int count)
{
    countDigits = count;
    // Удаляем все данные и обнуляем переменные
    digits.clear();
    // Временно сохраняем все значения в вектор
    QVector<int> nums;


    int tmp;
    qsrand(time(0));
    for (int i = 0; i < count; i++)
    {
        while(true)
        {
            tmp = qrand() % 10;
            bool flag = false;
            for (int j = 0; j < nums.length(); j++)
            {
                if (nums.at(j) == tmp)
                {
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                nums << tmp;
                break;
            }
        }
        digits << tmp;
    }

#ifdef _DEBUG
    qDebug() << "Note:\tGenerated: " << digits;
#endif
}

QString GameClass::getDigits()
{
    QString dig;
    for (int i = 0; i < digits.length(); i++)
        dig += QString::number(digits.at(i));
    return dig;
}

