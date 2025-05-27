#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <iomanip>

using namespace std;
//ру
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX 1
#endif

int main() {
    // ру
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif

    ifstream file("my_file.txt");
    string line;

    if (!file.is_open()) {
        cout << "Не удалось открыть файл" << endl;
        return 1;
    }

    while (getline(file, line)) {
        // ищем последний пробел в строке
        int index = line.length() - 1;
        while (index > 0 && line[index] != ' ') {
            index--;
        }

        // получаем имя файла после пробела
        string filename = line.substr(index + 1);

        // ищем точку в имени файла
        size_t dotPos = filename.find('.');
        if (dotPos != string::npos) {
            string ext = filename.substr(dotPos + 1);
            if (ext == "txt") {
                cout << filename << endl; // только txt файлы
            } else {
                cout << "ОШИБКА" << endl; // остальные
            }
        } else {
            // если нет точки — нет весело
            cout << "ОШИБКА" << endl;
        }
    }

    file.close();
    return 0;
}