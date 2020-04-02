#ifndef CORE_H
#define CORE_H


#include <QApplication>

// ГОЛОВНА ФУНКЦІЯ, ЯКА ПОВЕРТАЄ НЕОБХІДНІ ЗНАЧЕННЯ
QString getRandom(int count);

// ФУНКЦІЯ ДЛЯ СТВОРЕННЯ ТЕКСТОВОГО РЯДКА З МАСИВУ ЦИФР
QString makeString(int ar[], int n);

// ОТРИМАННЯ ВИПАДКОВОГО ЧИСЛА У ЗАДАНИХ МЕЖАХ
int randomBetween(int low, int high);

// функція для сортування. повертає true, якщо необхідно поміняти
// значення місцями, в іншому випадку - false.
// Аналог Disposition
bool sortingAlg(QString str1, QString str2);

void sort(int ar[], int n);



#endif // CORE_H
