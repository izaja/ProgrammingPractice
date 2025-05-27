#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <iomanip>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX 1
#endif

using namespace std;

int main()
{
    #ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    #endif
    
    ifstream LastSTR("my_file.txt");
    string line;
    // объявление файла
    if (LastSTR.is_open())
    {
        // пока есть непустые строки
        while (getline(LastSTR, line))
        {
            // идем с конца строки, ищем первый пробел
            int index = line.length() - 1;
            while (line.at(index) != ' ' && index > 0)
            {
                index--;
            }
            // формируем подстроку с первого символа после пробела до последнего символа строки
            string filename = line.substr(index + 1, line.length() - 1);
            size_t dotPos = filename.find('.');
            //точка
            if (dotPos != string::npos)
            {   
                //расширение после точки
                string ext = filename.substr(dotPos + 1);
                if (ext == "txt")
                {
                    cout << filename << '\n';
                }
                else
                {   
                    //не тхт
                    cout << "ОШИБКА" << '\n';
                }
            }
            else
            {
                //нет точки
                cout << "ОШИБКА" << '\n';
            }
        }
        //закрываемся
        LastSTR.close();
    }
    else
    {
        // если нет в папке
        cout << "Unable to open file";
    }
    return 0;
}
