#include "pch.h"
#include<iostream>
#include<cmath>

#define PI 3.14159265

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    double x, y, z;
    cout << "1 задача" << "\n";
    cout << "Вычисление значения выражения (10 вариант)" << "\n\n";
    cout << "Введите значения для тех переменных:" << "\n";
    /* Start(x, y, z) */
    cout << "x = "; cin >> x;
    cout << "y = "; cin >> y;
    cout << "z = "; cin >> z;
    int result, znamen, injection;
    znamen = y + 2 * (z - x);
    injection = 3 * x;
    try {
        if (znamen == 0)
            throw "Знаменатель равен нулю. Выражение не имеет результата";
        if (injection % 90 == 0 && injection % 180 != 0)
            throw injection;
        result = 2 * tan(injection) + (x - 0.55 * y * z) / znamen;
        cout << "\nРезультат выражения = " << result;
    }
    catch (const char* exception) {
        cout << "Errow: " << exception << "\n";
    }
    catch (double i) {
        cout << "Error: " << "при значении угла " << i << " тангенс бесконечный";
    }

 /*   cout << "\n\n" << "2 задача" << "\n";
    int N;
    cout << "Введите целое число N > "; cin >> N;
    string evenNumber = (N > 99 && N < 1000 && (N % 2) == 0) ? "Число является четным трехзначным" : "Число НЕ является четным трехзначным";
    cout << evenNumber;
    */

    //cout << "\n\n 3 задача \n";
    //int N, prevDigit, lastDigit;
    //bool ascendingDigits = true;
    //cout << "Введите N > "; cin >> N;
    //prevDigit = N % 10;
    //while (N > 0) {
    //    N /= 10;
    //    lastDigit = N % 10;
    //    if (lastDigit >= prevDigit) {
    //        ascendingDigits = false;
    //        break;
    //    }
    //    prevDigit = lastDigit;
    //}
    //if (ascendingDigits) {
    //    cout << "Цифры числа образуют строго возрастающую последовательность\n";
    //}
    //else {
    //    cout << "Цифры числа НЕ образуют строго возрастающую последовательность\n";
    //}

    //cout << "4 задача\n\n";
    ////считает, сколько складываемых в сумме
    //float result = 0;
    //for (int i = 10; i <= 20; i++) {
    //    result += sin((float)i/10);
    //}
    //cout << "Результат выражения: " << result;
    return 0;
}
