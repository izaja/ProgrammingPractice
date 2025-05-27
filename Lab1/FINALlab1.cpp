#include <iostream>
#include <cmath>
#include <limits>
#include <windows.h>
#include <iomanip>

using namespace std; //printf необязателен, по условию
// ру
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX 1
#endif

// почти ноль
bool isAlmostZero(double value) 
{
    return abs(value) < numeric_limits<double>::epsilon();
}

// "y" с чеком
double calculateY(double x, double a) 
{
    // проверка деления на ноль
    if (isAlmostZero(x)) 
    {
        return numeric_limits<double>::quiet_NaN();
    }

    double cos_val = cos(x / 2.0);
    
    // cos(x/2) = 0 и a = 0
    if (isAlmostZero(cos_val) && isAlmostZero(a)) 
    {
        return numeric_limits<double>::quiet_NaN();
    }

    // отрицательная степень дробного "а"
    if (cos_val < 0 && floor(a) != a) 
    {
        return numeric_limits<double>::quiet_NaN();
    }
    double denominator = x * (0.5 - pow(cos_val, a));
        if (isAlmostZero(denominator)) 
    {
        return numeric_limits<double>::quiet_NaN();
    }
    return 2.0 / denominator;
}

int main() 
{
    // ру
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif

    double a;
    double start = -0.9;
    double finish = 6.1;
    double delta = 0.5;
    int iteration = 1;
    
    cout << "Введите a: ";
    if (!(cin >> a)) 
        {
        cout << "а должно быть числом." << endl;
        return 1;
        }
    
    // проверка на NaN и бесконечность
    if (isnan(a) || isinf(a)) 
    {
        cout << "Некорректное значение a" << endl;
        return 1;
    }
    
    // диапазон основа cmath
    if (a != 0.0 && (abs(a) < 0.000001 || abs(a) > 1000000)) 
    {
    cout << "Ошибка диапазона" << endl;
        return 1;
    }
    
    // а0
    if (a == 0.0) 
    {
    cout << "a=0" << endl;
    }
    
    // таблица
    cout << "+------------+------------+------------+---------------+\n";
    cout << "|   № п/п    |     x      |     a      |      y        |\n";
    cout << "+------------+------------+------------+---------------+\n";
    
    // цикл
    for (double x = start; x <= finish + delta/2; x += delta) 
    {
        double y = calculateY(x, a);
        cout << "| " << setw(10) << iteration;
        // x
        cout << " | " << fixed << setprecision(2) << setw(10) << x;
        // a
        cout << " | " << fixed << setprecision(6) << setw(10) << a;
        // ошибки y
        if (isnan(y)) 
        {
            // ERROR вышли за рамки
            cout << " | " << setw(13) << "ERROR";
        } 
            else if (isinf(y)) 
            {
            // INF ±∞
            cout << " | " << setw(13) << "INF";
            } 
                else 
                {
                // вывод
                cout << " | " << fixed << setprecision(6) << setw(13) << y;
                }
        cout << " |\n";
        iteration++;
    }
    cout << "+------------+------------+------------+---------------+\n";
    return 0;
}