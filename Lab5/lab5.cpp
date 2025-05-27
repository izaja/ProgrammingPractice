#include <iostream>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <cstdlib>  
#include <ctime>    
#include <windows.h> 
#include <stdio.h>  
 

HANDLE hStdout;

int main() {
    // настройка
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    // Получение значений текущих цветов шрифта и фона:
    CONSOLE_SCREEN_BUFFER_INFO start_attribute;
    // get concole colour
    GetConsoleScreenBufferInfo(hStdout, &start_attribute);

    // матрица
    const int MAX_ROWS = 100, MAX_COLUMNS = 100;
    int numbers[MAX_ROWS][MAX_COLUMNS];
    int m, n, z;

    // ввод m
    printf("m (1-%d): ", MAX_ROWS);
    if (!(std::cin >> m) || m <= 0 || m > MAX_ROWS) {
        std::cin.clear();
        while (std::cin.get() != '\n'); // очистка буфера
        printf("ERROR: 1 to %d.\n", MAX_ROWS);
        return 1;
    }

    // ввод n
    printf("n (1-%d): ", MAX_COLUMNS);
    if (!(std::cin >> n) || n <= 0 || n > MAX_COLUMNS) {
        std::cin.clear();
        while (std::cin.get() != '\n');
        printf("ERROR: 1 to %d.\n", MAX_COLUMNS);
        return 1;
    }

    // рандомайзер
    srand(time(0));
    printf("\n(%dx%d):\n", m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            numbers[i][j] = rand() % 10;
            printf("%d\t", numbers[i][j]);
        }
        printf("\n");
    }

    // ввод z
    printf("\nz: ");
    if (!(std::cin >> z)) {
        std::cin.clear();
        while (std::cin.get() != '\n');
        printf("ERROR:\n");
        return 1;
    }

    // Обработка массива
    printf("\n(%dx%d)\n", m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // если элемент массива больше z, то вычитаем z из него
            if (numbers[i][j] > z) {
                numbers[i][j] -= z;
                // и задаем вывод другим цветом
                SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_RED);
            }
            // вывод элмемента массива
            printf("%d\t", numbers[i][j]);
            // возвращаем обычный цвет под самый конец
            SetConsoleTextAttribute(hStdout, start_attribute.wAttributes);
        }
        printf("\n");
    }

    return 0;
}