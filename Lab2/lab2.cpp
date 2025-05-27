#include <iostream>
#include <limits>
#include <windows.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX 1
#endif

using namespace std;

int safeInputInt(const char* prompt, int minVal, int maxVal) 
{
    while (true) {
        cout << prompt;
        string input;
        getline(cin, input);
        
        try {
            size_t pos;
            int value = stoi(input, &pos);
            
            // Проверяем, что вся строка была обработана (нет лишних символов)
            if (pos != input.length()) 
            {
                throw invalid_argument("Invalid input");
            }
            
            if (value < minVal || value > maxVal) 
            {
                cout << "Ошибка: число должно быть между " << minVal << " и " << maxVal << "\n";
                continue;
            }
            
            return value;
        }
        catch (...) {
            cout << "Ошибка: введено недопустимое число\n";
        }
    }
}

int safeInputDay(int year, int month) 
{
    int day;
    while (true) {
        day = safeInputInt("Введите день: ", 1, 31);
        
        bool valid = true;
        if (month == 2) 
        {
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) 
            {
                if (day > 29) valid = false; // високосный
            } else 
            {
                if (day > 28) valid = false; // невисокосный
            }
        } else if (month == 4 || month == 6 || month == 9 || month == 11) 
        {
            if (day > 30) valid = false;
        }
        
        if (valid) return day;
        cout << "Недопустимый день\n";
    }
}

int main() 
{
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif
    
    int minYear = 9999, maxYear = -1, minMonth = 99, maxMonth = -1, minDay = 99, maxDay = -1;
    int totalYear = 0, totalMonth = 0, totalDay = 0;

    for (int i = 0; i < 5; i++) {
        cout << "\nЧеловек № " << i + 1 << "\n";
        // ГОД
        int year = safeInputInt("Введите год: ", 1, 2025);
        // МЕСЯЦ
        int month = safeInputInt("Введите месяц: ", 1, 12);
        // ДЕНЬ
        int day = safeInputDay(year, month);

        // мин дата
        if (year < minYear || 
           (year == minYear && month < minMonth) || 
           (year == minYear && month == minMonth && day < minDay)) 
           {
            minYear = year;
            minMonth = month;
            minDay = day;
            }
        // макс дата
        if (year > maxYear || 
           (year == maxYear && month > maxMonth) || 
           (year == maxYear && month == maxMonth && day > maxDay)) 
            {
            maxYear = year;
            maxMonth = month;
            maxDay = day;
            }
        totalYear += year;
        totalMonth += month;
        totalDay += day;
    }
    
    cout << "\nРезультаты:\n";
    cout << "Дата рождения самого старшего: " << maxDay << "." << maxMonth << "." << maxYear << "\n";
    cout << "Дата рождения самого младшего: " << minDay << "." << minMonth << "." << minYear << "\n";
    cout << "Средняя дата рождения: " << totalDay/5 << "." << totalMonth/5 << "." << totalYear/5 << "\n";

    return 0;
}